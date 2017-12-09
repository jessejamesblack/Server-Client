#ifndef SORTER_CLIENT_H
#define SORTER_CLIENT_H
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <errno.h>
#include <pthread.h>
#include <math.h>
#include <netdb.h>

void * send_file(void * args);
void *sortDir(void *argp);

struct argsDir
{
  char * path;
  char * columnName;
  char * outputdirectory;
  int obool;
};
typedef struct argsDir ArgsDir;

struct client_args
{
    char * filename;
    char * path;
};
typedef struct client_args CArgs;

#endif
