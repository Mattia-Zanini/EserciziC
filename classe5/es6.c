#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
- Generare un array di 100 numeri casuali, contenente numeri casuali interi positivi, da 1 a 233, non ripetuti.
- Ordinare, dalla posizione 0 alla posizione 19, i primi numeri interi positivi pari, dopo aver verificato che
  siano almeno 20. Se non lo sono ridurre la posizione massima.
- Ordinare, dalla posizione 20 alla posizione 39, in ordine decrescente, gli ultimi numeri dispari,
  dopo aver verificato che siano almeno 20. Se non lo sono ridurre la posizione massima.
- Gli altri numeri, quelli dalla posizione 40 alle 99, dovranno essere ordinati in modo crescente.
*/

#define SIZE_ARRAY 100
#define MIN 1
#define MAX 233

#define TRUE 1
#define FALSE 0

#define randnum(min, max) ((rand() % (int)(((max) + 1) - (min))) + (min)) // genera numeri random in un certo range di valori

void Sort(int *arr, int size, int start)
{
    for (int i = start; i < size; i++)
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

void ReverseSort(int *arr, int size)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = i + 1; j < size; ++j)
        {
            if (arr[i] < arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void PrintArray(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        printf("[%d]: %d\n", i, arr[i]);
}

int FindNumber(int *arr, int n)
{
    for (int i = 0; i < SIZE_ARRAY; i++)
        if (arr[i] == n)
            return i;

    return -1;
}

void GenArray(int *arr)
{
    for (int i = 0; i < SIZE_ARRAY; i++)
    {
        int n = randnum(MIN, MAX);
        if (FindNumber(arr, n) != -1)
            i--;
        else
            arr[i] = n;
    }
}

void CopyArray(int *s, int *d, int size, int start, int startS)
{
    for (int i = start; i < size; i++)
    {
        // printf("Salvataggio di %d in posizione [%d]\n", s[i - startS], i);
        d[i] = s[i - startS];
    }
}

void Sort1(int *arr)
{
    int temp[20], nEven = 0, nDispari = 0;
    for (int i = 0; i < 20; i++)
    {
        if (arr[i] % 2 == 0)
        {
            temp[nEven] = arr[i];
            // printf("Salvataggio di %d in posizione [%d]\n", arr[i], nEven);
            nEven++;
        }
        else
        {
            temp[20 - 1 - nDispari] = arr[i];
            // printf("Salvataggio di %d in posizione [%d]\n", arr[i], (20 - 1 - nDispari));
            nDispari++;
        }
    }
    Sort(temp, nEven, 0);
    CopyArray(temp, arr, 20, 0, 0);
}

void Sort2(int *arr)
{
    int temp[20], nEven = 0, nDispari = 0;
    for (int i = 20; i < 40; i++)
    {
        if (arr[i] % 2 != 0)
        {
            temp[nDispari] = arr[i];
            // printf("Salvataggio di %d in posizione [%d]\n", arr[i], nDispari);
            nDispari++;
        }
        else
        {
            temp[20 - 1 - nEven] = arr[i];
            // printf("Salvataggio di %d in posizione [%d]\n", arr[i], (20 - 1 - nEven));
            nEven++;
        }
    }
    ReverseSort(temp, nDispari);
    CopyArray(temp, arr, 40, 20, 20);
}

int main()
{
    int array[SIZE_ARRAY];
    srand(time(NULL));
    GenArray(array);
    Sort1(array);
    Sort2(array);
    Sort(array, SIZE_ARRAY, 40);
    PrintArray(array, SIZE_ARRAY);
    return 0;
}