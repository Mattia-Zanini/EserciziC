/*
Questo codice utilizza la funzione realloc per creare un array dinamico che può crescere di dimensione ogni volta che l'utente inserisce un nuovo numero. L'utente continua ad immettere numeri fino a quando non inserisce 0, e alla fine del programma vengono stampati tutti i numeri immessi. La funzione free() viene utilizzata per liberare la memoria allocata per l'array dinamico alla fine del programma.
*/

/* realloc example: rememb-o-matic */
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int input, n;        // input è il numero immesso dall'utente, n è un contatore utilizzato per il ciclo successivo
  int count = 0;       // count tiene traccia del numero di elementi nell'array numbers
  int *numbers = NULL; // numbers è l'array dinamico che contiene i numeri immessi dall'utente

  do
  {
    printf("Enter an integer value (0 to end): ");
    scanf("%d", &input);                                    // chiede all'utente di inserire un numero
    count++;                                                // incrementa il numero di elementi nell'array
    numbers = (int *)realloc(numbers, count * sizeof(int)); // utilizza la funzione realloc per aumentare la dimensione dell'array dinamico
    if (numbers == NULL)                                    // controlla se l'allocazione della memoria è andata a buon fine
    {
      puts("Error (re)allocating memory"); // stampa un errore se l'allocazione non è andata a buon fine
      exit(1);
    }
    numbers[count - 1] = input; // assegna l'input immesso dall'utente all'ultima posizione dell'array
  } while (input != 0);         // ripete queste istruzioni finché l'input non è 0

  printf("Numbers entered: ");
  for (n = 0; n < count; n++)
    printf("%d ", numbers[n]); // stampa tutti i numeri immessi dall'utente
  free(numbers);               // libera la memoria allocata per l'array dinamico
  printf("\n");
  return 0;
}