#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define SIZE_ARRAY 50
#define MIN 0
#define MAX 100
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

void GenArray(int *arr)
{
    for (int i = 0; i < SIZE_ARRAY; i++)
    {
        arr[i] = randnum(MIN, MAX);
    }
}

void PrintArray(int *arr, int reverse)
{
    if(reverse == 0){
      for (int i = 0; i < SIZE_ARRAY; i++)
    {
        printf("[%d]: %d\n", i, arr[i]);
    }
    }
    else if(reverse == 1){
      for (int i = SIZE_ARRAY - 1; i >= 0; i--)
    {
        printf("[%d]: %d\n", i, arr[i]);
    }
    }
}

int main()
{
    int r;
    int array[SIZE_ARRAY];
    srand(time(NULL));
    GenArray(array);

    while (1)
    {
        char risp;
        printf("1) Stampa degli elementi array\n");
        printf("2) Stampa inversa degli elementi dell’array\n");
        printf("3) Stampa tutti i numeri pari\n");
        printf("4) Stampa tutti i numeri dispari\n");
        printf("5) Ricerca di un numero nell’array (letto in input)\n");
        printf("6) Eliminare un elemento dell’array (se esistente)\n");
        printf("7) Alternare (o scambiare ) a due a due le posizioni del vettore\n");
        printf("8) Ordinamento del vettore (ordinamento a scelta)\n");
        printf("9) Esci\n");

        printf("Seleziona: ");
        scanf("%c", &risp);
        int n = atoi(&risp);
        if (n == 9)
            break;

        switch (n)
        {
        case 1:
            PrintArray(array, 0);
            break;
        case 2:
            PrintArray(array, 1);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        }
        /*sleep(1);
        printf("Press Any Key to Continue\n");
        getc(stdin);
        */
        printf("\e[1;1H\e[2J"); // pulisce tutto il terminale
    }
}
