#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

int tot = 0;

void signal_handler(int signum) {

  // Return type of the handler function should be void
  printf("\nChiusura del programma...\n");
  printf("sono stati trovati: %d insoluti\n", tot);
  exit(0);
}

/*int main(void) {

  signal(SIGINT, intHandler);

  while (1) {
    if (keepRunning == 1) {
      sleep(1);
      printf("Ciao sono in esecuzione\n");
    } else if (keepRunning == 0) {
      printf("Hai premuto ctrl + c\n");
      break;
    }
  }
}*/

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf(
        "Argomenti errati. Inserire come primo argomento il nome di un file\n");
    exit(0);
  }
  char stringa[1000], codice[5];
  int p1p0[2], pid;

  pipe(p1p0);
  while (1) {
    // signal handler
    signal(SIGINT, signal_handler);

    printf("Inserisci codice:\n");
    scanf("%s", codice);

    if (strcmp("esci", codice) == 0) {
      printf("\nChiusura del programma...\n");
      printf("sono stati trovati: %d insoluti\n", tot);
      close(p1p0[READ]);
      close(p1p0[WRITE]);
      exit(0);
    }

    pid = fork();
    if (pid == 0) {
      close(p1p0[READ]);
      close(WRITE);
      dup(p1p0[WRITE]);
      close(p1p0[WRITE]);

      execl("/bin/grep", "grep", "-c", strcat(codice, " insoluto"), argv[1],
            NULL);
      return -1;
    }

    read(p1p0[READ], stringa, sizeof(stringa));
    printf("Sono stati trovati %d insoluti\n", atoi(stringa));
    tot = tot + atoi(stringa);

    if (pid < 0) {
      printf("Errore durante la generazione del figlio");
    }
  }

  return 0;
}