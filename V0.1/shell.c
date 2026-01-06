#include "shell.h"

void execute_command(char *line, char *shell_name)
{
    pid_t pid;
    int status;
    char *argv[2];
    static int cmd_count = 1;

    /* Ignorer les lignes vides */
    if (line[0] == '\0')
        return;

    argv[0] = line;
    argv[1] = NULL;

    pid = fork();
    
    if (pid == -1)
    {
        perror("fork");
        return;
    }
    else if (pid == 0) /* Processus enfant */
    {
        if (execve(line, argv, environ) == -1)
        {
            fprintf(stderr, "%s: %d: %s: not found\n", 
                    shell_name, cmd_count, line);
            exit(127);
        }
    }
    else /* Processus parent */
    {
        wait(&status);
    }
    
    cmd_count++;
}
