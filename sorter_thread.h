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
/*****
*
*	Define structures and function prototypes for your sorter
*
*
*
******/

//Suggestion: define a struct that mirrors a record (row) of the data set

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

struct tids
{
  pthread_t tid;
  struct tids *next;
};
typedef struct tids Tids;

struct mergeArgs
{
  struct Tokenizer **arr1;
  int size1;
  struct Tokenizer **arr2;
  int size2;
  struct Tokenizer **arr3;
  char *columnName;
  int returnIndex;
};
typedef struct mergeArgs merges;

struct args
{
  char * columnName;
  char * outputDir;
  char * filename;
  char * path;
};
typedef struct args Args;

struct argsDir
{
  char * path;
  char * columnName;
  char * outputdirectory;
  int obool;
};
typedef struct argsDir ArgsDir;

struct returnStruct
{
  struct Tokenizer **array;
  int size;
  int name;
};
typedef struct returnStruct Returner;

int quickSort(struct Tokenizer **arr, int left, int right, char *columnName);

void swap(struct Tokenizer **a, struct Tokenizer **b);

int partition(struct Tokenizer **arr, int low, int high);

void myquicksort(struct Tokenizer **arr, int low, int high);

void mymergesort(struct Tokenizer **arr, int size, char *columnName);

void *mergeThread(void *mergeArgs);

void mymerge(struct Tokenizer **arr1, int size1, struct Tokenizer **arr2, int size2, struct Tokenizer **arr3, char *columnName);

void *sorter(void *args);

void *sortDir(void *args);
