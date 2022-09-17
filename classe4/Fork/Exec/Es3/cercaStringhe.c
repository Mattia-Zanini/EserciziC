#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1
#define WORD_LENGTH 10

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        int tot = 0;
        int piped[2];
        int pStat = pipe(piped);
        if (pStat == 0)
        {
            char str[WORD_LENGTH];
            while (1)
            {
                printf("Inserisci la parola che vuoi cercare:\n");
                scanf("%s", str);
                if (strcmp(str, "fine") != 0)
                {
                    int p1 = fork();
                    if (p1 == 0) // figlio
                    {
                        close(1);
                        dup(piped[WRITE]);
                        close(piped[WRITE]);
                        close(piped[READ]);

                        execl("/bin/grep", "grep", "-c", str, argv[1], NULL);
                        exit(1);
                    }
                    else if (p1 > 0) // padre
                    {
                        wait(&p1);
                        if (p1 != -1)
                        {
                            char ris;
                            read(piped[READ], &ris, 4);
                            printf("'%s' è stata individuata %d volte\n\n", str, atoi(&ris));
                            tot += atoi(&ris);
                        }
                        else
                        {
                            printf("Errore durante la chiamata exec\n");
                        }
                    }
                    else // errore generazione figlio
                    {
                        printf("Errore durante la generazione del figlio\n");
                        break;
                    }
                }
                else // termina il ciclo
                {
                    break;
                }
            }
            printf("La ricerca ha prodotto %d risultati totali\n", tot);
        }
        else
        {
            printf("Errore durante la creazione del canale pipe\n");
        }
    }
    else
    {
        printf("Argomenti Errati\n");
    }
    return 0;
}