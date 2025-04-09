#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int sockfd;
    struct sockaddr_in server,client;
    socklen_t len=sizeof(client);
    char buffer[1024];
    char message[1024]="Hello from server";

    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(8080);

    bind(sockfd,(struct sockaddr*)&server,sizeof(server));

    recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&client,&len);
    printf("Message : %s\n", buffer);

    sendto(sockfd,message,strlen(message),0,(struct sockaddr*)&client,len);
    close(sockfd);
    return 0;
}