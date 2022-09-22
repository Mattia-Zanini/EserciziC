#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("Questo è il puntatore di argc: %p\n", &argc);

    int *puntatore;
    int pere = 82988273;
    puntatore = &pere;
    int valore = *puntatore;
    printf("Questo è il valore di 'valore': %d\n", valore);
    printf("Puntatore di pere: %p\n", &pere);

    return 0;
}