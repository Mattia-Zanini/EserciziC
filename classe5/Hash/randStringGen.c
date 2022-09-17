#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define N_STRINGS 1000000
#define MIN_CHARS 3
#define MAX_CHARS 20

#define ASCII_START 32 // 32 è lo spazio
#define ASCII_END 126

#define randnum(min, max) ((rand() % (int)(((max) + 1) - (min))) + (min))

char *generateRandomString(int size)
{
    int i;
    // char *charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
    //  printf("Dimensione del charset: %ld\n", strlen(charset));
    char *res = malloc(size + 1);

    for (i = 0; i < size; i++)
    {
        /*
        int key = randnum(0, 69);
        res[i] = charset[key];
        */
        int key = (rand() % (ASCII_END - ASCII_START)) + ASCII_START;
        res[i] = (char)key;
        if (key == 92 || key == 32 || key == 34)
            i--;
    }
    res[i] = '\0';
    return res;
}

int checkStrings(char *strs[], char *str, int size)
{
    for (int i = 0; i < size; i++)
    {
        /*
        printf("Parola Array in posizione %d: %s\n", i, strs[i]);
        printf("Parola Generata: %s\n", str);
        */
        if (strcmp(strs[i], str) == 0)
            return 1;
    }
    return 0;
}

void wirteOutput(char *outputFile, char *strs[], int size, int isJson)
{
    FILE *output;
    if ((output = fopen(outputFile, "w+")) == NULL)
    {
        printf("errore nell'apertura del file output");
        exit(2);
    }

    if (isJson == 1)
        fprintf(output, "[\n"); // inizio array in json
    for (int i = 0; i < size; i++)
    {
        if (isJson == 1)
            if (i < size - 1)
                fprintf(output, "\"%s\",\n", strs[i]);
            else
                fprintf(output, "\"%s\"\n", strs[i]);
        else
            fprintf(output, "%s\n", strs[i]);
        // printf("i: %d\n", i);
    }
    if (isJson == 1)
        fprintf(output, "]\n"); // fine array in json

    fclose(output);
}

int main()
{
    // printf("Questo è il char 32: '%c'\n\n", 32);
    srand(time(NULL));
    // printf("%d\n", randnum(1, 70));
    int percentage = 0;
    char *strings[N_STRINGS];
    printf("Starting to generate random strings\n\n");
    for (int i = 0; i < N_STRINGS; i++)
    {
        int n = randnum(MIN_CHARS, MAX_CHARS);
        // printf("Numero di lettere estratto: %d\n", n);
        char *str = generateRandomString(n);
        // printf("Parola generata: %s\n", str);
        // sleep(1);
        if (checkStrings(strings, str, i) != 0)
        {
            // printf("find same word\n");
            i--;
        }
        else
            strings[i] = str;
        // if (i >= 10000 && N_STRINGS % i == 0 && ((100 * i) / N_STRINGS) % 10 == 0)
        if (i >= (N_STRINGS / 100) && percentage != (100 * i) / N_STRINGS)
        {
            percentage = (100 * i) / N_STRINGS;
            fputs("\033[A\033[2K", stdout);
            rewind(stdout);
            printf("%d%%\n", percentage); // 1000 : 100 = i : x
        }
        // printf("Parola assegnata: %s\n", strings[i]);
    }
    wirteOutput("output.json", strings, N_STRINGS, 1);
    wirteOutput("output.txt", strings, N_STRINGS, 0);
    printf("End\n");
    return 0;
}