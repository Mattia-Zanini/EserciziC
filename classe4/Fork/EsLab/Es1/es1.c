/// \file es1.c
/// \author Mattia Zanini
/// \date 18/11/2021

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/**
 * \fn int main()
 * \brief funzione che si occupa di generare tre figli i quali scirvono in modo consecutivo su file, in seguito il padre legge il contenuto del file e lo mostra a schermo
 */

int main()
{
    int pid1, pid2, pid3, status;
    FILE *fp;
    if ((fp = fopen("output.txt", "w+")) == NULL)
    {
        printf("Figlio 1: Impossibile aprire il file\n");
    }
    pid1 = fork();
    if (pid1 == 0) //figlio più lento
    {
        sleep(6);
        char row[] = "Figlio 1: Ciao sono il primo figlio\n";
        fprintf(fp, "%s", row);
        fclose(fp);
        exit(1);
    }
    else if (pid1 > 0)
    {
        pid2 = fork();
        if (pid2 == 0)
        {
            sleep(4);
            char row[] = "Figlio 2: Ciao sono il secondo figlio\n";
            fprintf(fp, "%s", row);
            exit(2);
        }
        else if (pid2 > 0)
        {
            pid3 = fork();
            if (pid3 == 0) //figlio più veloce
            {
                char row[] = "Figlio 3: Ciao sono il terzo figlio\n";
                fprintf(fp, "%s", row);
                exit(3);
            }
            else if (pid3 > 0)
            {
                printf("Padre: Aspetto che il figlio più lento finisca di scrivere sul file\n");
                waitpid(pid1, &status, 0);
                printf("Padre: Ok i miei figli hanno appena finito, vado a leggere quello che hanno scritto\n\n");
                FILE *fp;
                if ((fp = fopen("output.txt", "r")) == NULL)
                {
                    printf("Padre: Impossibile aprire il file\n");
                }
                else
                {
                    char c;
                    while (!feof(fp))
                    {
                        c = fgetc(fp);
                        if (c != EOF)
                            putchar(c);
                    }
                    printf("\nQuesto è quello che i miei figli hanno scritto\n");
                }
                fclose(fp);
            }
        }
    }
    return 0;
}