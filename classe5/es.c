#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define SIZE_ARRAY 101
#define MIN 0
#define MAX 101

#define TRUE 1
#define FALSE 0

#define randnum(min, max) ((rand() % (int)(((max) + 1) - (min))) + (min)) // genera numeri random in un certo range di valori

/*
Scrivere un programma in C che gestica, attraverso un menù, le seguenti operazione sugli array:
1) Stampa degli elementi array;
2) Stampa inversa degli elementi dell’array;
3) Stampa tutti i numeri pari;
4) Stampa tutti i numeri dispari;
5) Ricerca di un numero nell’array (letto in input);
6) Eliminare un elemento dell’array (se esistente);
7) Alternare (o scambiare ) a due a due le posizioni del vettore: esempio
vettore: 1,2,3,4 vettore alternato: 2,1,4,3 (attenzione se lungo dispari);
8) Ordinamento del vettore (ordinamento a scelta).
*/

void PrintArray(int *arr, int reverse)
{
    if (reverse == FALSE)
        for (int i = 0; i < SIZE_ARRAY; i++)
            printf("[%d]: %d\n", i, arr[i]);

    else if (reverse == TRUE)
        for (int i = SIZE_ARRAY - 1; i >= 0; i--)
            printf("[%d]: %d\n", i, arr[i]);
}

void PrintNumbers(int *arr, int even)
{
    int n = 2;

    for (int i = 0; i < SIZE_ARRAY; i++)
    {
        if (even == FALSE && arr[i] % n != 0)
            printf("[%d]: %d\n", i, arr[i]);

        else if (even == TRUE && arr[i] % n == 0)
            printf("[%d]: %d\n", i, arr[i]);
    }
}

int FindNumber(int *arr, int n, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == n)
        {
            // printf("Trovato numero uguale a posizione [%d]\n", i);
            return i;
        }
    }
    return -1;
}

void Sort(int *arr)
{
    for (int i = 0; i < SIZE_ARRAY; i++)
    {
        for (int j = i + 1; j < SIZE_ARRAY; j++)
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

void SwitchValue(int *arr)
{
    for (int i = 0; i < SIZE_ARRAY; i += 2)
    {
        /*
        printf("Questo è i: %d\n", i);
        printf("Questo è arr[i]: %d\n", arr[i]);
        printf("Questo è arr[i + 1]: %d\n", arr[i + 1]);
        */

        if (i + 1 >= SIZE_ARRAY)
            break;
        int temp = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = temp;
    }
}

void GenArray(int *arr)
{
    for (int i = 0; i < SIZE_ARRAY; i++)
    {
        arr[i] = randnum(MIN, MAX);
        if (FindNumber(arr, arr[i], i) != -1)
            i--;
    }
}

void DeleteNumber(int *arr, int pos, int nR)
{
    // use for loop to delete the element and update the index
    for (int i = pos; i < SIZE_ARRAY - 1; i++)
    {
        arr[i] = arr[i + 1]; // assign arr[i+1] to arr[i]
    }

    int *tmp;
    tmp = realloc(arr, SIZE_ARRAY - 1 * sizeof(int));
    free(arr);
    arr = tmp;
    sleep(10);
}

int main()
{
    int r;
    // int array[SIZE_ARRAY];
    int *array = malloc(SIZE_ARRAY * sizeof(int));
    int nRemoved = 0;
    srand(time(NULL));
    GenArray(array);

    while (1)
    {
        char risp[1];
        printf("1) Stampa degli elementi array\n");
        printf("2) Stampa inversa degli elementi dell’array\n");
        printf("3) Stampa tutti i numeri pari\n");
        printf("4) Stampa tutti i numeri dispari\n");
        printf("5) Ricerca di un numero nell’array (letto in input)\n");
        printf("6) Eliminare un elemento dell’array (se esistente)\n");
        printf("7) Alternare (o scambiare ) a due a due le posizioni del vettore\n");
        printf("8) Ordinamento del vettore (ordinamento a scelta)\n");
        printf("9) Esci\n\n");

        printf("Seleziona: ");
        scanf("%s", risp);
        int n = atoi(risp);
        if (n == 9)
            break;

        int num = 0;
        switch (n)
        {
        case 1:
            PrintArray(array, FALSE);
            break;
        case 2:
            PrintArray(array, TRUE);
            break;
        case 3:
            PrintNumbers(array, TRUE);
            break;
        case 4:
            PrintNumbers(array, FALSE);
            break;
        case 5:
            printf("Inserisci un numero: ");
            scanf("%d", &num);
            if (FindNumber(array, num, SIZE_ARRAY) != -1)
                printf("Il numero c'è\n");
            else
                printf("Il numero non c'è\n");
            break;
        case 6:
            printf("Inserisci un numero: ");
            scanf("%d", &num);
            int pos = FindNumber(array, num, SIZE_ARRAY);
            if (pos != -1)
            {
                printf("Il numero c'è\n");
                DeleteNumber(array, pos, nRemoved);
            }
            else
                printf("Il numero non c'è\n");
            break;
        case 7:
            SwitchValue(array);
            break;
        case 8:
            Sort(array);
            break;
        }
        sleep(1);
        printf("\n\n\n");
    }
    free(array);
}

// A utility function to get maximum value in arr[]
int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort(int arr[], int n, int exp)
{
    int output[n]; // output array
    int i, count[10] = {0};

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

// The main function to that sorts arr[] of size n using
// Radix Sort
void radixsort(int arr[], int n)
{
    // Find the maximum number to know number of digits
    int m = getMax(arr, n);

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}