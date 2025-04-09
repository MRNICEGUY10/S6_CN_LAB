#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define TOTAL_PACKETS 10
#define WINDOW_SIZE 4

int simulate_ack()
{
    return rand()%10 <7;
}

int main()
{
    srand(time(0));
    
    int base=1;
    int acknowledged[TOTAL_PACKETS+1]={0};

    while(base<=TOTAL_PACKETS)
    {
        printf("\n----SENDING PACKETS----\n");
        for(int i=base;i<base+WINDOW_SIZE && i<=TOTAL_PACKETS;i++)
        {
            if(!acknowledged[i])
            {
                printf("Sender : Sending packet %d\n", i);
            }
        }

        sleep(1);

        printf("\n----WAITING FOR ACKNOWLEDGEMENT----\n");
        for(int i=base;i<base+WINDOW_SIZE && i<=TOTAL_PACKETS;i++)
        {
            if(!acknowledged[i])
            {
                if(simulate_ack())
                {
                    printf("Ack recieved for packet %d\n", i);
                    acknowledged[i]=1;
                }
                else
                {
                    printf("Ack lost for packet %d\n", i);
                }
            }
        }

        int all_acknowledged = 1;
        for (int i = base; i < base + WINDOW_SIZE && i <= TOTAL_PACKETS; i++) 
        {
            if (!acknowledged[i]) 
            {
                all_acknowledged = 0;
                break;
            }
        }

        if (all_acknowledged) 
        {
            base += WINDOW_SIZE;
        }

        sleep(1);
    }

    printf("All packets sent successfully\n");
    return 0;
}