#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

//#define N_STRINGS 1000000
#define N_STRINGS 50
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

int checkStrings(char *strs[18][N_STRINGS], char *str, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Lunghezza stringa: %ld\n", strlen(str));
        // sleep(1);
        printf("Parola Array in posizione %d: %s\n", i, strs[strlen(str) - 3][i]);
        printf("Parola Generata: %s\n", str);

        if (strs[strlen(str) - 3][i] != NULL)
            if (strcmp(strs[strlen(str) - 3][i], str) == 0)
                return 1;
    }
    return 0;
}

void wirteOutput(char *outputFile, char *strs[18][N_STRINGS], int *ss, int isJson)
{
    FILE *output;
    if ((output = fopen(outputFile, "w+")) == NULL)
    {
        printf("errore nell'apertura del file output");
        exit(2);
    }

    if (isJson == 1)
        fprintf(output, "[\n"); // inizio array in json
    for (int j = 0; j < 18; j++)
    {
        for (int i = 0; i < ss[j]; i++)
        {
            if (isJson == 1)
                if (i < ss[j] - 1)
                    fprintf(output, "\"%s\",\n", strs[j][i]);
                else
                    fprintf(output, "\"%s\"\n", strs[j][i]);
            else
                fprintf(output, "%s\n", strs[j][i]);
            // printf("i: %d\n", i);
        }
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
    int sizes[18] = {0};

    // char *strings[18][N_STRINGS];
    char *(*strings)[N_STRINGS];

    strings = calloc(18, sizeof *strings);

    if (strings == NULL)
    {
        fprintf(stderr, "Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }

    printf("Starting to generate random strings\n\n");
    for (int i = 0; i < N_STRINGS; i++)
    {
        int n = randnum(MIN_CHARS, MAX_CHARS);
        // printf("Numero di lettere estratto: %d\n", n);
        char *str = generateRandomString(n);
        // printf("Parola generata: %s\n", str);
        // sleep(1);
        if (checkStrings(strings, str, sizes[strlen(str) - 3]) != 0)
        {
            // printf("find same word\n");
            i--;
        }
        else
        {
            strings[strlen(str) - 3][i] = str;
            sizes[strlen(str) - 3]++;
        }
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

    printf("Ecco quante parole sono state scritte\n");
    for (int i = 0; i < 18; i++)
        printf("%d\n", sizes[i]);

    // wirteOutput("output2.json", strings, sizes, 1);
    wirteOutput("output2.txt", strings, sizes, 0);
    printf("End\n");
    free(strings);
    return 0;
}