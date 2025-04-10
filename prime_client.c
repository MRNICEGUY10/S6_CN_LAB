#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 8080

int main()
{
    int sockfd;
    struct sockaddr_in server;
    char buffer[1024];
    char number[1024];

    sockfd=socket(AF_INET,SOCK_STREAM,0);

    server.sin_family=AF_INET;
    server.sin_port=htons(PORT);
    server.sin_addr.s_addr=inet_addr("127.0.0.1");

    connect(sockfd,(struct sockaddr*)&server,sizeof(server));
    printf("Connected to server\n");

    printf("Enter a number : ");
    scanf("%s", number);

    send(sockfd,number,strlen(number),0);

    read(sockfd,buffer,sizeof(buffer));
    printf("%s\n", buffer);

    close(sockfd);
    return 0;
}