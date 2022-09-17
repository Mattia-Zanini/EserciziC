/// \file es.c
/// \author Mattia Zanini
/// \date 19/11/2021

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/**
 * \fn int main()
 * \brief 
 */

int main()
{
    int pid1, pid2, pid3, status;
    pid1 = fork();
    if (pid1 == 0) //figlio più lento
    {
        printf("Ciao io sono Qui\n");
        exit(1);
    }
    else if (pid1 > 0)
    {
        pid2 = fork();
        if (pid2 == 0)
        {
            printf("Ciao io sono Quo\n");
            exit(2);
        }
        else if (pid2 > 0)
        {
            pid3 = fork();
            if (pid3 == 0) //figlio più veloce
            {
                printf("Ciao io sono Qua\n");
                exit(3);
            }
            else if (pid3 > 0)
            {
                waitpid(pid3, &status, 0);
                printf("L'ultimo figlio ha terminato\n");
            }
        }
        return 0;
    }
}