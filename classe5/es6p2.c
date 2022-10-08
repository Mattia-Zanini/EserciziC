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

void Sort(int *arr, int size, int reverse)
{
    if (reverse == FALSE)
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
    else
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

int Sort1(int *arr, int *e, int *o)
{
    int ev = 0, od = 0;
    for (int i = 0; i < 40; i++)
    {
        if (arr[i] % 2 == 0 && ev < 20)
        {
            e[ev] = arr[i];
            ev++;
        }
    }
}

int main()
{
    int array[SIZE_ARRAY];
    int even[20];
    int odd[20];
    srand(time(NULL));
    GenArray(array);
    Sort(array, SIZE_ARRAY, FALSE);
    PrintArray(array, SIZE_ARRAY);
    return 0;
}