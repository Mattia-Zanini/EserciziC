#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    char p[10];
    int somma = 0;
    printf("Scrivi una parola lunga massimo 10 caratteri:\n");
    // scanf("%s", p);
    scanf("%10[0-9a-zA-Z ]", p);
    for (int i = 0; i < 10; i++)
    {
        p[i] = tolower(p[i]);
        somma += p[i];
    }
    printf("Ecco la parola: %s\n", p);
    printf("Somma: %d\n", somma);
    return 0;
}