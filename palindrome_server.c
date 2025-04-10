#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int palindrome(char buffer[])
{
    int ispalindrome=0;
    int length=strlen(buffer);
    char rev[BUFFER_SIZE];

    for(int i=0;i<length;i++)
    {
        rev[i]=buffer[length-i-1];
    }
    rev[length]='\0';

    if(strcmp(rev,buffer)==0)
    {
        ispalindrome=1;
    }

    return ispalindrome;
}


int main()
{
    int sockfd,newsock;
    struct sockaddr_in server,client;
    socklen_t len=sizeof(client);
    char buffer[BUFFER_SIZE];
    char message[BUFFER_SIZE];

    if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(PORT);

    if(bind(sockfd,(struct sockaddr*)&server,sizeof(server))<0)
    {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    if(listen(sockfd,3)<0)
    {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }
    printf("Server waiting for connection\n");

    if((newsock=accept(sockfd,(struct sockaddr*)&client,&len))<0)
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    printf("Connection established\n");

    read(newsock,buffer,sizeof(buffer)-1);

    int result=palindrome(buffer);

    if(result)
    {
        sprintf(message,"%s","It is palindrome");
    }
    else
    {
        sprintf(message,"%s","It is not palindrome");
    }

    send(newsock,message,strlen(message),0);

    close(newsock);
    close(sockfd);
    return 0;
}