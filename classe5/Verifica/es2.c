#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_LENGTH 30

#define MIN_UPPER 65
#define MAX_UPPER 90

#define MIN_LOWER 97
#define MAX_LOWER 122

#define MIN_N 48
#define MAX_N 57

int IsSpecial(char c)
{
    if (c >= 33 && c <= 48 || c >= 58 && c <= 64 || c >= 91 && c <= 96 || c >= 123 && c <= 126)
        return 1;
    return 0;
}

void Sort(char *arr, int size)
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

char *LettereMaiuscole(char *w)
{
    int n = 0;
    for (int i = 0; i < strlen(w); i++)
        if (w[i] >= MIN_UPPER && w[i] <= MAX_UPPER)
            n++;

    char *upper = malloc(n + 1);
    n = 0;
    for (int i = 0; i < strlen(w); i++)
    {
        if (w[i] >= MIN_UPPER && w[i] <= MAX_UPPER)
        {
            upper[n] = w[i];
            n++;
        }
    }
    upper[n] = '\0';
    return upper;
}

char *LettereMinuscole(char *w)
{
    int n = 0;
    for (int i = 0; i < strlen(w); i++)
        if (w[i] >= MIN_LOWER && w[i] <= MAX_LOWER)
            n++;

    char *lower = malloc(n + 1);
    n = 0;
    for (int i = 0; i < strlen(w); i++)
    {
        if (w[i] >= MIN_LOWER && w[i] <= MAX_LOWER)
        {
            lower[n] = w[i];
            n++;
        }
    }
    lower[n] = '\0';
    return lower;
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

char *LettereSpeciali(char *w)
{
    int n = 0;
    for (int i = 0; i < strlen(w); i++)
        if (IsSpecial(w[i]))
            n++;

    char *charS = malloc(n + 1);
    n = 0;
    for (int i = 0; i < strlen(w); i++)
    {
        if (IsSpecial(w[i]))
        {
            charS[n] = w[i];
            n++;
        }
    }
    charS[n] = '\0';
    /*
    for (int i = 0; i < strlen(charS); i++)
        printf("Lettera: %c\n", charS[i]);
    */

    return charS;
}

int main()
{
    char word[WORD_LENGTH];
    /*
    char c = '{';
    printf("Lettera %c valore: %d\n", c, c);
    printf("Lettera %d\n", IsSpecial(c));
    */

    printf("Scrivi una parola\n");
    scanf("%s", word);
    printf("Ecco la tua parola: %s\n", word);

    char *charMaiscuole = LettereMaiuscole(word);
    char *charMinuscole = LettereMinuscole(word);
    char *charNum = LettereNumeriche(word);
    char *charSpec = LettereSpeciali(word);

    Sort(charMaiscuole, strlen(charMaiscuole));
    Sort(charMinuscole, strlen(charMinuscole));
    Sort(charNum, strlen(charNum));
    Sort(charSpec, strlen(charSpec));

    int totalLength = strlen(word);
    char sortWord[totalLength + 1];
    int index = 0;
    for (int i = 0; i < strlen(charMaiscuole); i++)
    {
        sortWord[index] = charMaiscuole[i];
        index++;
    }

    for (int i = 0; i < strlen(charMinuscole); i++)
    {
        sortWord[index] = charMinuscole[i];
        index++;
    }

    for (int i = 0; i < strlen(charNum); i++)
    {
        sortWord[index] = charNum[i];
        index++;
    }

    for (int i = 0; i < strlen(charSpec); i++)
    {
        sortWord[index] = charSpec[i];
        index++;
    }
    sortWord[totalLength] = '\0';

    printf("Ecco la tua parola: %s\n", sortWord);
}