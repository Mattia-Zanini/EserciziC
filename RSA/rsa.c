/*
 * C program to Implement the RSA Algorithm
 */

#include <stdio.h> // Libreria per input/output standard
// #include <conio.h> // Libreria per gestire gli oggetti dell'interfaccia utente
#include <curses.h> // Libreria per gestire gli oggetti dell'interfaccia utente
// Aggiungere "-lcurses" quando si compila il codice (arm64)

#include <stdlib.h> // Libreria standard per la gestione di memoria dinamica
#include <math.h>   // Libreria per le funzioni matematiche
#include <string.h> // Libreria per le operazioni su stringhe

long int p, q, n, t, flag, e[100], d[100], temp[100], j, m[100], en[100], i;
char msg[100];

int prime(long int);
void ce();
long int cd(long int);
void encrypt();
void decrypt();

int main()
{
    printf("\nENTER FIRST PRIME NUMBER\n"); // Richiede in input il primo numero primo
    scanf("%d", &p);
    flag = prime(p); // Controlla se il numero in input è primo
    if (flag == 0)
    {
        printf("\nWRONG INPUT\n"); // Se il numero non è primo, termina il programma
        getch();
        exit(1);
    }
    printf("\nENTER ANOTHER PRIME NUMBER\n"); // Richiede in input il secondo numero primo
    scanf("%d", &q);
    flag = prime(q); // Controlla se il numero in input è primo
    if (flag == 0 || p == q)
    {
        printf("\nWRONG INPUT\n"); // Se il numero non è primo oppure è uguale al primo, termina il programma
        getch();
        exit(1);
    }
    printf("\nENTER MESSAGE\n"); // Richiede in input il messaggio da criptare
    fflush(stdin);
    scanf("%s", msg);
    for (i = 0; msg[i] != NULL; i++)
        m[i] = msg[i];     // Copia il messaggio in un array di interi
    n = p * q;             // Calcola il prodotto dei due numeri primi
    t = (p - 1) * (q - 1); // Calcola il valore di totient di n
    ce();                  // Calcola i valori di e e d
    printf("\nPOSSIBLE VALUES OF e AND d ARE\n");
    for (i = 0; i < j - 1; i++)
        printf("\n%ld\t%ld", e[i], d[i]); // Stampa i valori di e e d
    encrypt();                            // Cripta il messaggio
    decrypt();                            // Decripta il messaggio
}

int prime(long int pr) // Funzione che verifica se un numero è primo
{
    int i;
    j = sqrt(pr); // Calcola la radice quadrata del numero
    for (i = 2; i <= j; i++)
    {
        if (pr % i == 0)
            return 0; // Se il numero è divisibile per un altro numero diverso da 1 e se stesso, non è primo
    }
    return 1;
}
// Funzione per calcolare i valori di e e d
void ce()
{
    int k;
    k = 0;
    for (i = 2; i < t; i++)
    {
        if (t % i == 0)
            continue;
        flag = prime(i);
        if (flag == 1 && i != p && i != q)
        {
            e[k] = i;
            flag = cd(e[k]);
            if (flag > 0)
            {
                d[k] = flag;
                k++;
            }
            if (k == 99)
                break;
        }
    }
}

// Funzione per calcolare il valore di d
long int cd(long int x)
{
    long int k = 1;
    while (1)
    {
        k = k + t;
        if (k % x == 0)
            return (k / x);
    }
}
void encrypt()
{
    long int pt, ct, key = e[0], k, len;
    i = 0;
    len = strlen(msg); // Calcola la lunghezza del messaggio da cifrare
    while (i != len)   // Itera finché non si è cifrato ogni carattere del messaggio
    {
        pt = m[i];    // Prende il carattere in posizione i del messaggio
        pt = pt - 96; // Sottrae 96 dal valore ASCII del carattere
        k = 1;
        for (j = 0; j < key; j++) // Esegue l'elevamento a potenza modulo n
        {
            k = k * pt;
            k = k % n;
        }
        temp[i] = k; // Salva il risultato dell'elevamento a potenza in un array temporaneo
        ct = k + 96; // Aggiunge 96 al risultato per ottenere il carattere cifrato
        en[i] = ct;  // Salva il carattere cifrato in un array di caratteri cifrati
        i++;         // Incrementa l'indice per il prossimo carattere del messaggio
    }
    en[i] = -1; // Aggiunge un carattere nullo alla fine dell'array di caratteri cifrati
    printf("\nTHE ENCRYPTED MESSAGE IS\n");
    for (i = 0; en[i] != -1; i++) // Stampa ogni carattere cifrato
        printf("%c", en[i]);
}

void decrypt()
{
    long int pt, ct, key = d[0], k;
    i = 0;
    while (en[i] != -1) // Itera finché non si è decrittato ogni carattere cifrato
    {
        ct = temp[i]; // Prende il valore dell'elevamento a potenza precedentemente salvato
        k = 1;
        for (j = 0; j < key; j++) // Esegue l'elevamento a potenza modulo n inverso
        {
            k = k * ct;
            k = k % n;
        }
        pt = k + 96; // Aggiunge 96 al risultato per ottenere il carattere originale
        m[i] = pt;   // Salva il carattere originale in un array di caratteri del messaggio originale
        i++;         // Incrementa l'indice per il prossimo carattere cifrato
    }
    m[i] = -1; // Aggiunge un carattere nullo alla fine dell'array di caratteri del messaggio originale
    printf("\nTHE DECRYPTED MESSAGE IS\n");
    for (i = 0; m[i] != -1; i++) // Stampa ogni carattere del messaggio originale
        printf("%c", m[i]);
}

void SecureScanF(char msg[], int *number)
{
    int flag = 0, result;
    char buff[32];

    do
    {
        printf("%s", msg);
        scanf("%s", buff);
        if ((result = atoi(buff)) != 0)
            // if (IsPrime(result))
            flag = 1;
    } while (flag != 1);

    *number = result;
    // printf("Risultato: %d\n", result);
}