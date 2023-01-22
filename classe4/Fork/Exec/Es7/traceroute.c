#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define R 0
#define W 1

// traceroute google.com | awk '{print $4}' | tail -n +2

int main()
{
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
  }
  else
  {
    pipe(p2p3);
    p2 = fork();
    if (p2 == 0) // awk
    {
      close(R); // stdin
      dup(p1p2[R]);
      close(p1p2[W]);
      close(p1p2[R]);

      close(W); // stdout
      dup(p2p3[W]);
      close(p2p3[W]);
      close(p2p3[R]);

      execl("/bin/awk", "awk", "{print $4}", NULL);
      return -1;
    }
    else
    {
      pipe(p3p0);
      p3 = fork(); // tail -n +2
      if (p3 == 0)
      {
        close(R); // stdin
        dup(p2p3[R]);
        close(p2p3[W]);
        close(p2p3[R]);

        close(W); // stdout
        dup(p3p0[W]);
        close(p3p0[W]);
        close(p3p0[R]);

        // chiudo la pipe che non serve
        close(p1p2[W]);
        close(p1p2[R]);

        execl("/bin/tail", "tail", "-n", "+2", NULL);
        return -1;
      }
      else // padre
      {
        close(p1p2[W]);
        close(p1p2[R]);
        close(p2p3[W]);
        close(p2p3[R]);
        close(p3p0[W]);

        wait(&p3);
        int nread = 0;

        while ((nread = read(p3p0[0], buffer, 1)) > 0)
        {
          if (buffer[0] == '\n')
          {
            tot = tot + strtod(valore, &ptr);
            valore[0] = '\0';
          }
          strncat(valore, &buffer[0], sizeof(buffer[0]));
        }
        printf("Totale: %.2lf ms\n", tot);
      }
    }
  }
}