#include<stdio.h>
#define infinity 9999
#define MAX 10

int cost[MAX][MAX],dist[MAX][MAX],next_hop[MAX][MAX];
int nodes;

void initialize()
{
    for(int i=0;i<nodes;i++)
    {
        for(int j=0;j<nodes;j++)
        {
            dist[i][j]=cost[i][j];
            next_hop[i][j]=j;
        }
    }
}

void update_route()
{
    int updated;
    do
    {
        updated=0;
        for(int i=0;i<nodes;i++)
        {
            for(int j=0;j<nodes;j++)
            {
                for(int k=0;k<nodes;k++)
                {
                    if(dist[i][j]>dist[i][k]+dist[k][j])
                    {
                        dist[i][j]=dist[i][k]+dist[k][j];
                        next_hop[i][j]=next_hop[i][k];
                        updated=1;
                    }
                }
            }
        }
    }while(updated);
}

void display()
{
    for(int i=0;i<nodes;i++)
    {
        printf("\nRouting table of router %d\n", i+1);
        printf("Destination\tDistance\tNext_hop\n");
        for(int j=0;j<nodes;j++)
        {
            printf("%d\t\t%d\t\t%d\t\n", j+1,dist[i][j],next_hop[i][j]+1);
        }
    }
}

int main()
{
    printf("Enter the no. of routers : ");
    scanf("%d", &nodes);
    printf("Enter the cost matrix (9999 if no direct link): ");
    for(int i=0;i<nodes;i++)
    {
        for(int j=0;j<nodes;j++)
        {
            scanf("%d", &cost[i][j]);
            if(i==j)
            {
                cost[i][j]=0;
            }
        }
    }
    initialize();
    update_route();
    display();
    return 0;
}