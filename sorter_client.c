#include "sorter_client.h"

pthread_mutex_t send_file_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t totalThreadsLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t sendRow = PTHREAD_MUTEX_INITIALIZER;

int totalFiles = 0;
int sockfd = 0;

const char *get_filename_ext(const char *filename)
{
    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename)
        return "";
    return dot + 1;
}

int is_Valid_CSV(struct dirent *file, char * columnName, char * path)
{
    if (strstr(file->d_name, "-sorted-"))
    {
        return -1;
    }
    if (strcasecmp(get_filename_ext(file->d_name), "csv") == 0)
    {
        char filename[4096];
        strcpy(filename, path);
        strcat(filename, "/");
        strcat(filename, file->d_name); 
        FILE * test = fopen(filename, "r");
        char * buffer = NULL;
        size_t n = 0;
        getline(&buffer, &n, test);

        if(strstr(buffer, columnName) != NULL){
           fclose(test);
           return 0;
        }
        else{
            fclose(test);
            return -1;
        }
    }

            
    return -1;
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


int main(int argc, char const *argv[])
{
    char header[6];
    if (argc < 7)
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
        close(sockfd);
        return 1;
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

    struct addrinfo hints, *servinfo, *p;
    int rv;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET; 
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(host_name, port_number, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        exit(1);
    }

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

        break; 
    }
    if (p == NULL) {
        fprintf(stderr, "failed to connect\n");
        exit(2);
    }                                                                         


    char buffer[50];
    bzero(buffer, 50);

    if (strlen(columnName) < 10)
        sprintf(buffer, "0%lu", strlen(columnName)); 		    
    else
        sprintf(buffer, "%lu", strlen(columnName));

    strcat(buffer, columnName);
    write(sockfd, buffer, strlen(buffer));


    int obool = 0;
    ArgsDir *argsdir = malloc(sizeof(*argsdir));
    argsdir->obool = obool;
    argsdir->path = malloc(strlen(directory) + 1);
    argsdir->outputdirectory = malloc(strlen(output_directory) + 1);
    argsdir->columnName = malloc(strlen(columnName) + 1);
    strcpy(argsdir->path, directory);
    strcpy(argsdir->outputdirectory, output_directory);
    strcpy(argsdir->columnName, columnName);	


    //send all the files to server
    sortDir(argsdir); 

    //printf("All files have been sent to the server.\n");	
    if(totalFiles != 0){

        char outputty[1024];
        strcpy(outputty, output_directory);
        strcat(outputty, "/");
        strcat(outputty, "AllFiles-sorted-<");
        strcat(outputty, columnName);
        strcat(outputty, ">.csv");

        char buff[1024];

        FILE * finalOutput = fopen(outputty, "w");	

        // printing header to output file
        fprintf(finalOutput, "color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes\n");


        // ----------DUMP REQUEST----------

        bzero(header, 6);

        header[0] = '*';
        header[5] = '\0';
        write(sockfd, header, 5);
        bzero(header, 6);


        // ----------GETTING THE SORTED ROWS BACK----------    

        readn(sockfd, header, 5);	
        //printf("header received from server: %s\n", header);	

        char bufferLen[5];
        int a = 0;		
        for(a = 0; a < 4; a++) {
            bufferLen[a] = header[a+1];
        }
        bufferLen[4] = '\0';
        int bufferLength = atoi(bufferLen);
        //printf("initial bufferLength: %d\n", bufferLength);
        int rowIndex = 1;

        while(header[0] != '*') 
        {
            //printf("bufferLength: %d\n", bufferLength);

            // reading another line sent by the client
            readn(sockfd, buff, bufferLength);
            buff[bufferLength] = '\0';
            //printf("%d:\n%s\n",rowIndex, buff);


            fprintf(finalOutput, "%s", buff);	
            bzero(buff, 1024);
            bzero(header, 6);


            // reading the header again to get the next line legnth
            readn(sockfd, header, 5);
            header[5] = '\0';
            // printf("\nheader: %s\n", header);


            for(a = 0; a < 4; a++) {
                bufferLen[a] = header[a+1];
            }
            bufferLen[4] = '\0';
            bufferLength = atoi(bufferLen);

            rowIndex++;
        }


        fclose(finalOutput);
    }

    close(sockfd);

    // printf("done, received final result file, total files sent to server: %d\n", totalFiles);
    return 0;
}




void *sortDir(void *argp)
{
    pthread_t tidsDir[10000];
    int files = 0;
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
        else if (is_Valid_CSV(currentDirFile, columnName, path) == 0)
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
            totalFiles++;
            //printf("total valid files: %d\n", totalFiles);
            pthread_mutex_unlock(&totalThreadsLock);
            files++;
            pthread_create(&tidsDir[files - 1], NULL, send_file, arg);
            pthread_join(tidsDir[files-1], NULL);
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
    char header[6];
    bzero(header, 6);
    CArgs *arg = args;
    char buffer[1024] = {0};
    //bzero(buffer, 1024);

    char head[1024] = {0};
    //printf("file: %s\n  entered.", arg->filename);
    char descriptor[1024];
    strcpy(descriptor, arg->path);
    strcat(descriptor, "/");
    strcat(descriptor, arg->filename);

    FILE *fp = fopen(descriptor, "r");
    if(fp != NULL)
    {
        // Throwing away the header, server is hard coded for this .csv file.
        fgets(head, 1024, fp);


        while ((fgets(buffer, 1024, fp) != NULL) ) {
            //printf("\nin this loop\n");
            // need to write a header first that has a byte for whether the incoming bytes are a line of the csv or not, and also how many bytes it is going to write for a specific line    	
            header[0] = '$';
            int lineLen = strlen(buffer);


            if(lineLen < 100) {
                strcat(header, "00");
                char rest[2];
                sprintf(rest, "%d", lineLen);
                strcat(header, rest);
                header[5] = '\0';
                //printf("header:  %s\n", header);
                //printf("strlen of header: %d\n", strlen(header));
                write(sockfd, header, strlen(header));
                //printf("header written successfully1\n");

            }
            else if(lineLen < 1000){
                strcat(header, "0");
                char rest[3];
                sprintf(rest, "%d", lineLen);
                strcat(header, rest);
                header[5] = '\0';
                //printf("header:  %s\n", header);
                //printf("strlen of header: %d\n", strlen(header));
                write(sockfd, header, strlen(header));
                //printf("header written successfully1\n");
            }
            else{
                char rest[4];
                sprintf(rest, "%d", lineLen);
                strcat(header, rest);
                header[5] = '\0';
                //printf("header:  %s\n", header);
                //printf("strlen of header: %d\n", strlen(header));
                write(sockfd, header, strlen(header));	
                //	printf("header written successfully2\n");    	
            }

            //printf("header sent over?: %s\n", header);    	
            //printf("actual buffer length:%d\n", strlen(buffer));

            write(sockfd, buffer, strlen(buffer));

            //printf("is it hanging at the write statement?\n");		


            //printf("%d unsorted line sent to server:\n%s", lineNum, buffer);
            //lineNum++;

            bzero(buffer, lineLen);
            bzero(header, 6);

        }




        fclose(fp);
    }

    //printf("file: %s\n  done.\n", arg->filename);

    pthread_exit(NULL);

}

