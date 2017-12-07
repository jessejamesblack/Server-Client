#include "client.h"
#define TEST_SIZE 7

pthread_mutex_t send_file_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t totalThreadsLock = PTHREAD_MUTEX_INITIALIZER;

pthread_t tids[100000]; 
int totalThreads = 0;
char header[6];
int totalFiles = 0;

int sockfd = 0;

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
        if (strstr(file->d_name, "Client"))
        {
                return -1;
        }
        if (strstr(file->d_name, "output"))
        {
                return -1;
        }
        if (strcasecmp(get_filename_ext(file->d_name), "csv") == 0)
        {
                return 0;
        }
        
        return -1;
}


int main(int argc, char const *argv[])
{
    long globalCounter = 0;
    if (argc < 3)
    {
        printf("Invalid amount of arguments.\n");
        return 1;
    }

    char *default_dirName = "./";
    char *default_outName = "./";

    char *columnName;
    char *directory = default_dirName;
    char *output_directory = default_outName;
    char *port_number;
    char *host_name;

    char dirr[4096];
    char out_folder[4096];
    
    // The req_paramate
    int req_parameters = 3;
    int found_par = 0;

    // Validate input parameters.
    int i = 1;
    while (i < argc)
    {
	if (!strcmp(argv[i], "-c"))
	{
	    columnName = (char*)argv[i+1];
	    i += 2;
	    found_par++;
	}
	else if (!strcmp(argv[i], "-d"))
	{
	    strcpy(dirr, argv[i+1]);
	    strcat(dirr, "/");
	    directory = dirr;
	    i += 2;
	}
	else if (!strcmp(argv[i], "-o"))
	{
	    strcpy(out_folder, argv[i+1]);
	    strcat(out_folder, "/");
	    output_directory = out_folder;
	    i += 2;
	}
	else if (!strcmp(argv[i], "-p"))
	{
	    port_number = (char*)argv[i+1];
	    i += 2;
	    found_par++;
	}
	else if (!strcmp(argv[i], "-h"))
	{
	    host_name = (char*)argv[i+1];
	    i += 2;
	    found_par++;
	}
	else
	{
	    printf("Invalid option parameter, use -c to sort column.\n");
	    printf(" -o for output file, -d for output directory\n");
	    printf(" -h for hostname, -p for port number\n");
	    return 1;
	}
    }

    if (found_par != req_parameters)
    {
	printf("Required parameters: -c -h -p\n");
	return 1;
    }

   // printf("directory: %s\n", directory);
   // printf("output directory: %s\n", output_directory);
  //  printf("column name: %s\n", columnName);
  //  printf("port number: %s\n", port_number);
  //  printf("host name: %s\n", host_name);

struct addrinfo hints, *servinfo, *p;
int rv;
memset(&hints, 0, sizeof hints);
hints.ai_family = AF_INET; // use AF_INET6 to force IPv6
hints.ai_socktype = SOCK_STREAM;

if ((rv = getaddrinfo(host_name, port_number, &hints, &servinfo)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    exit(1);
}

// loop through all the results and connect to the first we can
 for(p = servinfo; p != NULL; p = p->ai_next) {
     if ((sockfd = socket(p->ai_family, p->ai_socktype,p->ai_protocol)) == -1) {
             perror("socket");
             continue;
     }

     if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
             perror("connect");
             close(sockfd);
             continue;
        }

     break; // if we get here, we must have connected successfully
  }
if (p == NULL) {
     fprintf(stderr, "failed to connect\n");
     exit(2);
 }                                                                         


    char buffer[50];
    bzero(buffer, 50);
    
    if (strlen(columnName) < 10)
		sprintf(buffer, "0%d", strlen(columnName)); 		    
    else
    	sprintf(buffer, "%d", strlen(columnName));
    	
    strcat(buffer, columnName);
    write(sockfd, buffer, strlen(buffer));
   // printf("%s\n", buffer);

    
	// traverse directories spawning threads to send files to the server
	// need to have a join loop after the traverse directories is done
	// after the join loop, create a new result file and set everything up so the server can write the results back to this client
	// have to send the server a dump request  
	
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

		  int obool = 0;
        ArgsDir *argsdir = malloc(sizeof(*argsdir));
        argsdir->obool = obool;
        argsdir->path = malloc(strlen(directory) + 1);
        argsdir->outputdirectory = malloc(strlen(output_directory) + 1);
        argsdir->columnName = malloc(strlen(columnName) + 1);
        strcpy(argsdir->path, directory);
        strcpy(argsdir->outputdirectory, output_directory);
        strcpy(argsdir->columnName, columnName);	
	
	
	    sortDir(argsdir);
	    
	    
	    int y = 0;
	    for(y = 0; y < totalThreads; y++){
	    	pthread_join(tids[y], NULL);
	    }
	   // printf("All files have been sent to the server.\n");	
	if(totalFiles != 0){

	char outputty[1024];
   strcpy(outputty, output_directory);
   strcat(outputty, "/");
   strcat(outputty, "AllFiles-sorted-<");
   strcat(outputty, columnName);
   strcat(outputty, ">.csv");
   
   int b = 0;
	char buff[1024];
	
	FILE * finalOutput = fopen(outputty, "w");	
	
   fprintf(finalOutput, "color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes\n");
				 
		 
		 /*
		 ----------DUMP REQUEST----------
		 */
		 header[0] = '*';
	    header[6] = '\0';
	    write(sockfd, header, strlen(header));
	    
	// read lines from socket and write into finalOutput file
	 int index = 0;
	 while(1) {	
	 	   b = recv(sockfd, buff, 1024, 0);
	 		//printf("%d\n", index);
			index++;
			if(strstr(buff, "DONE")){
				fwrite(buff, 1, b-4 ,finalOutput);	
				break;
			}
			fwrite(buff, 1, b ,finalOutput);	
			bzero(buff, 1024);
	 }

	
	fclose(finalOutput);
}
   // printf("done, received final result file\n");
    return 0;
}

void *sortDir(void *argp)
{
        ArgsDir *args = argp;
        int obool = args->obool;
        char *path = args->path;
        char *columnName = args->columnName;
        char *outputdirectory = args->outputdirectory;

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

								// recursively search for more files to send to the server
                        sortDir(argsdir);
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
 
                          CArgs *arg = malloc(sizeof(*arg));
   							  arg->path = path;
   							  arg->filename = currentDirFile->d_name;
   							  //printf("arg->path: %s\n", arg->path);
   							  //printf("arg->filename: %s\n", arg->filename);

                        pthread_mutex_lock(&totalThreadsLock);
                        totalThreads++;
                        totalFiles++;
                        pthread_create(&tids[totalThreads - 1], NULL, send_file, arg);
                        pthread_mutex_unlock(&totalThreadsLock);
                }
                // INVALID file, not a directory or a valid csv file
                else
                {
                        continue;
                }
        }

        return NULL;
}


void * send_file(void * args)
{
    pthread_mutex_lock(&send_file_lock);

    CArgs *arg = args;
    char buffer[1024] = {0};

    char descriptor[1024];
    strcpy(descriptor, arg->path);
    strcat(descriptor, "/");
    strcat(descriptor, arg->filename);

    FILE *fp = fopen(descriptor, "r");

    // Throwing away the header, server is hard coded for this .csv file.
    fgets(buffer, 1024, fp);
    
    
 while (fgets(buffer, 1024, fp) != NULL) {
		// need to write a header first that has a byte for whether the incoming bytes are a line of the csv or not, and also how many bytes it is going to write for a specific line    	
    	header[0] = '$';
    	int lineLen = strlen(buffer);
    	
    	if(lineLen < 1000){
    		strcat(header, "0");
    		char rest[3];
    		sprintf(rest, "%d", lineLen);
    		strcat(header, rest);
    		header[6] = '\0';
    		//printf("%s\n", header);
    		write(sockfd, header, strlen(header));
    	}
    	else{
    		char rest[4];
    		sprintf(rest, "%d", lineLen);
    		strcat(header, rest);
    		header[6] = '\0';
    		//printf("%s\n", header);
    		write(sockfd, header, strlen(header));	    	
    	}
    	//printf("actual buffer length:%d\n", strlen(buffer) );
		write(sockfd, buffer, strlen(buffer));
		bzero(buffer, lineLen);
		bzero(header, 6);
    }
   
    fclose(fp);
   
    pthread_mutex_unlock(&send_file_lock);
    pthread_exit(NULL);
}

