/*
Assignment name:        picoshell
Expected files:         picoshell.c
Allowed functions:      close, fork, wait, exit, execvp, dup2, pipe
___________________________________________________________________

Write the following function:

int    picoshell(char **cmds[]);

The goal of this function is to execute a pipeline. It must execute each
commands of cmds and connect the output of one to the input of the
next command (just like a shell).
e
Cmds contains a null-terminated list of valid commands. Each rows
of cmds are an argv array directly usable for a call to execvp. The first
arguments of each command is the command name or path and can be passed
directly as the first argument of execvp.

If any error occur, The function must return 1 (you must of course
close all the open fds before). otherwise the function must wait all child
processes and return 0. You will find in this directory a file main.c which
contain something to help you test your function.


Examples: 
./picoshell /bin/ls "|" /usr/bin/grep picoshell
picoshell
./picoshell echo 'squalala' "|" cat "|" sed 's/a/b/g'
squblblb

___________________________________________________________________

Old summary by a student:
You are given a main function. It converts received arguments into cmds array
of strings. When there is a pipe the commands after the pipe are in the next
array of strings. You have to create a pipeline using the cmds you receive from
the main, and execute them. If there is any error the function should return 1.
Close all FFS before returning. If the cmds executed successfully wait all
child processes and return 0.
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h> //il tipo pid_t si torva qui

int    picoshell(char **cmds[])
{
    int num = 0;

    while(cmds[num] != NULL) //null terminated list of valid comands
        num++;
    
    int fd[2]; //fd[0] per la lettura e fd[1] per la scrittura;
    int prev_fd = -1;
    pid_t pids[num];// tiene traccia dei processi figli

    for (int i = 0; i < num; i++) //num adesso e' il numero di comandi
    {
        if(i < num - 1) //se non e' l'ultimo comando crea una pipe
        {
            if(pipe(fd) == -1)
            {
                perror("pipe");
                return(1);
            }
        }
        pids[i] = fork(); //crea un processo figlio (pid = 0 --> figlio)

        if(pids[i] == -1) //gestione errore avvio processo figlio con fork
        {
            perror("fork");
            return(1);
        }
        if(pids[i] == 0) //inizio processo figlio
        {
            if(prev_fd != -1) //se il comando non e' il primo leggi da prev_fd
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if(i < num - 1) //se il comando non e' l'ultimo scrivi sulla pipe
            {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);
            }
            execvp(cmds[i][0], cmds[i]); //esegui il comando
            perror("esecvp");
            exit(1);
        }           //fine processo figlio
        if(prev_fd != 1) //ritorno al processo padre
            close(prev_fd);
        if(i < num - 1)
        {
            close(fd[1]);
            prev_fd = fd[0];
        }
    }
    for(int i = 0; i < num; i++) //Attendi che tutti i processi figli abbiano finito
        wait(NULL);
    return (0);
}


//main per il test della funzione
int main(void)
{
    char *cmd1[] = {"ls", "-l", NULL};
    char *cmd2[] = {"grep", ".j", NULL};
    char *cmd3[] = {"wc", "-l", NULL};

    char **cmds[] = {cmd1, cmd2, cmd3, NULL};

    picoshell(cmds);

    return 0;
}