#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int sockfd;
    struct sockaddr_in server;
    char buffer[BUFFER_SIZE];
    char value[BUFFER_SIZE];

    if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server.sin_family=AF_INET;
    server.sin_port=htons(PORT);
    server.sin_addr.s_addr=inet_addr("127.0.0.1");

    if(connect(sockfd,(struct sockaddr*)&server,sizeof(server))<0)
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    printf("Connected to server\n");

    printf("Enter a string : ");
    scanf("%s", value);

    send(sockfd,value,strlen(value),0);

    read(sockfd,buffer,sizeof(buffer));
    printf("%s", buffer);

    close(sockfd);
    return 0;

}