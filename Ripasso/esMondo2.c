#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Argomenti errati\n");
    return 0;
  }
  int p1p2[2], p2p0[2], p1, p2, tot = 0;
  char buff[1024];
  while (1) {
    printf("Cosa vuoi cercare?\n");
    scanf("%s", buff);
    if (strcmp(buff, "fine") == 0) {
      printf("La ricerca ha prodotto %d occorrenze\n", tot);
      break;
    }
    pipe(p1p2);
    pipe(p2p0);
    p1 = fork();
    if (p1 == 0) { // figlio 1
      sleep(2);
      /*char str[30];
      sprintf(str, "ls -l /proc/%d/fd", getpid());
      system(str);*/
      close(0); // stdin
      dup(p1p2[READ]);
      close(p1p2[WRITE]);
      close(p1p2[READ]);

      close(1); // stdout
      dup(p2p0[WRITE]);
      close(p2p0[WRITE]);
      close(p2p0[READ]);

      execl("/bin/grep", "grep", "-c", buff, NULL);
      return -1;
    } else { // padre
      p2 = fork();
      if (p2 == 0) { // figlio 2
        close(1);    // stdout
        dup(p1p2[WRITE]);
        close(p1p2[WRITE]);
        close(p1p2[READ]);
        close(p2p0[WRITE]);
        close(p2p0[READ]);

        execl("/bin/cat", "cat", argv[1], NULL);
        return -1;
      } else { // padre
        close(p1p2[WRITE]);
        close(p1p2[READ]);
        close(p2p0[WRITE]);
        waitpid(p1, &p1, 0);
        read(p2p0[READ], buff, sizeof(buff));
        tot = tot + atoi(buff);
        printf("dati ottenuti %d\n", atoi(buff));
      }
    }
  }
  return 0;
}