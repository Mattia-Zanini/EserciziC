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
        int status;
        int tot = 0;
        char str[WORD_LENGTH];
        while (1)
        {
            printf("Inserisci la parola che vuoi cercare:\n");
                scanf("%s", str);
                if (strcmp(str, "fine") != 0)
                {
                    int p1 = fork();
                    int piped[2];
                    pipe(piped);
                    if(p1 == 0) //figlio 1
                    {
                        close(1); // stdout
                        dup(piped[WRITE]);
                        close(piped[READ]);
                        close(piped[WRITE]);
                        exit(0);
                    }
                    else if( p1 > 0) //padre
                    {
                        int p2 = fork();
                        int piped2[2];
                        pipe(piped2);
                        if(p2 == 0) // figlio 2
                        {
                            sleep(3);
                            close(0); // stdin
                            dup(piped[READ]);
                            close(piped[READ]);
                            close(piped[WRITE]);

                            close(1); // stdout
                            dup(piped2[WRITE]);
                            close(piped2[WRITE]);
                            close(piped2[READ]);
                            exit(0);
                        }
                        else if(p2 > 0) //padre
                        {
                            close(piped[WRITE]);
                            close(piped[READ]);

                            int p3 = fork();
                            int piped3[2];
                            pipe(piped3);
                            if(p3 == 0) // figlio 3
                            {
                                sleep(6);

                                close(0); // stdin
                                dup(piped2[READ]);
                                close(piped2[READ]);
                                close(piped2[WRITE]);

                                close(1); // stdout
                                dup(piped3[WRITE]);
                                close(piped3[WRITE]);
                                close(piped3[READ]);
                                exit(0);
                            }
                            else if(p3 > 0) //padre
                            {
                                close(piped2[READ]);
                                close(piped2[WRITE]);

                                close(0); // stdin
                                dup(piped3[READ]);
                                close(piped3[READ]);
                                close(piped3[WRITE]);

                                printf("Padre\n");
                                sprintf(str, "ls -l /proc/%d/fd", getpid());
                                system(str);

                                waitpid(p1, &status, 0);
                                waitpid(p2, &status, 0);
                                waitpid(p3, &status, 0);
                            }
                        }
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
        printf("Argomenti Errati\n");
    }
    return 0;
}