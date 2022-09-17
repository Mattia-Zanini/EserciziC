#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char p[10];
    char p2[100];
    int somma = 0;
    printf("Scrivi una parola lunga massimo 10 caratteri:\n");
    // scanf("%s", p2);

    for (int i = 0; (p2[i] = getchar()) != '\n'; i++)
        ;
    p2[9] = '\0';
    // printf("Lettera: %s\n", p2);

    int j = 0;
    for (int i = 0; i < strlen(p2); i++)
    {
        printf("Lettera: %c\n", p2[i]);
        if (j == 10)
            break;
        if (p2[i] != ' ' && p2[i] != '\n')
        {
            p[j] = p2[i];
            j++;
        }
    }
    printf("Parola scremata: %s\n", p);

    for (int i = 0; i < 10; i++)
    {
        // printf("Valore del carattere '%c': %d\n", p[i], p[i]);
        somma += p[i];
    }
    printf("Somma: %d\n", somma);

    return 0;
}