#include "client.h"
#include "socket.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#define TEST_SIZE 7

pthread_mutex_t send_file_lock = PTHREAD_MUTEX_INITIALIZER;

int sockfd = 0;

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

    char dir[4096];
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
	    strcpy(dir, argv[i+1]);
	    strcat(dir, "/");
	    directory = dir;
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

    printf("directory: %s\n", directory);
    printf("output directory: %s\n", output_directory);
    printf("column name: %s\n", columnName);
    printf("port number: %s\n", port_number);
    printf("host name: %s\n", host_name);

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
//freeddrinfo(servinfo);

   // struct sockaddr_in address;
   // struct sockaddr_in serv_addr;
   // int valread;
   // if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
   // {
    //    printf("\n Socket creation error \n");
  //      return -1;
//    }

  //  memset(&serv_addr, '0', sizeof(serv_addr));

   // serv_addr.sin_family = AF_INET; 
   // serv_addr.sin_port = htons(atoi(port_number));
   	
//	struct addrinfo hints, *result;
//	memset(&hints, 0, sizeof(struct addrinfo));
//	hints.ai_family = AF_NET;
//	hints.ai_socktype = SOCK_STREAM;
//	hints.ai_flags = AI_PASSIVE;
//	int s;
//	s = getaddrinfo(host_name, "80", &hints, &results); 
	
    // Convert IPv4 and IPv6 addresses from text to binary form
  //  if (inet_pton(AF_INET, "128.6.13.203", &serv_addr.sin_addr) <= 0)
   // {
    //    printf("\nInvalid address/ Address not supported \n");
     //   return -1;
   // }

//    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
 //   {
  //      printf("\nConnection Failed \n");
   //     return -1;
   // }

    char buffer[50];
    bzero(buffer, 50);
    
    if (strlen(columnName) < 10)
		sprintf(buffer, "0%d", strlen(columnName)); 		    
    else
    	sprintf(buffer, "%d", strlen(columnName));
    	
    strcat(buffer, columnName);
    write(sockfd, buffer, strlen(buffer));
    printf("%s\n", buffer);

    // Need to add code to receive connection id that will later be used to request sorted file and close connection with server.mak
    // Need to change to create thread for each csv file and traverse directory otherwise.
    CArgs *arg = malloc(sizeof(*arg));
    arg->path = "./";
    arg->filename = "movie_metadata.csv";

    pthread_t tid;
    pthread_t tid1;
    pthread_t tid2;

    pthread_create(&tid, NULL, send_file, arg);
    //pthread_create(&tid1, NULL, send_file, arg);
    //pthread_create(&tid2, NULL, send_file, arg);
    pthread_join(tid, NULL);
    //pthread_join(tid1, NULL);
    //pthread_join(tid2, NULL);
    
    return 0;
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
		write(sockfd, buffer, strlen(buffer));
    }
    bzero(buffer, 1024);
//   strcat(buffer, "FILE DONE");
    write(sockfd, buffer, strlen(buffer));

    fclose(fp);
   
    pthread_mutex_unlock(&send_file_lock);
    pthread_exit(NULL);
}
