#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define TOTAL_PACKETS 5
#define TIMEOUT 3

int simulate_ack()
{
    return rand()%10 < 7;
}

int main()
{
    srand(time(0));

    int packet=1;
    int ack_recieved;

    while(packet<=TOTAL_PACKETS)
    {
        printf("Sender : Packet %d send\n", packet);

        sleep(1);
        ack_recieved=simulate_ack();

        if(ack_recieved)
        {
            printf("Reciever : Ack recieved for packet %d\n", packet);
            packet++;
        }
        else
        {
            printf("Reciever : Ack lost for packet %d, Retransmitting....\n", packet);
            sleep(TIMEOUT);
        }
    }
    printf("All packets send successfully\n");
    return 0;
}