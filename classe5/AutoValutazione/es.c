#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE_ARRAY 100
#define MIN 0
#define MAX 80

#define randnum(min, max) ((rand() % (int)(((max) + 1) - (min))) + (min)) // genera numeri random in un certo range di valori

typedef struct
{
    int nOccurence;
    int number;
} Occurence_t;

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

void GenArray(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        arr[i] = randnum(MIN, MAX);
}

int FindNumber(int *arr, int n, int size)
{
    for (int i = 0; i < size; i++)
        if (arr[i] == n)
            return i;
    return -1;
}

void ShiftNumberLastPosition(int *arr, int pos, int size)
{
    if (size == 0)
        printf("Non puoi accorciare l'array più di così");
    else
        // sposta l'elmento in una certa posizione nell'ultima posizione dell'array
        for (int i = pos; i < size - 1; i++)
            arr[i] = arr[i + 1];
}

void ResizeArray(int *arr, int newSize)
{
    int *tmp = realloc(arr, newSize * sizeof(int));
    if (tmp != NULL)
        arr = tmp;
    else if (tmp != NULL && newSize != 0)
        printf("Errore durante il ridimensionamento dell'array");
}

void ResizeOccurence(Occurence_t *arr, int newSize)
{
    Occurence_t *tmp = realloc(arr, newSize * sizeof(Occurence_t));
    if (tmp != NULL)
        arr = tmp;
    else if (tmp != NULL && newSize != 0)
        printf("Errore durante il ridimensionamento dell'array");
}

void DeleteNumber(int *arr, int *size, int n)
{
    int pos = FindNumber(arr, n, *size);
    if (pos == -1)
    {
        // printf("Il numero non c'è\n");
    }
    else
    {
        // printf("Numero trovato in posizione: %d\n", pos);
        ShiftNumberLastPosition(arr, pos, *size);
        (*size)--;
        ResizeArray(arr, *size);
    }
}

Occurence_t *FindOccurence(int *arr, int size, int *sizeFinded)
{
    Occurence_t *occ = malloc(sizeof(Occurence_t) * SIZE_ARRAY);
    occ[*sizeFinded].nOccurence = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == arr[i + 1])
            occ[*sizeFinded].nOccurence++;
        else if (arr[i] != arr[i + 1] && occ[*sizeFinded].nOccurence > 0)
        {
            // printf("'%d' occorrenze trovate: %d\n", arr[i], occ[*sizeFinded].nOccurence + 1);
            occ[*sizeFinded].nOccurence++;
            occ[*sizeFinded].number = arr[i];
            (*sizeFinded)++;
            // printf("Nuovo ridimensionamento %d\n", *sizeFinded);
            // ResizeOccurence(occ, *sizeFinded);
            occ[*sizeFinded].nOccurence = 0;
        }
    }
    return occ;
}

void CountOccurence(int *arr, int size)
{
    int occ = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == arr[i + 1])
            occ++;
        else if (arr[i] != arr[i + 1] && occ > 0)
        {
            printf("'%d' occorrenze trovate: %d\n", arr[i], occ + 1);
            occ = 0;
        }
    }
}

int main()
{
    int size = SIZE_ARRAY;
    int *array = malloc(sizeof(int) * size);
    srand(time(NULL));
    GenArray(array, size);
    Sort(array, size);
    // PrintArray(array, size);

    CountOccurence(array, size);

    int sizeFind = 0;
    Occurence_t *occorrenze = FindOccurence(array, size, &sizeFind);

    printf("Occorrenze trovate: %d\n", sizeFind);

    for (int i = 0; i < sizeFind; i++)
    {
        for (int j = 0; j < occorrenze[i].nOccurence; j++)
        {
            // printf("Occorrenze trovate per %d: %d\n", occorrenze[i].number, occorrenze[i].nOccurence);
            DeleteNumber(array, &size, occorrenze[i].number);
        }
    }
    // PrintArray(array, size);
    free(occorrenze);

    for (int i = size - 1; i >= 0; i--)
        if (array[i] % 2 == 0)
            printf("Pari %d\n", array[i]);

    printf("\n\n");

    for (int i = 0; i < size; i++)
        if (array[i] % 2 != 0)
            printf("Dispari %d\n", array[i]);

    return 0;
}