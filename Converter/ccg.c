#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define WRITE 1
#define READ 0

void ChangeTextColor(int id) {
  switch (id) {
  case -1:
    printf("\033[0m"); // DEFAULT COLOR
    break;
  case 0:
    printf("\033[0;30m"); // BLACK
    break;
  case 1:
    printf("\033[1;31m"); // RED
    break;
  case 2:
    printf("\033[0;32m"); // GREEN
    break;
  case 3:
    printf("\033[0;33m"); // YELLOW
    break;
  case 4:
    printf("\033[0;34m"); // BLUE
    break;
  case 5:
    printf("\033[0;35m"); // PURPLE
    break;
  case 6:
    printf("\033[0;36m"); // CYAN
    break;
  case 7:
    printf("\033[0;37m"); // WHITE
    break;
  }
}
// check the file extension, which must be .dg
int GoodExtension(char filename[]) {
  int length = strlen(filename);
  if (filename[length - 2] == 'd' && filename[length - 1] == 'g') {
    return 0; // good extension
  }
  return -1; // bad extension
}

int main(int argc, char *argv[]) {
  // I check that there is an argument
  if (argc != 2) {
    ChangeTextColor(1);
    printf("Error: ");
    ChangeTextColor(-1);
    printf("no input files\n");
    return 1;
  }
  // I check that exist the file passed by argument
  if (access(argv[1], F_OK) != 0) {
    ChangeTextColor(1);
    printf("Error: ");
    ChangeTextColor(-1);
    printf("file not found\n");
    return 2;
  }
  // check the file extension
  if (GoodExtension(argv[1]) != 0) {
    ChangeTextColor(1);
    printf("Error: ");
    ChangeTextColor(-1);
    printf("file have bad extension\n");
    return 3;
  }
  // A child controls how many characters the file contains
  int son, p[2];
  pipe(p);
  son = fork();
  if (son == 0) {
    dup2(p[WRITE], WRITE);
    char cmd[40];
    sprintf(cmd, "wc -m %s", argv[1]);
    system(cmd);
    exit(0);
  }
  wait(&son);
  char nchar[100], c;
  // read the pipe to get the number of chars that there is in the file
  while (read(p[READ], &c, 1) > 0) {
    if (c != ' ') {
      strncat(nchar, &c, 1);
    } else {
      break;
    }
  }
  char tmp[strlen(nchar)];
  strcpy(tmp, nchar);
  printf("Quant chars: %d\n", atoi(nchar));
  printf("chars (string): %s\n", nchar);
  return 0;
}