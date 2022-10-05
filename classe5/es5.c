#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

#define randnum(min, max) ((rand() % (int)(((max) + 1) - (min))) + (min)) // genera numeri random in un certo range di valori

/*
Realizzare "array auto-incrementante" di interi, che sia sempre pieno. Dovrà avere le seguenti funzionalità:
- inserisci numero
- verifica numero
- elimina numero
- ordina
*/

void PrintArray(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        printf("[%d]: %d\n", i, arr[i]);
}

void Sort(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (arr[i] > arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void DeleteNumber(int *arr, int pos, int size)
{
    if (size == 0)
        printf("Non puoi accorciare l'array più di così");
    else
    {
        // use for loop to delete the element and update the index
        for (int i = pos; i < size - 1; i++)
        {
            arr[i] = arr[i + 1]; // assign arr[i+1] to arr[i]
        }
        size--;
    }
}

void TestRemoveElements()
{
    size_t oldSize = 10;
    size_t newSize = 9;

    int *arr = malloc(sizeof(int) * oldSize);

    for (int i = 0; (size_t)i < oldSize; i++)
    {
        arr[i] = i;
    }

    for (int i = 0; (size_t)i < oldSize; i++)
    {
        printf("%d ", arr[i]);
    }

    putchar('\n');

    int *tmp = realloc(arr, newSize * sizeof(int));

    if (tmp != NULL)
    {
        arr = tmp;

        for (int i = 0; (size_t)i < newSize; i++)
        {
            printf("%d ", arr[i]);
        }

        putchar('\n');
    }

    free(arr);
}

int main()
{
    return 0;
}