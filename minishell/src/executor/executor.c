#include "minishell.h"

void execute_single_cmd(t_cmd *cmd, t_shell *shell)
{
    pid_t pid;
    int saved_stdin;
    int saved_stdout;
    int status;

    if (!cmd || !cmd->argv || !cmd->argv[0])
        return;

    // 1. CONTROLLA SE È ARRIVATO SIGINT PRIMA DI INIZIARE
    if (g_signal == SIGINT)
    {
        shell->exit_code = 130;  // Bash: SIGINT = 130
        g_signal = 0;  // Reset
        printf("\n");   // Bash stampa nuova riga
        return;         // Non eseguire il comando
    }

    saved_stdin = dup(STDIN_FILENO);
    saved_stdout = dup(STDOUT_FILENO);

    if (apply_redirections(cmd->redirs, shell) < 0)
    {
        shell->exit_code = 1;  // Redirection fallita
        // Ripristina stdin/stdout prima di uscire
        dup2(saved_stdin, STDIN_FILENO);
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdin);
        close(saved_stdout);
        return;
    }

    if (is_builtin(cmd->argv[0]))
    {
        shell->exit_code = run_builtin(cmd, shell);
    }
    else
    {
        pid = fork();
        if (pid == 0)
        {
            // Processo figlio
            execve_or_die(cmd, shell);
        }
        else if (pid > 0)
        {
            // Processo padre
            waitpid(pid, &status, 0);
            
            if (WIFEXITED(status))
                shell->exit_code = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
            {
                int sig = WTERMSIG(status);
                if (sig == SIGINT)
                {
                    shell->exit_code = 130;
                    printf("\n");  // Bash stampa nuova riga per SIGINT
                }
                else if (sig == SIGQUIT)
                {
                    shell->exit_code = 131;
                    printf("Quit (core dumped)\n");  // Come bash
                }
                else
                {
                    shell->exit_code = 128 + sig;  // Formula standard
                }
            }
            // Reset segnale dopo averlo gestito
            g_signal = 0;
        }
        else
        {
            perror("fork");
            shell->exit_code = 1;
        }
    }

    // 2. RIPRISTINA stdin/stdout DOPO aver gestito exit_code
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
}


void execute_pipeline(t_cmd *cmds, t_shell *shell)
{
    int     fd[2];
    int     prev_fd;
    pid_t   pid;
    pid_t   last_pid;
    int     status;

    prev_fd = -1;
    while (cmds)
    {
        if (cmds->next)
            pipe(fd);

        pid = fork();
        if (pid == 0)
        {
            if (prev_fd != -1)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (cmds->next)
            {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);
            }
            // redirections + heredoc QUI
            execve_or_builtin(cmds, shell);
            exit(1);
        }
        if (prev_fd != -1)
            close(prev_fd);
        if (cmds->next)
        {
            close(fd[1]);
            prev_fd = fd[0];
        }
        last_pid = pid;
        cmds = cmds->next;
    }
    waitpid(last_pid, &status, 0);
    while (wait(NULL) > 0)
        ;
    if (WIFEXITED(status))
         shell->exit_code = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
         shell->exit_code = 128 + WTERMSIG(status);
}
