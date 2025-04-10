#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 8080

int check_prime(int num)
{
    int isprime=1;
    if(num<2)
    {
        isprime=0;
    }
    else
    {
        for(int i=2;i*i<=num;i++)
        {
            if(num%i==0)
            {
                isprime=0;
                break;
            }
        }
    }
    return isprime;
}

int main()
{
    int sockfd,newsock;
    struct sockaddr_in address;
    socklen_t len=sizeof(address);
    char buffer[1024];
    char message[1024];

    sockfd=socket(AF_INET,SOCK_STREAM,0);

    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(PORT);

    bind(sockfd,(struct sockaddr*)&address,sizeof(address));

    listen(sockfd,3);
    printf("Waiting for connection\n");

    newsock=accept(sockfd,(struct sockaddr*)&address,&len);
    printf("Connection established\n");

    read(newsock,buffer,sizeof(buffer));
    int num=atoi(buffer);

    int result=check_prime(num);
    
    if(result)
    {
        sprintf(message,"%d is prime",num);
    }
    else
    {
        sprintf(message,"%d is not prime", num);
    }

    send(newsock,message,strlen(message),0);

    close(newsock);
    close(sockfd);
    return 0;
}