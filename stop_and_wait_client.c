#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/time.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define TIMEOUT 3

int main()
{
    int sock=0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE]={0};
    char packet[50];
    struct timeval tv;

    if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("Socket Creation Failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);

    if(inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr)<=0)
    {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }

    if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
    {
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }

    printf("Client : Connection Established");

    tv.tv_sec=TIMEOUT;
    tv.tv_usec=0;
    setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,(const char*)&tv,sizeof(tv));

    int packet_number=1;
    while(packet_number<=5)
    {
        sprintf(packet, "%d", packet_number);
        printf("Client : Sending packet %d\n", packet_number);
        send(sock,packet,strlen(packet),0);

        int valread=read(sock,buffer,BUFFER_SIZE);
        if(valread>0 && strcmp(buffer,"ACK")==0)
        {
            printf("Client : ACK recieved for packet %d\n", packet_number);
            packet_number++;
        }
        else
        {
            printf("Client : Timeout !! Retransmitting packet %d\n", packet_number);
        }

        memset(buffer,0,BUFFER_SIZE);
    }

    printf("Clinet : All packets sent seccessfully\n");
    close(sock);
    return 0;
}