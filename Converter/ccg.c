#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define WRITE 1
#define READ 0

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Error: no input files\n");
    return 1;
  }
  int p[2];
  pipe(p);
  int son = fork();
  if (son == 0) {
    dup2(p[WRITE], WRITE);
    system("wc -c ccg.c");
    exit(0);
  }
  wait(&son);
  char nchar[0], c;
  while (read(p[READ], &c, 1) > 0) {
    if (c != ' ') {
      strncat(nchar, &c, 1);
    } else {
      break;
    }
  }
  printf("%s\n", nchar);
  return 0;
}