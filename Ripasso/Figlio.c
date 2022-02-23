#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// GENERAZIONE FIGLIO
/*int main() {
  int figlio;
  int prova = 1;
  figlio = fork();   // genero il processo figlio
  if (figlio == 0) { // figlio
    printf("Ciao sono il processo figlio\n");
    prova = prova + 5; // = 6
    printf("%d\n", prova);
    exit(0);
  } else if (figlio > 0) { // padre
    wait(&figlio);
    printf("Ciao sono il processo padre\n");
    printf("%d\n", prova);   // = 1
  } else if (figlio == -1) { // errore Il figlio non viene generato
    printf("Errore durante la generazione del processo figlio\n");
  }
  return 0;
}*/

// ARGV E ARGC
// arg = argument
// v = value -- > valore
// c = count --> numero
/*int main(int argc, char *argv[]) {
  for (int i = 0; i < argc; i++) {
    printf("%s\n", argv[i]);
  }
  printf("Ci sono %d argomenti\n", argc);
  if (argc == 3) {
    printf("Il tuo nome è: %s\nIl tuo cognome è: %s", argv[1], argv[2]);
  } else {
    printf("Argomenti errati");
  }
  return 0;
}*/

// close & file descriptor & dup
/*int main() {
  int piped[2];
  pipe(piped);
  char str[30];
  sprintf(str, "ls -l /proc/%d/fd", getpid());
  close(0);
  dup(piped[0]);
  system(str);
  return 0;
}*/

// PIPE
/*int main() {
  int figlioAPadre[2];
  pipe(figlioAPadre); // creazione del canale di comunicazione (Pipe)
  char str[30];
  sprintf(str, "ls -l /proc/%d/fd", getpid());
  system(str);
  // close(figlioAPadre[0]); // chiude la pipe dal lato della lettura
  int figlio;
  int prova = 1;
  figlio = fork();   // genero il processo figlio
  if (figlio == 0) { // figlio DEVE SCRIVERE
    printf("Ciao sono il processo figlio\n");
    prova = prova + 5;      // = 6
    close(figlioAPadre[0]); // chiudo la lettura
    write(figlioAPadre[1], &prova, 4);
    exit(0);
  } else if (figlio > 0) { // padre DEVE LEGGERE
    wait(&figlio);
    printf("Ciao sono il processo padre\n");
    int risultato;
    close(figlioAPadre[1]); // chiudo la scrittura
    read(figlioAPadre[0], &risultato, 4);
    printf("Il risultato è: %d\n", risultato);
  } else if (figlio == -1) { // errore Il figlio non viene generato
    printf("Errore durante la generazione del processo figlio\n");
  }
  return 0;
}*/

// scanf
/*int main() {
  int variabile;
  scanf("%d", &variabile);
  printf("Questo è il valore che hai scritto %d", variabile);
  return 0;
}*/

// puntatori
int main() {
  int variabile = 489;
  int *posizione = &variabile;
  printf("Questo è il suo valore: %d\n", variabile);
  printf("Questo è la sua posizione: %p\n",
         &variabile); // p = pointer --> puntatore
  int ciao = *posizione;
  printf("Ciao adesso vale: %d\n", ciao);
}