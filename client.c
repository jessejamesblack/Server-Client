#include "socket.h"
#include <stdlib.h>
#define PORT 8080
#define TEST_SIZE 7

int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "1024";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "128.6.13.188", &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    // Need to add code to receive connection id that will later be used to request sorted file and close connection with server.mak
    // Need to change to create thread for each csv file and traverse directory otherwise.
    FILE *fp = fopen("movie_metadata.csv", "r");

    // Throwing away the header, server is hard coded for this .csv file.
    fgets(buffer, 1024, fp);
    
    while (fgets(buffer, 1024, fp) != NULL) {
	write(sock, buffer, strlen(buffer));
    }

    fclose(fp);

    return 0;
}
