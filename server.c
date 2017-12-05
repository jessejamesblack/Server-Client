	#include "socket.h"
	#include <string.h>
	#include <pthread.h>
	#define PORT 8080
	void * clientHandler(void *);
	
	int main(int argc, char const *argv[])
	{
	    int server_fd, new_socket, valread;
	    struct sockaddr_in address;
	    int opt = 1;
	    int addrlen = sizeof(address);
	    char buffer[1024] = {0};
	    char *hello = "Hi jesse you suck";
	
		printf("waiting for client...\n");
	    // Creating socket file descriptor
	    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	    {
	        perror("socket failed");
	        exit(EXIT_FAILURE);
	    }
	
	    // Forcefully attaching socket to the port 8080
	    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
	                   &opt, sizeof(opt)))
	    {
	        perror("setsockopt");
	        exit(EXIT_FAILURE);
	    }
	    address.sin_family = AF_INET;
	    address.sin_addr.s_addr = INADDR_ANY;
	    address.sin_port = htons(PORT);
	
	    // Forcefully attaching socket to the port 8080
	
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
		pthread_t tids[1000];
		int tidCount = 0;
		pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	   while ((new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t *)&addrlen)))
	   {
			puts("connection accepted, spawning thread to process the client");
			pthread_mutex_lock(&mutex);
			tidCount++;
			void * arg = (void *) new_socket;
			pthread_create(&tids[tidCount - 1], NULL, clientHandler, arg); 
			pthread_mutex_unlock(&mutex);
	   }
	    valread = read(new_socket, buffer, 1024);
	    printf("%s\n", buffer);
	    send(new_socket, hello, strlen(hello), 0);
	    printf("Hello message sent\n");   
		int j = 0;
		for(j = 0; j < tidCount; j++){
			pthread_join(tids[j], NULL);	
		}
	 return 0;
	}
	
	
	void * clientHandler (void * args){
	int sock = (intptr_t)args;
	    int read_size = 0;
	    char client_message[2000];
	
	while( (read_size = recv(sock , client_message , sizeof(client_message) , 0)) > 0 ){
	    printf("Read Text: %.*s", read_size, client_message);
	 }
		
		if(read_size == 0)
		{
	    	printf("Client disconnected\n");
	    	fflush(stdout);
		}
		else if(read_size == -1)
		{
	   	 perror("recv failed");
		}
	
		pthread_exit(NULL);
	}



