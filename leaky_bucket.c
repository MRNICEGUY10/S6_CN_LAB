#include<stdio.h>
#include<stdlib.h>

void leaky_bucket(int bucket_capacity,int leak_rate,int num_packets,int packets[])
{
    int bucket=0;

    printf("Time\tIncoming\tBucket\tLeaked\tRemaining\n");
    for(int i=0;i<num_packets;i++)
    {
        printf("%d\t%d\t",i+1,packets[i]);
        
        bucket=bucket+packets[i];
        if(bucket>bucket_capacity)
        {
            printf("%d (Overflowed,Dropped %d)", bucket_capacity,bucket-bucket_capacity);
            bucket=bucket_capacity;
        }
        else
        {
            printf("\t%d\t", bucket);
        }

        int leaked=(bucket>=leak_rate ? leak_rate : bucket);
        bucket=bucket-leaked;
        printf("%d\t%d\n", leaked,bucket);
    }

    int time=num_packets+1;
    while(bucket>0)
    {
        int leaked=(bucket>=leak_rate ? leak_rate : bucket);
        printf("%d\t%d\t\t%d\t%d\t%d\n", time,0,bucket,leaked,bucket-leaked);
        bucket=bucket-leaked;
        time++;
    }
}

int main()
{
    int bucket_capacity,leak_rate,num_packets;
    printf("Enter the bucket capacity : ");
    scanf("%d", &bucket_capacity);
    printf("Enter the leak rate : ");
    scanf("%d", &leak_rate);
    printf("Enter the number of packets : ");
    scanf("%d", &num_packets);
    int packets[num_packets];
    printf("Enter the size of each packets : ");
    for(int i=0;i<num_packets;i++)
    {
        scanf("%d", &packets[i]);
    }

    printf("Leaky Bucket Simulation\n");
    leaky_bucket(bucket_capacity,leak_rate,num_packets,packets);
    return 0;
}