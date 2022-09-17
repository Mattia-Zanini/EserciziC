/// @file es2.c
/// @author Mattia Zanini
/// @date 18/11/2021
/// @brief file che genera due figli i quali, a loro volta, ne generano altri due e dopo aver fatto ciò i figli del padre aspettano in ordine i loro figli generati il padre, invece, attende la terminazione dei figli nell'ordine inverso con cui li crea

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * @fn int main()
 * @brief Funzione che assegna un pid iniziale, genera due figli i quali, a loro volta, ne generano altri due e dopo aver fatto ciò i figli del padre aspettano in ordine i loro figli generati il padre, invece, attende la terminazione dei figli nell'ordine inverso con cui li crea
*/

int main()
{
    int f1, f2, g1, g2, h1, h2, padre;
    padre = getpid();
    f1 = 0;
    f2 = 0;
    g1 = 0;
    h1 = 0;
    g2 = 0;
    h2 = 0;
    printf("1) processo padre con pid: %i\n", padre);
    f1 = fork(); //nasce il primo figlio
    if (f1 > 0)  //processo padre
    {
        printf("2) processo figlio 1 con pid: %i\n", f1);
        f2 = fork(); //nasce il secondo figlio
        if (f2 > 0)
        {
            printf("4) processo figlio 2 con pid: %i\n", f2);
            waitpid(f2, 0, 0);
            printf("11) ha terminato F2: %i \n", f2);
            waitpid(f1, 0, 0);
            printf("12) ha terminato F1: %i \n", f1);
        }
        else if (f2 == 0)
        {
            g2 = fork(); //nipote 2 di f2
            if (g2 == 0)
                exit(0);
            else
            {
                h2 = fork();
                if (h2 == 0)
                    exit(0);
                else
                {
                    printf("5) processo nipote 1 di F2 con pid: %i \n", g2);
                    printf("6) processo nipote 2 di F2 con pid: %i \n", h2);
                    waitpid(g2, 0, 0);
                    waitpid(h2, 0, 0);
                    printf("9) ha terminato N1: %i \n", g2);
                    printf("10) ha terminato N2: %i \n", h2);
                    exit(0);
                }
            }
        }
    }
    else if (f1 == 0) //figlio 1
    {
        g1 = fork(); //nipote 1 di f1
        if (g1 == 0)
            exit(0);
        else
        {
            h1 = fork();
            if (h1 == 0)
                exit(0);
            else
            {
                printf("3) processo nipote 1 di F1 con pid: %i \n", g1);
                printf("4) processo nipote 2 di F1 con pid: %i \n", h1);
                waitpid(g1, 0, 0);
                waitpid(h1, 0, 0);
                printf("7) ha terminato N1 di F1: %i \n", g1);
                printf("8) ha terminato N2 di F1: %i \n", h1);
                exit(0);
            }
        }
    }
    return 0;
}