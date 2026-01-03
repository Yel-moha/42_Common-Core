#include "minishell.h"

int apply_heredoc(char *delimiter, t_shell *shell)
{
    int fd[2];
    pid_t pid;
    int saved_stdin;

    if (pipe(fd) < 0)
        return (-1);
    saved_stdin = dup(STDIN_FILENO);
    pid = fork();
    if (pid == 0)
    {
        dup2(saved_stdin, STDIN_FILENO);  // <-- RIPRISTINA per readline()
        close(saved_stdin);
        close(fd[0]);
        read_heredoc(delimiter, shell, fd[1]);
        close(fd[1]);
        exit(0);
    }
    else
    {
        close(fd[1]);
       // waitpid(pid, NULL, 0);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
    }
    return (0);
}
void	process_heredocs(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*cmd;
	t_redir	*redir;
	int		pipefd[2];
	int		saved_stdin;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == T_HEREDOC)
			{
				if (pipe(pipefd) < 0)
					return ;
				
				saved_stdin = dup(STDIN_FILENO);
				read_heredoc(redir->target, shell, pipefd[1]);
				close(pipefd[1]);
				
				// Salva fd pipe
				redir->heredoc_fd = pipefd[0];
				
				dup2(saved_stdin, STDIN_FILENO);
				close(saved_stdin);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}