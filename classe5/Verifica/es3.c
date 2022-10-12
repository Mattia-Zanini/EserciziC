#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_LENGTH 30

#define MIN_N 48
#define MAX_N 57

void Sort(int *arr, int size, int noReverse)
{
    if (noReverse == 1)
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

char *LettereNumeriche(char *w)
{
    int n = 0;
    for (int i = 0; i < strlen(w); i++)
        if (w[i] >= MIN_N && w[i] <= MAX_N)
            n++;

    char *charN = malloc(n + 1);
    n = 0;
    for (int i = 0; i < strlen(w); i++)
    {
        if (w[i] >= MIN_N && w[i] <= MAX_N)
        {
            charN[n] = w[i];
            n++;
        }
    }
    charN[n] = '\0';
    return charN;
}

void ArrayNumPari(char *w)
{
    int n = 0, num = 0;
    for (int i = 0; i < strlen(w); i++)
    {
        num = (w[i] - 48);
        if (num % 2 == 0)
            n++;
    }

    int *numbers = malloc(n + 1);
    n = 0;

    for (int i = 0; i < strlen(w); i++)
    {
        num = (w[i] - 48);
        if (num % 2 == 0)
        {
            numbers[n] = num;
            n++;
        }
    }

    Sort(numbers, n, 1);
    printf("Numeri pari\n");
    for (int i = 0; i < n; i++)
        printf("[%d]: %d\n", i, numbers[i]);
}

void ArrayNumDisp(char *w)
{
    int n = 0, num = 0;
    for (int i = 0; i < strlen(w); i++)
    {
        num = (w[i] - 48);
        if (num % 2 != 0)
            n++;
    }

    int *numbers = malloc(n + 1);
    n = 0;

    for (int i = 0; i < strlen(w); i++)
    {
        num = (w[i] - 48);
        if (num % 2 != 0)
        {
            numbers[n] = num;
            n++;
        }
    }
    Sort(numbers, n, 0);
    printf("Numeri dispari\n");

    for (int i = 0; i < n; i++)
        printf("[%d]: %d\n", i, numbers[i]);
}

int main()
{
    char word[WORD_LENGTH];

    printf("Scrivi una parola\n");
    scanf("%s", word);
    printf("Ecco la tua parola: %s\n", word);

    char *charNum = LettereNumeriche(word);
    ArrayNumPari(charNum);
    ArrayNumDisp(charNum);
}