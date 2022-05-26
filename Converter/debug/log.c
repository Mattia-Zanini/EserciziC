#include "log.h"
#include <stdlib.h>
#include <stdio.h>

int DoLog(char log[])
{
  FILE *f;
  f = fopen("file_log.log", "a+"); // a+ (create + append) option will allow appending which is useful in a log file
  if (f == NULL) { /* Something is wrong   */}
  fprintf(f, "%s\n", log);
  return 0;
}