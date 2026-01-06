#include "shell.h"

extern char **environ;

int main(int argc, char **argv)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    int interactive;

    (void)argc; /* Éviter warning unused */
    
    interactive = isatty(STDIN_FILENO);

    while (1)
    {
        if (interactive)
        {
            printf("($) ");
            fflush(stdout);
        }

        nread = getline(&line, &len, stdin);
        
        if (nread == -1) /* EOF (Ctrl+D) */
        {
            if (interactive)
                printf("\n");
            break;
        }

        /* Supprimer le '\n' final */
        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        /* Exécuter la commande */
        execute_command(line, argv[0]);
    }

    free(line);
    return (0);
}
