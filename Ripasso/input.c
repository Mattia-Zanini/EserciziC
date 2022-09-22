#include <stdio.h>

void Ciao()
{
    printf("Ciao\n");
}

int Valore()
{
    return 5;
}

int main()
{
    Ciao();
    int n = Valore();
    printf("Questo è il valore ritornato%d\n", n);
    return 0;
}