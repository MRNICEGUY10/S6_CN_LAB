#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int sockfd;
    struct sockaddr_in server;
    socklen_t len=sizeof(server);
    char buffer[1024]="Hello from client";
    char recieve[1024];

    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    server.sin_family=AF_INET;
    server.sin_port=htons(8080);
    server.sin_addr.s_addr=inet_addr("127.0.0.1");

    sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr*)&server,len);
    memset(recieve,0,sizeof(recieve));
    recvfrom(sockfd,recieve,sizeof(recieve),0,(struct sockaddr*)&server,&len);
    printf("Message : %s\n", recieve);

    close(sockfd);
    return 0;
}