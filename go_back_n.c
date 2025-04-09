#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define TOTAL_PACKETS 10
#define WINDOW_SIZE 4

int simulate_ack()
{
    return rand()%10 < 7;
}


int main()
{
    srand(time(0));

    int base=1;
    int next_seq_num=1;

    while(base<=TOTAL_PACKETS)
    {
        printf("\n----SENDING PACKETS----\n");
        while(next_seq_num<base+WINDOW_SIZE && next_seq_num<=TOTAL_PACKETS)
        {
            printf("Sender : Sending packet %d\n", next_seq_num);
            next_seq_num++;
        }

        sleep(1);

        printf("\n----WAITING FOR ACKNOWLEDGEMENT----\n");
        for(int i=base;i<next_seq_num;i++)
        {
            if(simulate_ack())
            {
                printf("Ack recieved for packet %d\n", i);
            }
            else
            {
                printf("Ack lost for packet %d\n", i);
                printf("Retransmitting from packet %d\n", i);
                next_seq_num=i;
                break;
            }
        }
        base=next_seq_num;
        sleep(1);
    }
    printf("All packets send successfully\n");
    return 0;
}