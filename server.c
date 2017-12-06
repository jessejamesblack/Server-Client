	#include "server.h"
	#include "mergesort.c"

	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t clientIDLock = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t clientArrayLock = PTHREAD_MUTEX_INITIALIZER;
	
	int clientID = 0;
	
Returner * sorter(char * filename, char * columnName)
{
        int fileSize = 0;
        int line = 0;

		  FILE * moviefile = fopen(filename, "r");	  
		  
        char stringnn[1024];
        stringnn[0] = '\0';
		
        int FileArraySize = 1000;
        struct Tokenizer **fileArray = malloc(FileArraySize * sizeof(struct Tokenizer *));

		  int gQuoteCount = 0;

        while (fgets(stringnn, 1024, moviefile) != NULL)
        {
					 //printf("%s\n", stringnn);
                struct Tokenizer *newNode;

                newNode = TKCreate(stringnn, gQuoteCount);

                if (fileSize > FileArraySize)
                {
                        fileArray = realloc(fileArray, (2 * fileSize * (sizeof(struct Tokenizer *))));
                        FileArraySize = (fileSize + FileArraySize);
                }
                
                fileArray[fileSize] = newNode;
               // printRecord(fileArray[fileSize], stdout);
                fileSize++;
                line++;
        }


        if (line == 0)
        {
                printf("Error: No Entries in CSV to sort.\n");
                return NULL;
        }


        mymergesort(fileArray, fileSize, columnName);
        
        
        
        
        Returner * ret = malloc(sizeof(*ret));
        ret->array = fileArray;
		  ret->size = fileSize;
        
        // always make sure to close files when done with them
        fclose(moviefile);
        
        return ret;
}


// This function creates a tokenizer struct out a char * line of the CSV file.
// Returns the newly created struct with everything malloc'd correctly.
struct Tokenizer *TKCreate(char *ts, int gQuoteCount)
{
		//printf("%s\n", ts);
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
	
	
	
int main(int argc, char *argv[])
{
		int clientArraySize = 50;
	/*	if(argc < 3){
			printf("invalid amount of arguments.\n");
			return 1;
		}*/
		
		 char * portString = argv[2];
	//printf("%s\n", portString);	 
	int port = atoi(portString);
		// int port = 8080;
		  
	    int server_fd, new_socket, valread;
	    struct sockaddr_in address;
	    int opt = 1;
	    int addrlen = sizeof(address);
	    char buffer[1024] = {0};
	
		 printf("connection open for clients...\n");
		 

	    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	    {
	        perror("socket failed");
	        exit(EXIT_FAILURE);
	    }
	
	    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
	                   &opt, sizeof(opt)))
	    {
	        perror("setsockopt");
	        exit(EXIT_FAILURE);
	    }
	    
	    address.sin_family = AF_INET;
	    address.sin_addr.s_addr = INADDR_ANY;
	    address.sin_port = htons(port);
	    
	    printf("PORT: %d\n", port);
	fflush(stdout);
	
	 	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	   {
	        perror("bind failed");
	        exit(EXIT_FAILURE);
	    }
	   
	 	if (listen(server_fd, 3) < 0)
	   {
	        perror("listen");
	        exit(EXIT_FAILURE);
	   }
	   	   
	   
		int tidCount = 0;
		int k = 0; // index for finding a spot to put the client in client array
		int j = 0; // index for the join checking loop
		

  while ((new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t *)&addrlen)))
	   {
			puts("connection accepted, spawning thread to process the client");
			k = 0;
			j = 0;
			ClientArgs * args = malloc(sizeof(*args));
			args->clientID = clientID;
			args->socketFD = new_socket;
			pthread_t tid;
			clientID++;
							
			pthread_create(&tid, NULL, clientHandler, args); 
			
 }
	 return 0;
}


void * clientHandler (void * args){
		
		// grabbing arguments from the spawned client connection
		ClientArgs * arg = args; 
		int socketFD = (int) arg->socketFD;	
		int clientID = (int) arg->clientID;
		printf("socket ID: %d\n", socketFD);
		
		int valread;	
		
		char filename[1024];
		strcpy(filename, "Client");
		char clientIDBuffer[1024];
		snprintf(clientIDBuffer, 1024, "%d", clientID);
		strcat(filename, clientIDBuffer);
		strcat(filename, ".csv"); 
		
		FILE * file = fopen(filename, "wb");
		
		
		char buffer[1024]; // buffer to read in lines of the files
		char columnLen[5];
		char columnName[1024];
		int columnGet = 1;
		int total = 0;
		int b = 0;
		int c = 0;
		
	//grabbing the column from socket
		recv(socketFD, columnLen, 2, 0);
		printf("length of column: %d\n", atoi(columnLen));
		
		int columnAmount = atoi(columnLen);
		
		recv(socketFD, columnName, columnAmount, 0);
		printf("column: %s\n", columnName);
		
		
		while((b = recv(socketFD, buffer, 1024, 0)) > 0) {	
			total+= b;
			//printf("buffer: %s", buffer);
			fwrite(buffer, 1, b ,file);	
			//fprintf(file, "%s", buffer);
			bzero(buffer, 1024);
		}
		fclose(file);
		
		
	//I need to get the column name from the client somehow
	Returner * sortedReturn;
	
	// sort file
	sortedReturn = sorter(filename, columnName);
	
	// return file to client
	// need to have sorter return an array of row structs, so we can loop through it writing to a new file, then loop through that new file writing to the socket
	
	char outputText[1024];
	strcpy(outputText, "output");
	char clientIDBufferout[1024];
	snprintf(clientIDBufferout, 1024, "%d", clientID);
	strcat(outputText, clientIDBuffer);	
	
	FILE * output = fopen(outputText, "wb");
	int size = sortedReturn->size;
	struct Tokenizer ** sortedArray = sortedReturn->array;
	
	printf("size: %d\n", size);
	
	int u = 0;	
	for(u = 0; u < size; u++){
	//	printf("%d\n", u);
		printRecord(sortedArray[u], output);	
	}
	
	printf("done printing to output file on server\n");
	fclose(output);
	
	/*
	 // writing to file on client side
    while (fgets(buffer, 1024, output) != NULL) {
	    write(socketFD, buffer, 1024);
    }
    */
/*
	// delete client nonsorted input file 
	if (remove(filename) == 0)
      printf("Deleted successfully\n");
   else
      printf("Unable to delete the file\n");
	
		// delete sorted output file 
	if (remove(outputText) == 0)
      printf("Deleted successfully\n");
   else
      printf("Unable to delete the file\n");
	*/
	/*int q = 0;
	// signal ready to join, by updating the array		
		pthread_mutex_lock(&clientArrayLock);
		for(q = 0; q < clientArraySize; q++){
			if(clientArray[q].clientID == clientID){
					clientArray[q].clientReadyToJoin = 1;		
					break;
			}		
		}

		
		*/
		
pthread_exit(NULL);
}



