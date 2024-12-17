#include<stdio.h>
#include<stdlib.h>

typedef struct 
{
    int pid;
    int arrival_t;
    int burst_t;
    int ct;
    int turn_t;
    int wait_t;
}Process;

void table(Process p[],int n);
void gantt(Process p[],int n);

void main()
{
    int n,sum_turn_t=0,sum_wait_t=0;
    int idle=0;
    printf("Enetr the n of process\n");
    scanf("%d",&n);
    Process p[n];
    printf("Enter the arrival time\n");
    for(int i=0;i<n;i++)
    {
        p[i].pid=i+1;
        printf("P%d :",i+1);
        scanf("%d",&p[i].arrival_t);
        p[i].wait_t=p[i].turn_t=p[i].ct=0;
        
    }
      printf("Enter the burst time\n");
    for(int i=0;i<n;i++)
    {
         printf("P%d :",i+1);
        scanf("%d",&p[i].burst_t);
         p[i].wait_t=p[i].turn_t=p[i].ct=0;
        
    }

    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(p[j].arrival_t>p[j+1].arrival_t)
            {
                Process temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
    p[0].ct=p[0].arrival_t+p[0].burst_t;
    p[0].turn_t=p[0].ct-p[0].arrival_t;
    p[0].wait_t=0;
    sum_wait_t+=p[0].wait_t;
    sum_turn_t+=p[0].turn_t;

    for(int i=1;i<n;i++)
    {
        if(p[i-1].ct<p[i].arrival_t){
            idle=p[i].arrival_t-p[i-1].ct;
        }
        p[i].ct=p[i-1].ct+p[i].burst_t+idle;


        p[i].turn_t=p[i].ct-p[i].arrival_t;
        p[i].wait_t=p[i].turn_t-p[i].burst_t;

        sum_turn_t+=p[i].turn_t;
        sum_wait_t+=p[i].wait_t;
    }

    table(p,n);
    printf("Average turnaround time=%f\n",(sum_turn_t+0.0)/n);
     printf("Average waiting time=%f\n",(sum_wait_t+0.0)/n);
     gantt(p,n);

}
void table(Process p[],int n)
{
    printf("PID\tAT\tBT\tCT\tTT\tWT\n");
    for(int i=0;i<n;i++)
    {
        printf("%d \t %d \t %d \t %d \t %d \t %d \n",p[i].pid,p[i].arrival_t,p[i].burst_t,p[i].ct,p[i].turn_t,p[i].wait_t);
    }
}

void gantt(Process p[],int n)
{
    for(int i=0;i<n;i++){
    printf("------");
    }
    printf("\n");
    printf("|");
    for(int i=0;i<n;i++)
    {
        printf("  P%d  |",p[i].pid);
    }
    printf("\n");
    for(int i=0;i<n;i++){
    printf("------");
    }
    printf("\n");
    for(int i=0;i<n;i++){
        printf(" \t%d",p[i].turn_t);
    }

}