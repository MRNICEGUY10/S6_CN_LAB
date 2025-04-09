#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int newsock)
{
    char buffer[BUFFER_SIZE]={0};
    char filename[BUFFER_SIZE]={0};

    int valread=recv(newsock,filename,BUFFER_SIZE,0);
    if(valread<0)
    {
        char err_msg[BUFFER_SIZE]="File name not recieved";
        send(newsock,err_msg,strlen(err_msg),0);
        close(newsock);
        return;
    }

    FILE *file=fopen(filename,"r");
    if(file==NULL)
    {
        perror("File not found");
        exit(EXIT_FAILURE);
    }
    else
    {
        while(fgets(buffer,BUFFER_SIZE,file)!=NULL)
        {
            send(newsock,buffer,strlen(buffer),0);
            memset(buffer,0,BUFFER_SIZE);
        }
        printf("File sent to client\n");
        fclose(file);
    }
    close(newsock);
}


int main()
{
    int sockfd,newsock;
    struct sockaddr_in server,client;
    socklen_t len=sizeof(client);

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
        perror("LIstening failed");
        exit(EXIT_FAILURE);
    }
    printf("Server listening for connection\n");

    while(1)
    {
        if((newsock=accept(sockfd,(struct sockaddr*)&client,&len))<0)
        {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }
        printf("Connection established\n");

        handle_client(newsock);
    }
    close(sockfd);
    return 0;
}