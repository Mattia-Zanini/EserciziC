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
                    int piped1[2];
                    pipe(piped1);
                    if(p1 == 0) //figlio 1
                    {
                    }
                    else if( p1 > 0) //padre
                    {
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