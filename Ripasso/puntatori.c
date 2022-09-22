#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("Questo è il puntatore di argc: %p\n", &argc);

    int *puntatore = &argc;
    int pere = 82988273;
    puntatore = &pere;
    int valore = *puntatore;
    printf("Questo è il valore di 'valore': %d\n", valore);
    prova();

    return 0;
}