#ifndef CLIENT_H
#define CLIENT_H


void * send_file(void * args);

struct client_args
{
    char * filename;
    char * path;
};
typedef struct client_args CArgs;

#endif
