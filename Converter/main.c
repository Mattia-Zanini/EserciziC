#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "test/err.h"
#include "debug/log.h"

#define WRITE 1
#define READ 0

int main(int argc, char *argv[])
{
  // I check that there is an argument
  if (argc != 2)
  {
    ErrorWrite(1, "Error: ", -1, "no input files\n");
    DoLog("Error while translating, error code: 1; no input files");
    return 1;
  }
  // I check that exist the file passed by argument
  if (access(argv[1], F_OK) != 0)
  {
    ErrorWrite(1, "Error: ", -1, "file not found\n");
    DoLog("Error while translating, error code: 2; input file not found");
    return 2;
  }
  // check the file extension
  if (GoodExtension(argv[1]) != 0)
  {
    ErrorWrite(1, "Error: ", -1, "file have bad extension\n");
    DoLog("Error while translating, error code: 3; input file haven't the right extension");
    return 3;
  }
  // A child controls how many characters the file contains
  int son, p[2];
  pipe(p);
  son = fork();
  if (son == 0)
  {
    dup2(p[WRITE], WRITE);
    char cmd[40];
    sprintf(cmd, "wc -m %s", argv[1]);
    system(cmd);
    exit(0);
  }
  wait(&son);
  // read the pipe to get the number of chars that there is in the file
  char *nchar, c;
  nchar = malloc(1 * sizeof(char));
  while (read(p[READ], &c, 1) > 0)
  {
    if (c != ' ')
    {
      strncat(nchar, &c, 1);
    }
    else
    {
      break;
    }
  }
  char tmp[strlen(nchar)];
  strcpy(tmp, nchar);
  // printf("Quant chars: %d\n", atoi(nchar)); printf("chars (string): %s\n", nchar);
  return 0;
}