/*
Padre fa 2 figli, il secondo fa un cat del file e il primo genito fa grep -c di
parola e dopo padre scrive risultato su file.
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

int main(int argc, char *argv[]) {

  int p2p1[2], p1p0[2], pid1, pid2, tot = 0;
  char buff[1024], stringa[1024];

  while (1) {
    printf("Inserisci una parola da cercare\n");
    scanf("%s", stringa);

    if (strcmp(stringa, "fine") == 0) {
      printf("La ricerca ha prodotto %d occorrenze\n", tot);
      break;
    }

    pipe(p1p0);
    pipe(p2p1);

    pid1 = fork();
    if (pid1 == 0) // figlio 1
    {

      sleep(2);

      close(0); // stdin
      dup(p2p1[READ]);
      close(p2p1[READ]);
      close(p2p1[WRITE]);

      close(1); // stdout
      dup(p1p0[WRITE]);
      close(p1p0[WRITE]);
      close(p1p0[READ]);

      execl("/bin/grep", "grep", "-c", stringa, NULL);
      return -1;

    } else {
      pid2 = fork();
      if (pid2 == 0) // figlio 2
      {
        close(1); // stdout
        dup(p2p1[WRITE]);
        close(p2p1[WRITE]);
        close(p2p1[READ]);

        close(p1p0[WRITE]);
        close(p1p0[READ]);

        execl("/bin/cat", "cat", "File.txt", NULL);
        return -1;
      } else // padre
      {
        close(p2p1[READ]);
        close(p2p1[WRITE]);
        close(p1p0[WRITE]);
        waitpid(pid1, &pid1, 0);
        int num = read(p1p0[READ], buff, sizeof(buff));
        close(p1p0[READ]);
        printf("Ho letto questo: %d\n", atoi(buff));
        tot = tot + atoi(buff);

        int fd1 = open("FileOut.txt", O_WRONLY | O_CREAT, 0777);

        int stdout_copy = dup(1);
        close(1); // stdout
        dup(fd1);
        write(1, buff, num);
        close(fd1);
        dup2(stdout_copy, 1);
      }
    }
  }

  return 0;
}