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

int FindNumber(int *arr, int size, int n)
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
        if (FindNumber(arr, i, n) != -1)
            i--;
        else
            arr[i] = n;
    }
}

void CopyArray(int *s, int *d, int size, int startS)
{
    for (int i = 0; i < size; i++)
    {
        // printf("Salvataggio di %d in posizione [%d]\n", s[i - startS], i);
        d[i + startS] = s[i];
    }
}

void CopyArray2(int *s, int *d, int size, int start)
{
    for (int i = start; i < size; i++)
    {
        // printf("Salvataggio di %d in posizione [%d]\n", s[i], i);
        d[i - start] = s[i];
    }
}

int Pari(int n)
{
    if (n % 2 == 0)
        return TRUE;
    return FALSE;
}

void EvenAndOdd(int *arr, int *e, int *o)
{
    int ev = 0, od = 0, last = 99, r = 0;
    int rim[60];
    for (int i = 0; i < SIZE_ARRAY; i++)
    {
        if (Pari(arr[i]) == TRUE && ev < 20)
        {
            e[ev] = arr[i];
            // printf("Numero pari [%d]: %d\n", i, arr[i]);
            ev++;
        }
        else if (r < 60)
        {
            rim[r] = arr[i];
            r++;
        }

        if (Pari(arr[last]) == FALSE && od < 20)
        {
            o[od] = arr[last];
            // printf("Numero dispari [%d]: %d\n", last, arr[last]);
            od++;
            last--;
        }
        else if (r < 60)
        {
            rim[r] = arr[last];
            r++;
            last--;
        }
    }
    Sort(rim, 60, FALSE);
    Sort(o, od, TRUE);
    /*
    PrintArray(rim, 60);
    printf("\n\n\n\n");
    */

    CopyArray(e, arr, ev, 0);
    CopyArray(o, arr, od, ev);
    CopyArray(rim, arr, 60, ev + od);
}

void Integrity(int *arr, int *arr2)
{
    int integrity = 0;
    for (int i = 0; i < SIZE_ARRAY; i++)
    {
        for (int j = 0; j < SIZE_ARRAY; j++)
        {
            if (arr[i] == arr2[j])
                integrity++;
        }
    }
    printf("Integrity: %d%%\n", integrity);
}

int main()
{
    int array[SIZE_ARRAY];
    // int array2[SIZE_ARRAY];
    int even[20];
    int odd[20];
    srand(time(NULL));
    GenArray(array);

    // CopyArray(array, array2, SIZE_ARRAY, 0);

    Sort(array, SIZE_ARRAY, FALSE);
    EvenAndOdd(array, even, odd);
    PrintArray(array, SIZE_ARRAY);
    // PrintArray(array2, SIZE_ARRAY);
    // Integrity(array, array2);
    return 0;
}