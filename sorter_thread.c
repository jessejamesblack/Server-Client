#include "sorter_thread.h"

pthread_mutex_t totalThreadsLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t finalStructLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tidLlock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t TKCreateLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t argsLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mergesortLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t totalFilesLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t totalDirectoriesLock = PTHREAD_MUTEX_INITIALIZER;

FILE *finalOutput;

long initialSize = 10000;

int initial = 1;

int totalThreads = 1;

int mergeIteration = 0;

int totalFiles = 0;
int totalDirectories = 0;

pthread_t directories[100000];
pthread_t files[100000];

//Function to remove unnecessary leading and trailing whitespace characters.
//Returns a string with the whitespace removed.
char *trimwhitespace(char *str)
{
        while (isspace((unsigned char)*str)) // beginning spaces
                str++;
        if (*str == 0)
                return str;
        int index, i;
        i = 0;
        while (str[i] != '\0') //end spaces
        {
                if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
                {
                        index = i;
                }

                i++;
        }
        str[index + 1] = '\0';
        return str;
}

// Our own tokenizer function we created to prevent seg fault on empty entries.
// Uses strpbrk to find places where there are empty columns of a row entry.
// Returns a char * that is the next token in the line.


char *strtokk(char *str, char const *delims, char ** sp)
{
        char *n;
        char *ret = 0;

        if (str != NULL)
        {
                *sp = str;
        }
        if (*sp == NULL)
        {
                return NULL;
        }
        if ((n = strpbrk(*sp, delims)) != NULL)
        {
                *n = 0;
                ret = *sp;
                *sp = ++n;
        }
        else if (**sp)
        {
                ret = *sp;
                *sp = NULL;
        }
        return ret;
}

// Function that prints our row struct out.
// This is used to reprint the newly sorted CSV file at the end.
void printRecord(struct Tokenizer *tk, FILE *f)
{
        // printf("got in here\n");
        fprintf(f, "%s,", tk->color);
        fprintf(f, "%s,", tk->director_name);
        if (tk->num_critic_for_reviews == 0)
                fprintf(f, "%s", ",");
        else
                fprintf(f, "%lu,", tk->num_critic_for_reviews);
        if (tk->duration == 0)
                fprintf(f, "%s", ",");
        else
                fprintf(f, "%lu,", tk->duration);
        if (tk->director_facebook_likes == 0)
                fprintf(f, "%s", ",");
        else
                fprintf(f, "%lu,", tk->director_facebook_likes);
        if (tk->actor_3_facebook_likes == 0)
                fprintf(f, "%s", ",");
        else
                fprintf(f, "%lu,", tk->actor_3_facebook_likes);
        fprintf(f, "%s,", tk->actor_2_name);
        fprintf(f, "%lu,", tk->actor_1_facebook_likes);
        if (tk->gross == 0){
                fprintf(f, "%s", ",");
             }
        else
                fprintf(f, "%lu,", tk->gross);
        fprintf(f, "%s,", tk->genres);
        fprintf(f, "%s,", tk->actor_1_name);
        if (strstr(tk->movie_title, ",") != NULL)
        {
                fprintf(f, "\"%s\",", tk->movie_title);
        }
        else
        {
                fprintf(f, "%s,", tk->movie_title);
        }
        fprintf(f, "%lu,", tk->num_voted_users);
        fprintf(f, "%lu,", tk->cast_total_facebook_likes);
        fprintf(f, "%s,", tk->actor_3_name);
        fprintf(f, "%lu,", tk->facenumber_in_poster);
        fprintf(f, "%s,", tk->plot_keywords);
        fprintf(f, "%s,", tk->movie_imdb_link);
        fprintf(f, "%lu,", tk->num_user_for_reviews);
        fprintf(f, "%s,", tk->language);
        fprintf(f, "%s,", tk->country);
        fprintf(f, "%s,", tk->content_rating);
        if (tk->budget == 0)
                fprintf(f, "%s", ",");
        else
                fprintf(f, "%lu,", tk->budget);
        if (tk->title_year == 0)
                fprintf(f, "%s", ",");
        else
                fprintf(f, "%lu,", tk->title_year);
        fprintf(f, "%lu,", tk->actor_2_facebook_likes);
        if (tk->imdb_score == 6)
                fprintf(f, "%d,", 6);
        else
                fprintf(f, "%.1f,", tk->imdb_score);

        if (tk->aspect_ratio == 16.00)
                fprintf(f, "%.0f,", tk->aspect_ratio);
        else if (tk->aspect_ratio == 0)
                fprintf(f, "%s", ",");
        else if (tk->aspect_ratio == 0.00)
                fprintf(f, "%.0f,", tk->aspect_ratio);
        else
                fprintf(f, "%.2f,", tk->aspect_ratio);

        fprintf(f, "%lu", tk->movie_facebook_likes);
        fprintf(f, "\n");
}

// This function creates a tokenizer struct out a char * line of the CSV file.
// Returns the newly created struct with everything malloc'd correctly.
struct Tokenizer *TKCreate(char *ts, int gQuoteCount)
{
		char * sp;
        struct Tokenizer *newNode = malloc(sizeof(struct Tokenizer));
        if (strlen(ts) == 0)
        {
                return NULL;
        }
        if (strstr(ts, "\"") != NULL)
        {
                //entry has a comma in the title
                char *token;
                unsigned long int temp = 0;
                char *ptr = NULL;
                float temp2 = 0.0;
                token = strtokk(ts, ",", &sp);
                // newNode->color = malloc(strlen(token) + 1);
                strcpy(newNode->color, trimwhitespace(token));
                token = strtokk(NULL, ",", &sp);
                //newNode->director_name = malloc(strlen(token) + 1);
                strcpy(newNode->director_name, trimwhitespace(token));
                token = strtokk(NULL, ",", &sp);
                temp = strtoul(token, &ptr, 10);
                newNode->num_critic_for_reviews = temp;
                token = strtokk(NULL, ",", &sp);
                temp = strtoul(token, &ptr, 10);
                newNode->duration = temp;
                token = strtokk(NULL, ",", &sp);
                temp = strtoul(token, &ptr, 10);
                newNode->director_facebook_likes = temp;
                token = strtokk(NULL, ",", &sp);
                temp = strtoul(token, &ptr, 10);
                newNode->actor_3_facebook_likes = temp;
                token = strtokk(NULL, ",", &sp);
                //newNode->actor_2_name = malloc(strlen(token) + 1);
                strcpy(newNode->actor_2_name, trimwhitespace(token));
                token = strtokk(NULL, ",", &sp);
                temp = strtoul(token, &ptr, 10);
                newNode->actor_1_facebook_likes = temp;
                token = strtokk(NULL, ",", &sp);
                temp = strtoul(token, &ptr, 10);
                //printf("gross = %ul", temp);
                newNode->gross = temp;
                token = strtokk(NULL, ",", &sp);
                //newNode->genres = malloc(strlen(token) + 1);
                strcpy(newNode->genres, trimwhitespace(token));
                token = strtokk(NULL, ",", &sp);
                //newNode->actor_1_name = malloc(strlen(token) + 1);
                strcpy(newNode->actor_1_name, trimwhitespace(token));

                while (gQuoteCount != 2)
                {
                        token = strtokk(NULL, "\"", &sp);
                        //newNode->movie_title = malloc(strlen(token) + 1);
                        strcpy(newNode->movie_title, trimwhitespace(token));
                        gQuoteCount++;
                }
                if (gQuoteCount == 2)
                {
                        gQuoteCount = 0;
                }
                token = strtokk(NULL, ",", &sp);
                token = strtokk(NULL, ",", &sp);
                temp = strtoul(token, &ptr, 10);
                newNode->num_voted_users = temp;
                token = strtokk(NULL, ",", &sp);
                temp = strtoul(token, &ptr, 10);
                newNode->cast_total_facebook_likes = temp;
                token = strtokk(NULL, ",", &sp);
                //newNode->actor_3_name = malloc(strlen(token) + 1);
                strcpy(newNode->actor_3_name, trimwhitespace(token));
                token = strtokk(NULL, ",",&sp);
                temp = strtoul(token, &ptr, 10);
                newNode->facenumber_in_poster = temp;
                token = strtokk(NULL, ",",&sp);
                // newNode->plot_keywords = malloc(strlen(token) + 1);
                strcpy(newNode->plot_keywords, trimwhitespace(token));
                token = strtokk(NULL, ",",&sp);
                //newNode->movie_imdb_link = malloc(strlen(token) + 1);
                strcpy(newNode->movie_imdb_link, trimwhitespace(token));
                token = strtokk(NULL, ",",&sp);
                temp = strtoul(token, &ptr, 10);
                newNode->num_user_for_reviews = temp;
                token = strtokk(NULL, ",",&sp);
                //newNode->language = malloc(strlen(token) + 1);
                strcpy(newNode->language, trimwhitespace(token));
                token = strtokk(NULL, ",",&sp);
                // newNode->country = malloc(strlen(token) + 1);
                strcpy(newNode->country, trimwhitespace(token));
                token = strtokk(NULL, ",",&sp);
                //newNode->content_rating = malloc(strlen(token) + 1);
                strcpy(newNode->content_rating, trimwhitespace(token));
                token = strtokk(NULL, ",",&sp);
                temp = strtoul(token, &ptr, 10);
                newNode->budget = temp;
                token = strtokk(NULL, ",",&sp);
                temp = strtoul(token, &ptr, 10);
                newNode->title_year = temp;
                token = strtokk(NULL, ",",&sp);
                temp = strtoul(token, &ptr, 10);
                newNode->actor_2_facebook_likes = temp;
                token = strtokk(NULL, ",",&sp);
                temp2 = atof(token);
                newNode->imdb_score = temp2;
                token = strtokk(NULL, ",",&sp);
                temp2 = atof(token);
                newNode->aspect_ratio = temp2;
                token = strtokk(NULL, ",",&sp);
                temp = strtoul(token, &ptr, 10);
                newNode->movie_facebook_likes = temp;
        }
        else
        {
                //  entry doesnt have comma in title
                char *token;
                unsigned long int temp = 0;
                char *ptr = NULL;
                float temp2 = 0.0;
                token = strtokk(ts, ",",&sp);
                //newNode->color = malloc(strlen(token) + 1);
                strcpy(newNode->color, trimwhitespace(token));
                token = strtokk(NULL, ",",&sp);
                //newNode->director_name = malloc(strlen(token) + 1);
                strcpy(newNode->director_name, trimwhitespace(token));
                token = strtokk(NULL, ",",&sp);
                temp = strtoul(token, &ptr, 10);
                newNode->num_critic_for_reviews = temp;
                token = strtokk(NULL, ",",&sp);
                temp = strtoul(token, &ptr, 10);
                newNode->duration = temp;
                token = strtokk(NULL, ",",&sp);
                temp = strtoul(token, &ptr, 10);
                newNode->director_facebook_likes = temp;
                token = strtokk(NULL, ",",&sp);
                temp = strtoul(token, &ptr, 10);
                newNode->actor_3_facebook_likes = temp;
                token = strtokk(NULL, ",",&sp);
                // newNode->actor_2_name = malloc(strlen(token) + 1);
                strcpy(newNode->actor_2_name, trimwhitespace(token));
                token = strtokk(NULL, ",",&sp);
                temp = strtoul(token, &ptr, 10);
                newNode->actor_1_facebook_likes = temp;
                token = strtokk(NULL, ",",&sp);
                temp = strtoul(token, &ptr, 10);
                newNode->gross = temp;
                token = strtokk(NULL, ",",&sp);
                // newNode->genres = malloc(strlen(token) + 1);
                strcpy(newNode->genres, trimwhitespace(token));
                token = strtokk(NULL, ",",&sp);
                // newNode->actor_1_name = malloc(strlen(token) + 1);
                strcpy(newNode->actor_1_name, trimwhitespace(token));
                token = strtokk(NULL, ",",&sp);
                // newNode->movie_title = malloc(strlen(token) + 1);
                strcpy(newNode->movie_title, trimwhitespace(token));
                token = strtokk(NULL, ",",&sp);
                temp = strtoul(token, &ptr, 10);
                newNode->num_voted_users = temp;
                token = strtokk(NULL, ",",&sp);
                temp = strtoul(token, &ptr, 10);
                newNode->cast_total_facebook_likes = temp;
                token = strtokk(NULL, ",",&sp);
                //newNode->actor_3_name = malloc(strlen(token) + 1);
                strcpy(newNode->actor_3_name, trimwhitespace(token));
                token = strtokk(NULL, ",",&sp);
                temp = strtoul(token, &ptr, 10);
                newNode->facenumber_in_poster = temp;
                token = strtokk(NULL, ",",&sp);
                // newNode->plot_keywords = malloc(strlen(token) + 1);
                strcpy(newNode->plot_keywords, trimwhitespace(token));
                token = strtokk(NULL, ",",&sp);
                // newNode->movie_imdb_link = malloc(strlen(token) + 1);
                strcpy(newNode->movie_imdb_link, trimwhitespace(token));
                token = strtokk(NULL, ",",&sp);
                temp = strtoul(token, &ptr, 10);
                newNode->num_user_for_reviews = temp;
                token = strtokk(NULL, ",",&sp);
                //newNode->language = malloc(strlen(token) + 1);
                strcpy(newNode->language, trimwhitespace(token));
                token = strtokk(NULL, ",",&sp);
                // newNode->country = malloc(strlen(token) + 1);
                strcpy(newNode->country, trimwhitespace(token));
                token = strtokk(NULL, ",",&sp);
                // newNode->content_rating = malloc(strlen(token) + 1);
                strcpy(newNode->content_rating, trimwhitespace(token));
                token = strtokk(NULL, ",",&sp);
                temp = strtoul(token, &ptr, 10);
                newNode->budget = temp;
                token = strtokk(NULL, ",",&sp);
                temp = strtoul(token, &ptr, 10);
                newNode->title_year = temp;
                token = strtokk(NULL, ",",&sp);
                temp = strtoul(token, &ptr, 10);
                newNode->actor_2_facebook_likes = temp;
                token = strtokk(NULL, ",",&sp);
                temp2 = atof(token);
                newNode->imdb_score = temp2;
                token = strtokk(NULL, ",",&sp);
                temp2 = atof(token);
                newNode->aspect_ratio = temp2;
                token = strtokk(NULL, ",",&sp);
                temp = strtoul(token, &ptr, 10);
                newNode->movie_facebook_likes = temp;
        }
        return newNode;
}

void *sorter(void *argp)
{
        int fileSize = 0;
        int line = 0;
        Args *args = argp;
        char *columnName = args->columnName;
        char *outputDir = args->outputDir;
        char *filename = args->filename;
        char *path = args->path;
        pthread_t id = pthread_self();

        printf("%li, ", (unsigned long int)id);
        fflush(stdout);

        //getting the column names
        char bufferColumn[1024];
        bufferColumn[0] = '\0';
        char stringnn[1024];
        int blah = 0;
        stringnn[0] = '\0';

        FILE *moviefile = fopen(path, "r+");

        if (fgets(bufferColumn, 1024, moviefile) != NULL)
        {
                blah = 1;
        }
        if (blah == 0)
        {
                printf("Filename: %s, ERROR: Empty file.\n", filename);

        }

        int FileArraySize = 1000;
        struct Tokenizer **fileArray = malloc(FileArraySize * sizeof(struct Tokenizer *));

		  int gQuoteCount = 0;

        while (fgets(stringnn, 1024, moviefile) != NULL)
        {

                struct Tokenizer *newNode;

                newNode = TKCreate(stringnn, gQuoteCount);

                if (fileSize > FileArraySize)
                {
                        fileArray = realloc(fileArray, (2 * fileSize * (sizeof(struct Tokenizer *))));
                        FileArraySize = (fileSize + FileArraySize);
                }
                fileArray[fileSize] = newNode;
                fileSize++;
                line++;
        }


        if (line == 0)
        {
                printf("Error: No Entries in CSV to sort.\n");
                return NULL;
        }
        mymergesort(fileArray, fileSize, columnName);
        
        Returner *ret = malloc(sizeof(*ret));
        ret->array = fileArray;
        ret->size = fileSize;

        fclose(moviefile);
        pthread_exit((void *)ret);
}

const char *get_filename_ext(const char *filename)
{
        //printf("in file ext funct\n");
        const char *dot = strrchr(filename, '.');
        if (!dot || dot == filename)
                return "";
        return dot + 1;
}

int is_Valid_CSV(struct dirent *file)
{
        if (strstr(file->d_name, "-sorted-"))
        {
                return -1;
        }
        if (strcasecmp(get_filename_ext(file->d_name), "csv") == 0)
        {
                return 0;
        }
        
        return -1;
}

void *sortDir(void *argp)
{
        ArgsDir *args = argp;
        int obool = args->obool;
        char *path = args->path;
        char *columnName = args->columnName;
        char *outputdirectory = args->outputdirectory;

        pthread_t id = pthread_self();

        printf("%li, ", (unsigned long int)id);
        fflush(stdout);

        struct dirent *currentDirFile; // Pointer for directory entry
        DIR *currentDir = opendir(path);

        if (currentDir == NULL) // opendir returns NULL if couldn't open directory
        {
                printf("Could not open current directory\n");
        }

        while ((currentDirFile = readdir(currentDir)) != NULL)
        {
                //current dirent is a folder that needs to be forked
                if (currentDirFile->d_type == DT_DIR)
                {
                        // fork this new directory to be processed
                        if (strcmp(currentDirFile->d_name, ".") == 0)
                        {
                                continue;
                        }
                        if (strcmp(currentDirFile->d_name, "sorter_thread.dSYM") == 0)
                        {
                                continue;
                        }
                        if (strcmp(currentDirFile->d_name, "..") == 0)
                        {
                                continue;
                        }
                        if (strcmp(currentDirFile->d_name, ".git") == 0)
                        {
                                continue;
                        }

                        char fullpath[1024];
                        fullpath[0] = '\0';
                        strcpy(fullpath, path);
                        strcat(fullpath, "/");
                        strcat(fullpath, currentDirFile->d_name);

                        ArgsDir *argsdir = malloc(sizeof(*argsdir));
                        argsdir->obool = obool;
                        argsdir->path = malloc(strlen(fullpath) + 1);
                        argsdir->outputdirectory = malloc(strlen(outputdirectory) + 1);
                        argsdir->columnName = malloc(strlen(columnName) + 1);
                        strcpy(argsdir->path, fullpath);
                        strcpy(argsdir->outputdirectory, outputdirectory);
                        strcpy(argsdir->columnName, columnName);

                        pthread_mutex_lock(&totalThreadsLock);
                        totalThreads++;
                        totalDirectories++;
                        pthread_create(&directories[totalDirectories - 1], NULL, sortDir, argsdir);
                        pthread_mutex_unlock(&totalThreadsLock);
                }
                else if (is_Valid_CSV(currentDirFile) == 0)
                {
                        char outputPath[1024];
                        strcpy(outputPath, path);
                        char fullpath[1024];
                        strcpy(fullpath, path);
                        strcat(fullpath, "/");
                        strcat(fullpath, currentDirFile->d_name);
                        if (obool == 0)
                        {
                                outputdirectory = outputPath;
                        }

                        Args *argsfile = malloc(sizeof(*argsfile));
                        argsfile->columnName = malloc(strlen(columnName) + 1);
                        argsfile->path = malloc(strlen(fullpath) + 1);
                        argsfile->outputDir = malloc(strlen(outputdirectory) + 1);
                        argsfile->filename = malloc(strlen(currentDirFile->d_name) + 1);
                        strcpy(argsfile->columnName, columnName);
                        strcpy(argsfile->path, fullpath);
                        strcpy(argsfile->outputDir, outputdirectory);
                        strcpy(argsfile->filename, currentDirFile->d_name);

                        pthread_mutex_lock(&totalThreadsLock);
                        totalThreads++;
                        totalFiles++;
                        pthread_create(&files[totalFiles - 1], NULL, sorter, argsfile);
                        pthread_mutex_unlock(&totalThreadsLock);
                }
                // INVALID file, not a directory or a valid csv file
                else
                {
                        continue;
                }
        }

        pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	
		  long globalCounter = 0;
        if (argc < 3)
        {
                printf("Invalid amount of arguments.\n");
                return 1;
        }

        char *columnName;
        char *directory;
        char *outputdirectory;
        char buffer[1024];

        // 1 if a output directory is specified, 0 if no
        int obool = 0;

        if (argc == 3)
        {
                getcwd(buffer, sizeof(buffer));
                directory = buffer;
                outputdirectory = buffer;
                columnName = argv[2];
        }
        else if (argc == 5)
        {
                if ((strcmp(argv[1], "-c") == 0) && (strcmp(argv[3], "-d") == 0))
                {
                        directory = argv[4];
                        getcwd(buffer, sizeof(buffer));
                        outputdirectory = buffer;
                        columnName = argv[2];
                }
                else if ((strcmp(argv[1], "-d") == 0) && (strcmp(argv[3], "-c") == 0))
                {
                        directory = argv[2];
                        getcwd(buffer, sizeof(buffer));
                        outputdirectory = buffer;
                        columnName = argv[4];
                }
                else if ((strcmp(argv[1], "-c") == 0) && (strcmp(argv[3], "-o") == 0))
                {
                        getcwd(buffer, sizeof(buffer));
                        directory = buffer;
                        outputdirectory = argv[4];
                        obool = 1;
                        columnName = argv[2];
                }
                else if ((strcmp(argv[1], "-o") == 0) && (strcmp(argv[3], "-c") == 0))
                {
                        getcwd(buffer, sizeof(buffer));
                        directory = buffer;
                        outputdirectory = argv[2];
                        obool = 1;
                        columnName = argv[4];
                }
                else
                {
                        printf("Invalid input.\n");
                        return -1;
                }
        }
        else if (argc == 7)
        {
                if ((strcmp(argv[1], "-c") == 0) && (strcmp(argv[3], "-d") == 0) && (strcmp(argv[5], "-o") == 0))
                {
                        directory = argv[4];
                        outputdirectory = argv[6];
                        obool = 1;
                        columnName = argv[2];
                }
                else if ((strcmp(argv[1], "-c") == 0) && (strcmp(argv[3], "-o") == 0) && (strcmp(argv[5], "-d") == 0))
                {
                        directory = argv[6];
                        outputdirectory = argv[4];
                        obool = 1;
                        columnName = argv[2];
                }
                else if ((strcmp(argv[1], "-o") == 0) && (strcmp(argv[3], "-d") == 0) && (strcmp(argv[5], "-c") == 0))
                {
                        directory = argv[4];
                        outputdirectory = argv[2];
                        obool = 1;
                        columnName = argv[6];
                }
                else if ((strcmp(argv[1], "-o") == 0) && (strcmp(argv[3], "-c") == 0) && (strcmp(argv[5], "-d") == 0))
                {
                        directory = argv[6];
                        outputdirectory = argv[2];
                        obool = 1;
                        columnName = argv[4];
                }
                else if ((strcmp(argv[1], "-d") == 0) && (strcmp(argv[3], "-c") == 0) && (strcmp(argv[5], "-o") == 0))
                {
                        directory = argv[2];
                        outputdirectory = argv[6];
                        obool = 1;
                        columnName = argv[4];
                }
                else if ((strcmp(argv[1], "-d") == 0) && (strcmp(argv[3], "-o") == 0) && (strcmp(argv[5], "-c") == 0))
                {
                        directory = argv[2];
                        outputdirectory = argv[4];
                        obool = 1;
                        columnName = argv[6];
                }
                else
                {
                        printf("Invalid input.\n");
                        return -1;
                }
        }
        else
        {
                printf("Invalid input.\n");
                return -1;
        }

        if ((strcmp(columnName, "num_critic_for_reviews") == 0) || (strcmp(columnName, "duration") == 0) || (strcmp(columnName, "director_facebook_likes") == 0) || (strcmp(columnName, "actor_3_facebook_likes") == 0) || (strcmp(columnName, "actor_1_facebook_likes") == 0) || (strcmp(columnName, "gross") == 0) || (strcmp(columnName, "num_voted_users") == 0) || (strcmp(columnName, "cast_total_facebook_likes") == 0) || (strcmp(columnName, "facenumber_in_poster") == 0) || (strcmp(columnName, "num_user_for_reviews") == 0) || (strcmp(columnName, "budget") == 0) || (strcmp(columnName, "title_year") == 0) || (strcmp(columnName, "actor_2_facebook_likes") == 0) || (strcmp(columnName, "movie_facebook_likes") == 0) || (strcmp(columnName, "imdb_score") == 0) || (strcmp(columnName, "aspect_ratio") == 0) || (strcmp(columnName, "color") == 0) || (strcmp(columnName, "director_name") == 0) || (strcmp(columnName, "actor_2_name") == 0) || (strcmp(columnName, "genres") == 0) || (strcmp(columnName, "actor_1_name") == 0) || (strcmp(columnName, "movie_title") == 0) || (strcmp(columnName, "actor_3_name") == 0) || (strcmp(columnName, "plot_keywords") == 0) || (strcmp(columnName, "movie_imdb_link") == 0) || (strcmp(columnName, "language") == 0) || (strcmp(columnName, "country") == 0) || (strcmp(columnName, "content_rating") == 0))
        {
                ;
        }
        else
        {
                printf("Not a valid column to sort.\n");
                return -1;
        }

        /* look for arguments here -c column name, -d  starting directory  -- could also be black->curr dir,
         -o output directory*/
        DIR *dir = opendir(directory);
        if (dir)
        {
                /* Directory exists. */
                closedir(dir);
        }
        else if (ENOENT == errno)
        {
                fflush(stdout);
                printf("\nDirectory to search in is invalid. Please input valid directory. \n\n");
                fflush(stdout);
                return -1;
        }

        printf("Initial PID: %d\n", getpid());
        printf("TIDS of all child threads: ");
        fflush(stdout);

        ArgsDir *argsdir = malloc(sizeof(*argsdir));
        argsdir->obool = obool;
        argsdir->path = malloc(strlen(directory) + 1);
        argsdir->outputdirectory = malloc(strlen(outputdirectory) + 1);
        argsdir->columnName = malloc(strlen(columnName) + 1);
        strcpy(argsdir->path, directory);
        strcpy(argsdir->outputdirectory, outputdirectory);
        strcpy(argsdir->columnName, columnName);

        char outputty[1024];
        strcpy(outputty, outputdirectory);
        strcat(outputty, "/");
        strcat(outputty, "AllFiles-sorted-<");
        strcat(outputty, columnName);
        strcat(outputty, ">.csv");

        finalOutput = fopen(outputty, "w+");

        // printing out the thread id of the initial thread
        // dont want this number:
        //printf("%d, ", (int)getpid());

        // Start looking for files and directories to create threads, sort, and merge to final struct
        //sortDir(argsdir);

        pthread_t tid;
        pthread_create(&tid, NULL, sortDir, argsdir);
        pthread_join(tid, NULL);
        // should merge the files with themselves first in pairs of 2 and then with the intermediate struct

        //printf("totalfiles: %d\n", totalFiles);
        //printf("totalDirectories: %d\n", totalDirectories);

        int c = 0;
        for (c = 0; c < totalDirectories; c++)
        {
                pthread_join(directories[c], NULL);
                //printf("joining dir c= %d\n",c );
        }
        //printf("directories done joining");
        Returner **gatherFiles = malloc(totalFiles * sizeof(*gatherFiles));

        //printf("totalfiles: %d\n", totalFiles);
        int z = 0;
        for (z = 0; z < totalFiles; z++)
        {
                pthread_join(files[z], (void *)&gatherFiles[z]);
                globalCounter += gatherFiles[z]->size;
        }
        
       // printf("total rows: %d\n", globalCounter);
       // printf("files done joining, global size: %d", globalCounter);

/*
------------------------------------------------------------------------------------------
This upcoming section does rounds of merging, spawning threads to merge pairs of 2 files.
------------------------------------------------------------------------------------------
*/
        //printf("merge section starting");
        double roundAmount = totalFiles;

        // log2 (x) = logy (x) / logy (2)
        int fileRounds = ceil(log10(totalFiles) / log10(2));
        //  printf("\nnumber of files: %d, file rounds %d\n\n\n",totalFiles, fileRounds);
        int round = 0;
        for (round = 0; round < fileRounds; round++)
        {
               // printf("round: %d\n", round);
                int intRoundAmount = (int)(ceil(roundAmount / 2));
                pthread_t filesMerge[intRoundAmount];
                // send pairs of 2 off to merge
                int pairs = 0;
                int returnIndex = 0;
                //printf("roundAmount: %d\n", (int)roundAmount);
                int position = 0;

                if ((int)roundAmount % 2 == 0)
                {
                        for (pairs = 0; pairs < roundAmount; pairs = pairs + 2)
                        {
                                //printf("position: %d\n", position);
                                // printf("pairs index: %d, pairs + 1 index: %d\n", pairs, pairs+1);
                                // printf("gatherFiles directorName at pairs + 1: %s\n", (gatherFiles[pairs+1]->array)[0]->director_name);
                                struct mergeArgs *args = malloc(sizeof(*args));
                                args->arr1 = gatherFiles[pairs]->array;
                                // printf("arr1: director name: %s\n", (args->arr1)[0]->director_name);
                                args->size1 = gatherFiles[pairs]->size;
                                args->arr2 = gatherFiles[pairs + 1]->array;
                                args->size2 = gatherFiles[pairs + 1]->size;
                                args->columnName = columnName;
                                args->returnIndex = returnIndex;
                                pthread_create(&filesMerge[returnIndex], NULL, mergeThread, args);
                                returnIndex++;
                        }

                        Returner **gatherRound = malloc(roundAmount * sizeof(*gatherFiles));
                        // join them and store them in the gatherRound array
                        int pair2 = 0;
                        for (pair2 = 0; pair2 < roundAmount / 2; pair2++)
                        {
                                pthread_join(filesMerge[pair2], (void *)&gatherRound[pair2]);
                        }

                        //write the results of the gatherRound array back into the original gatherFiles array
                        int pair3 = 0;
                        for (pair3 = 0; pair3 < roundAmount / 2; pair3++)
                        {
                                gatherFiles[pair3] = gatherRound[pair3];
                        }
                }
                else
                {
                        for (pairs = 0; pairs < roundAmount; pairs = pairs + 2)
                        {
                                if ((double)(pairs + 1) == roundAmount)
                                {
                                        position = (int)((roundAmount - 1) / 2);
                                        gatherFiles[position] = gatherFiles[pairs];
                                        //printf("pairs: %d, position: %d\n", gatherFiles[pairs]->name, gatherFiles[position]->name);
                                        // printf("the lone array was moved\n");
                                        break;
                                }
                                //printf("position: %d\n", position);
                                //printf("pairs index: %d, pairs + 1 index: %d\n", pairs, pairs+1);
                                // printf("gatherFiles directorName at pairs + 1: %s\n", (gatherFiles[pairs+1]->array)[0]->director_name);
                                struct mergeArgs *args = malloc(sizeof(*args));
                                args->arr1 = gatherFiles[pairs]->array;
                                args->size1 = gatherFiles[pairs]->size;
                                args->arr2 = gatherFiles[pairs + 1]->array;
                                args->size2 = gatherFiles[pairs + 1]->size;
                                args->columnName = columnName;
                                args->returnIndex = returnIndex;
                                pthread_create(&filesMerge[returnIndex], NULL, mergeThread, args);
                                returnIndex++;
                        }

                        Returner **gatherRound = malloc(roundAmount * sizeof(*gatherFiles));
                        // join them and store them in the gatherRound array
                        int pair2 = 0;
                        for (pair2 = 0; pair2 < ceil(roundAmount / 2) - 1; pair2++)
                        {
                                pthread_join(filesMerge[pair2], (void *)&gatherRound[pair2]);
                        }

                        //write the results of the gatherRound array back into the original gatherFiles array
                        int pair3 = 0;
                        for (pair3 = 0; pair3 < ceil(roundAmount / 2) - 1; pair3++)
                        {
                                gatherFiles[pair3] = gatherRound[pair3];
                        }
                }
                roundAmount = ceil(roundAmount / 2);
        }

        if (totalFiles != 0)
        {
                printf("printing\n");
                fprintf(finalOutput, "color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes\n");
                struct Tokenizer **ptr = gatherFiles[0]->array;

                int x;
                for (x = 0; x < globalCounter; x++)
                {
                        printRecord(ptr[x], finalOutput);
                }
        }

        printf("\nTotal number of threads: %d\n", totalThreads);


        return 0;
}
