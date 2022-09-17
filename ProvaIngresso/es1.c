#include <stdio.h>
#include <stdlib.h>

int main()
{
    int v[5];
    printf("Inserisci 5 numeri\n");
    for (int i = 0; i < 5; i++)
    {
        scanf("%d", &v[i]);
        // printf("Numero inserito: %d\n", v[i]);
        if (v[i] == 0)
            break;
    }
    return 0;
}