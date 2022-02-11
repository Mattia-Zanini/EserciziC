#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// cat file.txt | grep -o *parola* | wc -l

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
                    if (p1 == 0) // figlio 1 CAT
                    {
                        close(1);
                        dup(piped[WRITE]);
                        close(piped[WRITE]);
                        close(piped[READ]);

                        execl("/bin/cat", "cat", argv[1], NULL);
                        exit(1);
                    }
                    else if (p1 > 0) // padre
                    {
                        int piped2[2];
                        pStat = pipe(piped2);
                        if (pStat == 0)
                        {
                            int p2 = fork();
                            if (p2 == 0) // figlio 2 GREP
                            {
                                close(0);
                                dup(piped[READ]);
                                close(piped[READ]);
                                close(piped2[READ]);
                                close(1);
                                dup(piped2[WRITE]);
                                close(piped2[WRITE]);
                                close(piped[WRITE]);

                                execl("/bin/grep", "grep", "-o", str, NULL);
                                exit(1);
                            }
                            else if (p2 > 0) // padre
                            {
                                int piped3[2];
                                pStat = pipe(piped3);
                                if (pStat == 0)
                                {
                                    int p3 = fork();
                                    if (p3 == 0) // figlio 3 WC
                                    {
                                        close(0);
                                        dup(piped2[READ]);
                                        close(piped[READ]);
                                        close(piped2[READ]);
                                        close(piped3[READ]);
                                        close(1);
                                        dup(piped3[WRITE]);
                                        close(piped3[WRITE]);
                                        close(piped2[WRITE]);
                                        close(piped[WRITE]);

                                        execl("/bin/wc", "wc", "-l", NULL);
                                        exit(1);
                                    }
                                    else if (p3 > 0) // padre
                                    {
                                        wait(&p3);
                                        if (p3 != -1)
                                        {
                                            char ris;
                                            read(piped3[READ], &ris, 4);
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
                                        printf("Errore durante la generazione del terzo figlio\n");
                                        break;
                                    }
                                }
                                else
                                {
                                    printf("Errore durante la creazione del terzo canale pipe\n");
                                }
                            }
                            else // errore generazione figlio
                            {
                                printf("Errore durante la generazione del secondo figlio\n");
                                break;
                            }
                        }
                        else
                        {
                            printf("Errore durante la creazione del secondo canale pipe\n");
                        }
                    }
                    else // errore generazione figlio
                    {
                        printf("Errore durante la generazione del primo figlio\n");
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
            printf("Errore durante la creazione del primo canale pipe\n");
        }
    }
    else
    {
        printf("Argomenti Errati\n");
    }
    return 0;
}