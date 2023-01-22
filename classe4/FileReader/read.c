/*
Il codice sopra è un programma in C che accetta tre argomenti dalla riga di comando: il file di input,
il file di output e un flag (-c o -p) che indica se il programma deve cercare un carattere o una parola
specifica all'interno del file di input.

La prima parte del codice crea due stringhe, fileInput e fileOutput, per memorizzare il nome del file di
input e del file di output passati come argomenti. Viene poi stampato a video il nome dei due file per mostrare
all'utente quali file verranno utilizzati.

La funzione strcmp(argv[3], "-c") verifica se il flag passato come terzo argomento è "-c", che indica che il
programma deve cercare un carattere specifico. In caso positivo, il programma apre il file di input in modalità
di lettura ("r"). Utilizza la funzione fgetc() per leggere il file carattere per carattere e confronta ogni
carattere con quello specificato come quarto argomento. Se il carattere corrisponde, la variabile find viene
incrementata. La funzione fgetc() restituisce EOF (end of file) quando raggiunge la fine del file, il ciclo while
termina e il file di input viene chiuso.

Il programma apre quindi il file di output in modalità di scrittura e sovrascrittura ("w+") e utilizza la funzione
fprintf() per scrivere il numero di caratteri trovati nel file di output. Il file di output viene quindi chiuso e
viene stampato a video il numero di caratteri trovati.

Se il flag passato come terzo argomento non è "-c", il programma esegue lo stesso processo per cercare una parola
specifica. In questo caso, utilizza un contatore streak per tenere traccia del numero di caratteri della parola
trovati consecutivamente e se streak raggiunge la lunghezza della parola da cercare, la variabile find viene incrementata.
Alla fine del processo, il programma scrive il numero di parole trovate nel file di output e lo chiude.
*/

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  FILE *in_File;
  int find = 0;
  // legge i file che sono nella stessa cartella
  char fileInput[strlen(argv[1])];
  strcpy(fileInput, argv[1]);
  printf("Questo e' il file input da cercare: %s\n", fileInput);

  char fileOutput[strlen(argv[2])];
  strcpy(fileOutput, argv[2]);
  printf("Questo e' il file ouput da cercare: %s\n", fileOutput);

  if (strcmp(argv[3], "-c") == 0)
  {
    in_File = fopen(fileInput, "r");
    char tmpChar, toFind = argv[4][0];
    if (in_File != NULL)
    { // quando trova il file
      printf("File di input trovato e aperto\n");
      while (1)
      {
        tmpChar = fgetc(in_File);
        if (tmpChar == toFind)
        {
          find++;
        }
        else if (tmpChar == EOF)
        {
          break;
        }
      }
    }
    else // quando non trova il file
    {
      printf("File di input non trovato\n");
    }
    printf("File di input chiuso\n");
    fclose(in_File);
    // file di uscita
    FILE *out_File = fopen(fileOutput, "w+"); // write + overwrite
    if (out_File != NULL)
    { // quando trova il file
      printf("File di output trovato e aperto\n");
    }
    else // quando non trova il file
    {
      printf("File di output non trovato\n");
    }
    fprintf(
        out_File,
        "Nel file sono stati trovati %d caratteri che corrispondono a '%c'\n",
        find, toFind);
    fclose(out_File);
    printf("File di output chiuso\n");
    printf("Sono stati trovati: %d caratteri uguali a quello da cercare\n",
           find);
  }
  else if (strcmp(argv[3], "-p") == 0)
  {
    in_File = fopen(fileInput, "r");
    long stringLength = strlen(argv[4]);
    int streak = 0;
    char tmpChar, toFind[stringLength];
    printf("La parola da cercare e' lunga: %ld caratteri\n", stringLength);
    strcpy(fileInput, argv[4]);
    if (in_File != NULL)
    { // quando trova il file
      printf("File di input trovato e aperto\n");
      while (1)
      {
        tmpChar = fgetc(in_File);
        if (tmpChar == fileInput[streak])
        {
          streak++;
        }
        else if (tmpChar == EOF)
        {
          break;
        }
        else
        {
          streak = 0;
        }
        if (streak ==
            stringLength -
                1) // perchè in stringLenght è stato conteggiato anche '\0'
        {
          find++;
          streak = 0;
        }
      }
      printf("Stringa da cercare: %s\n", argv[4]);
    }
    else // quando non trova il file
    {
      printf("File di input non trovato\n");
    }
    printf("File di input chiuso\n");
    fclose(in_File);
    // file di uscita
    FILE *out_File = fopen(fileOutput, "w+"); // write + overwrite
    if (out_File != NULL)
    { // quando trova il file
      printf("File di output trovato e aperto\n");
    }
    else // quando non trova il file
    {
      printf("File di output non trovato\n");
    }
    fprintf(out_File,
            "Nel file sono state trovate %d parole che corrispondono a '%s'\n",
            find, argv[4]);
    fclose(out_File);
    printf("File di output chiuso\n");
    printf("Sono stati trovate: %d parole uguali a quella da cercare\n", find);
  }
  return 0;
}