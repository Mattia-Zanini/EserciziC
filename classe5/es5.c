#include <stdio.h>
#include <stdlib.h>

/*
Realizzare "array auto-incrementante" di interi, che sia sempre pieno. Dovrà avere le seguenti funzionalità:
- inserisci numero
- verifica numero
- elimina numero
- ordina
*/

void PrintArray(int *arr, int *size)
{
    for (int i = 0; i < *size; i++)
        printf("[%d]: %d\n", i, arr[i]);
}

void Sort(int *arr, int *size)
{
    for (int i = 0; i < *size; i++)
    {
        for (int j = i + 1; j < *size; j++)
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

void ShiftNumberLastPosition(int *arr, int pos, int *size)
{
    if (*size == 0)
        printf("Non puoi accorciare l'array più di così");
    else
        // sposta l'elmento in una certa posizione nell'ultima posizione dell'array
        for (int i = pos; i < *size - 1; i++)
            arr[i] = arr[i + 1];
}

int FindNumber(int *arr, int n, int *size)
{
    for (int i = 0; i < *size; i++)
        if (arr[i] == n)
            return i;

    return -1;
}

void ResizeArray(int *arr, int newSize)
{
    int *tmp = realloc(arr, newSize * sizeof(int));

    if (tmp != NULL)
        arr = tmp;
    else if (tmp != NULL && newSize != 0)
        printf("Errore durante il ridimensionamento dell'array");
}

void DeleteNumber(int *arr, int *size, int n)
{
    int pos = FindNumber(arr, n, size);
    if (pos == -1)
        printf("Il numero non c'è\n");
    else
    {
        ShiftNumberLastPosition(arr, pos, size);
        (*size)--;
        ResizeArray(arr, *size);
    }
}

void InsertNumber(int *arr, int *size, int n)
{
    (*size)++;
    ResizeArray(arr, *size);
    arr[*size - 1] = n;
}

int main()
{
    int size = 0;
    int *arr = (int *)malloc(sizeof(int) * size);

    while (1)
    {
        char risp[1];
        printf("1) Inserisci numero\n");
        printf("2) Verifica numero\n");
        printf("3) Elimina numero\n");
        printf("4) Ordina\n");
        printf("5) Visualizza tutti i numeri\n");
        printf("6) Esci\n");

        printf("Seleziona: ");
        scanf("%s", risp);
        int n = atoi(risp);

        if (n == 6)
            break;

        int num = 0;
        switch (n)
        {
        case 1:
            printf("Inserisci un numero: ");
            scanf("%d", &num);
            InsertNumber(arr, &size, num);
            break;
        case 2:
            printf("Inserisci un numero: ");
            scanf("%d", &num);
            int p = FindNumber(arr, num, &size);
            if (p == -1)
                printf("Non trovato\n");
            else
                printf("Il numero è stato trovato in posizione: [%d]\n", p);
            break;
        case 3:
            printf("Inserisci un numero: ");
            scanf("%d", &num);
            DeleteNumber(arr, &size, num);
            break;
        case 4:
            Sort(arr, &size);
            break;
        case 5:
            PrintArray(arr, &size);
            break;
        }
        printf("\n\n");
    }

    if (size != 0)
        free(arr);
    return 0;
}