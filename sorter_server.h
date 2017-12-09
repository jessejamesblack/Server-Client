#ifndef SORTER_SERVER_H
#define SORTER_SERVER_H
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
#include <arpa/inet.h>


struct Tokenizer
{
  unsigned long int num_critic_for_reviews;
  unsigned long int duration;
  unsigned long int director_facebook_likes;
  unsigned long int actor_3_facebook_likes;
  unsigned long int actor_1_facebook_likes;
  unsigned long int gross;
  unsigned long int num_voted_users;
  unsigned long int cast_total_facebook_likes;
  unsigned long int facenumber_in_poster;
  unsigned long int num_user_for_reviews;
  unsigned long int budget;
  unsigned long int title_year;
  unsigned long int actor_2_facebook_likes;
  unsigned long int movie_facebook_likes;
  char color[300];
  char director_name[300];
  char actor_2_name[300];
  char genres[300];
  char actor_1_name[300];
  char movie_title[300];
  char actor_3_name[300];
  char plot_keywords[300];
  char movie_imdb_link[300];
  char language[300];
  char country[300];
  char content_rating[300];
  float imdb_score;
  float aspect_ratio;
};
typedef struct Tokenizer J;

struct clientArgs
{
   int clientID;
   int socketFD;
};

typedef struct clientArgs ClientArgs;


struct fileArgs
{
  char * columnName;
  char * outputDir;
  char * filename;
  char * path;
};
typedef struct args Args;

struct Tokenizer * TKCreate(char *ts, int gQuoteCount);
void printRecord(struct Tokenizer *tk, FILE *f);
char *strtokk(char *str, char const *delims, char ** sp);
char *trimwhitespace(char *str);
void * clientHandler(void * args);
void mymerge(struct Tokenizer **arr1, int size1, struct Tokenizer **arr2, int size2, struct Tokenizer **arr3, char *columnName);
void mymergesort(struct Tokenizer **arr, int size, char *columnName);

#endif
