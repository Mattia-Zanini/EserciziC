#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define R 0
#define W 1

// traceroute google.com | awk '{print $4}' | tail -n +2

int main() {
  int p1, p2, p3, p1p2[2], p2p3[2], p3p0[2];
  char *ptr, buffer[1], valore[100];
  double tot = 0;

  pipe(p1p2);
  p1 = fork();
  if (p1 == 0) // traceroute
  {
    close(W); // stdout
    dup(p1p2[W]);
    close(p1p2[W]);
    close(p1p2[R]);

    execl("/bin/traceroute", "traceroute", "google.com", NULL);
    return -1;
  } else {
    printf("aspetto il figlio");
    wait(&p1);

    int nope = 0;
    int nread = 0;

    while ((nread = read(p1p2[0], buffer, 1)) > 0) {
      if (buffer[0] == '\n') {
        printf("Ho letto la riga: %s\n", valore);
        tot = tot + strtod(valore, &ptr);
        valore[0] = '\0';
      }
      strncat(valore, &buffer[0], sizeof(buffer[0]));
      // rintf("Ho letto questo: %c", buffer[0]);
    }
    printf("%.2lf\n", tot);
  }
}