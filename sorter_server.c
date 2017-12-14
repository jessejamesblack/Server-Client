#include "sorter_server.h"
#include "mergesort.c"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t clientIDLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t clientArrayLock = PTHREAD_MUTEX_INITIALIZER;

int clientID = 0;

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
        strcpy(newNode->color, trimwhitespace(token));
        token = strtokk(NULL, ",", &sp);
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
        strcpy(newNode->actor_2_name, trimwhitespace(token));
        token = strtokk(NULL, ",", &sp);
        temp = strtoul(token, &ptr, 10);
        newNode->actor_1_facebook_likes = temp;
        token = strtokk(NULL, ",", &sp);
        temp = strtoul(token, &ptr, 10);
        //printf("gross = %ul", temp);
        newNode->gross = temp;
        token = strtokk(NULL, ",", &sp);
        strcpy(newNode->genres, trimwhitespace(token));
        token = strtokk(NULL, ",", &sp);
        strcpy(newNode->actor_1_name, trimwhitespace(token));

        while (gQuoteCount != 2)
        {
            token = strtokk(NULL, "\"", &sp);
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
        strcpy(newNode->actor_3_name, trimwhitespace(token));
        token = strtokk(NULL, ",",&sp);
        temp = strtoul(token, &ptr, 10);
        newNode->facenumber_in_poster = temp;
        token = strtokk(NULL, ",",&sp);
        strcpy(newNode->plot_keywords, trimwhitespace(token));
        token = strtokk(NULL, ",",&sp);
        strcpy(newNode->movie_imdb_link, trimwhitespace(token));
        token = strtokk(NULL, ",",&sp);
        temp = strtoul(token, &ptr, 10);
        newNode->num_user_for_reviews = temp;
        token = strtokk(NULL, ",",&sp);
        strcpy(newNode->language, trimwhitespace(token));
        token = strtokk(NULL, ",",&sp);
        strcpy(newNode->country, trimwhitespace(token));
        token = strtokk(NULL, ",",&sp);
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
        strcpy(newNode->color, trimwhitespace(token));
        token = strtokk(NULL, ",",&sp);
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
        strcpy(newNode->actor_2_name, trimwhitespace(token));
        token = strtokk(NULL, ",",&sp);
        temp = strtoul(token, &ptr, 10);
        newNode->actor_1_facebook_likes = temp;
        token = strtokk(NULL, ",",&sp);
        temp = strtoul(token, &ptr, 10);
        newNode->gross = temp;
        token = strtokk(NULL, ",",&sp);
        strcpy(newNode->genres, trimwhitespace(token));
        token = strtokk(NULL, ",",&sp);
        strcpy(newNode->actor_1_name, trimwhitespace(token));
        token = strtokk(NULL, ",",&sp);
        strcpy(newNode->movie_title, trimwhitespace(token));
        token = strtokk(NULL, ",",&sp);
        temp = strtoul(token, &ptr, 10);
        newNode->num_voted_users = temp;
        token = strtokk(NULL, ",",&sp);
        temp = strtoul(token, &ptr, 10);
        newNode->cast_total_facebook_likes = temp;
        token = strtokk(NULL, ",",&sp);
        strcpy(newNode->actor_3_name, trimwhitespace(token));
        token = strtokk(NULL, ",",&sp);
        temp = strtoul(token, &ptr, 10);
        newNode->facenumber_in_poster = temp;
        token = strtokk(NULL, ",",&sp);
        strcpy(newNode->plot_keywords, trimwhitespace(token));
        token = strtokk(NULL, ",",&sp);
        strcpy(newNode->movie_imdb_link, trimwhitespace(token));
        token = strtokk(NULL, ",",&sp);
        temp = strtoul(token, &ptr, 10);
        newNode->num_user_for_reviews = temp;
        token = strtokk(NULL, ",",&sp);
        strcpy(newNode->language, trimwhitespace(token));
        token = strtokk(NULL, ",",&sp);
        strcpy(newNode->country, trimwhitespace(token));
        token = strtokk(NULL, ",",&sp);
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


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------

int main(int argc, char *argv[])
{

    if(argc < 3){
        printf("Required parameters: -p <Port Number>\n");
        return 1;
    }
    printf("Received connections from: ");
    fflush(stdout);

    char * portString = argv[2];
    //printf("%s\n", portString);	 
    int port = atoi(portString);
    // int port = 8080;
    
        int server_fd, new_socket;
        struct sockaddr_in address;
        int opt = 1;
        int addrlen = sizeof(address);

        //printf("connection open for clients...\n");
        
        
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

    //printf("PORT: %d\n", port);
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

    char ipstr[INET6_ADDRSTRLEN];

        while ((new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t *)&addrlen)))
        {
            pthread_mutex_lock(&clientIDLock);
            struct sockaddr_in *s = (struct sockaddr_in *)&address;
            port = ntohs(s->sin_port);
            inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);


            printf("<%s>, ", ipstr);
            fflush(stdout);


            ClientArgs * args = malloc(sizeof(*args));
            args->clientID = clientID;
            args->socketFD = new_socket;
            pthread_t tid;
            clientID++;		
            pthread_create(&tid, NULL, clientHandler, args);
            pthread_mutex_unlock(&clientIDLock);

        }
    return 0;
}

int
readn(int f, void *av, int n)
{
    char *a;
    int m, t;

    a = av;
    t = 0;
    while(t < n){
        m = read(f, a+t, n-t);
        if(m <= 0){
            if(t == 0)
                return m;
            break;
        }
        t += m;
    }
    return t;
}

//-----------------------------------------------------------------------------
// Client Handler
//-----------------------------------------------------------------------------
void * clientHandler (void * args){

    // grabbing arguments from the spawned client connection
    ClientArgs * arg = args; 
    int socketFD = (int) arg->socketFD;	
    int clientID = (int) arg->clientID;

    char filename[1024];
    strcpy(filename, "Client");
    char clientIDBuffer[1024];
    snprintf(clientIDBuffer, 1024, "%d", clientID);
    strcat(filename, clientIDBuffer);
    strcat(filename, ".csv"); 

    FILE * file = fopen(filename, "wb");


    char buffer[1024] = {0}; // buffer to read in lines of the files
    char columnLen[5] = {0};
    char columnName[1024] = {0};

    //grabbing the column from socket

    readn(socketFD, columnLen, 2);	


    //printf("length of column: %d\n", atoi(columnLen));

    int columnAmount = atoi(columnLen);
    readn(socketFD, columnName, columnAmount);


    //printf("column: %s\n", columnName);

    /*
       ----------------creating row structs for all of the rows that come in from the client------------------------
       */		

    int fileSize = 0;
    int line = 0;

    int FileArraySize = 1000;
    struct Tokenizer **fileArray = malloc(FileArraySize * sizeof(struct Tokenizer *));
    int gQuoteCount = 0;
    char header[6] = {0};


    readn(socketFD, header, 5);
    header[5] = '\0';
    //printf("buffer received  %s\n", header);		

    char bufferLen[5];
    int a = 0;		
    for(a = 0; a < 4; a++) {
        bufferLen[a] = header[a+1];
    }
    bufferLen[5] = '\0';
    int bufferLength = atoi(bufferLen);
    //printf("bufferLength: %d\n", bufferLength);

    int rowIndex = 1;
    // getting all the unsorted rows from the client
    while(1) 
    {
        //printf("bufferLength: %d\n", bufferLength);
        // reading another line sent by the client
        //printf("header received from client: %s\n", header);

        readn(socketFD, buffer, bufferLength);
        buffer[bufferLength] = '\0';
        //printf("%d:\n%s\n",rowIndex, buffer);

        /*  Tokenizing the row grabbed from the client and putting into row struct array.  */
        struct Tokenizer *newNode;
        newNode = TKCreate(buffer, gQuoteCount);

        //  printf("finished tokenize\n");
        if (fileSize > FileArraySize)
        {
            fileArray = realloc(fileArray, (2 * fileSize * (sizeof(struct Tokenizer *))));
            FileArraySize = (fileSize + FileArraySize);
        }   
        fileArray[fileSize] = newNode;
        fileSize++;
        line++;		



        bzero(buffer, 1024);
        bzero(header, 6);

        // reading the header again to get the next line legnth and also to check if the client is done sending its rows
        readn(socketFD, header, 5);

        header[5] = '\0';
        //  printf("header: %s\n", header);
        //fflush(stdout);

        for(a = 0; a < 4; a++) {
            bufferLen[a] = header[a+1];
        }
        bufferLen[4] = '\0';
        bufferLength = atoi(bufferLen);


        // client is done sending rows
        if(header[0] == '*'){
            //printf("client done sending rows\n");
            break;		
        }
        rowIndex++;
    }

    if (line == 0)
    {
        printf("Error: No Entries in CSV to sort.\n");
        return NULL;
    }

    // printf("size: %d\n", fileSize);
    mymergesort(fileArray, fileSize, columnName);	

    // creating Sorted file on the server, to be used to transmit back to the client
    int u = 0;	
    for(u = 0; u < fileSize; u++){
        printRecord(fileArray[u], file);	
    }
    fclose(file);



    FILE * outputToClient = fopen(filename, "r");

    while (fgets(buffer, 1024, outputToClient) != NULL) {
        // need to write a header first that has a byte for whether the incoming bytes are a line of the csv or not, and also how many bytes it is going to write for a specific line    	
        header[0] = '$';
        int lineLen = strlen(buffer);


        if(lineLen < 100){
            strcat(header, "00");
            char rest[2];
            sprintf(rest, "%d", lineLen);
            strcat(header, rest);
            header[6] = '\0';
            write(socketFD, header, strlen(header));
        }
        else if(lineLen < 1000){
            strcat(header, "0");
            char rest[3];
            sprintf(rest, "%d", lineLen);
            strcat(header, rest);
            header[6] = '\0';
            write(socketFD, header, strlen(header));
        }
        else{
            char rest[4];
            sprintf(rest, "%d", lineLen);
            strcat(header, rest);
            header[6] = '\0';
            write(socketFD, header, strlen(header));	    	
        }

        //printf("header sent to client: %s\n", header);
        //printf("actual buffer length:%d\n", strlen(buffer) );
        //printf("Sorted row that is sent back to client:   %s\n", buffer);

        write(socketFD, buffer, strlen(buffer));

        bzero(buffer, lineLen);
        bzero(header, 6);
    }



    // Sending message back to the client that it can stop grabbing sorted rows
    bzero(buffer, 1024);
    //strcpy(buffer, "DONE");
    //buffer[5] = '\0';
    header[0] = '*';
    write(socketFD, header, 5);



    fclose(outputToClient);



//    remove(filename);





    // Free all memory associated with fileArray structure.
    int i = 0;
    for ( ; i < fileSize && fileArray[i] != NULL; i++)
        free(fileArray[i]);
    free(fileArray);

    // Free memory associated with args.
    free(args);




    //printf("Done processing client: %d\n", clientID);


    //closing socket to make sure we don't lose space on file descriptor table
    close(socketFD);

    pthread_exit(NULL);
}



