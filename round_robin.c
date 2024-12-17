#include<stdio.h>
#include<stdlib.h>

typedef struct Process
{
    int pid;
    int arrival_t;
    int burst_t;
    int turn_t;
    int wait_t;
    int ct;
    int rem_t;

}Process;
void table(Process p[],int n);
void gantt(Process p[],int n);

int main()
{
    Process p[100];
    int sum_turn_t=0;
    int sum_wait_t=0;
    int current_t=0;
    int time_quant;
    int comp_process=0;
    int i,j,k=0;
    int n;

    printf("Enter the time quatum\n");
    scanf("%d",&time_quant);

    printf("Enter the no of processes\n");
    scanf("%d",&n);


    printf("Enter the arrival time\n");
    for(i=0;i<n;i++)
    {
        p[i].pid=i+1;
        printf("P%d ",i+1);
        scanf("%d",&p[i].arrival_t);
        p[i].ct=p[i].turn_t=p[i].wait_t=0;
    }
    
    printf("Enter the burst time\n");
    for(i=0;i<n;i++)
    {
        printf("P%d ",i+1);
        scanf("%d",&p[i].burst_t);
        p[i].rem_t=p[i].burst_t;
    }

    i=0;
    while(1)
    {
        if(p[i].rem_t>0)
        {
            if(p[i].rem_t>time_quant)
            {
                p[i].rem_t-=time_quant;
                current_t+=time_quant;
            }
            else
            {
                current_t+=p[i].rem_t;
                p[i].rem_t=0;
                p[i].ct=current_t;

                p[i].turn_t=p[i].ct-p[i].arrival_t;
                p[i].wait_t=p[i].turn_t-p[i].burst_t;

                sum_turn_t+=p[i].turn_t;
                sum_wait_t+=p[i].wait_t;
                comp_process++;

                if(comp_process==n)
                {
                    break;
                }

            }
        }
        if(i==n-1)
        {
            i=0;
        }
        else{
            i++;
        }
    }

    table(p,n);
    gantt(p,n);
    printf("The avg trunaround time is %f\n",(sum_turn_t+0.0)/n);
    printf("The avg waiting time is %f",(sum_wait_t+0.0)/n);


}
void table(Process p[],int n)
{
    printf("PID\tAT\tBT\tTT\tWT\n");
    for(int i=0;i<n;i++)
    {
        printf("%d \t %d \t %d \t %d \t %d\n",p[i].pid,p[i].arrival_t,p[i].burst_t,p[i].turn_t,p[i].wait_t);
    }
}
void gantt(Process p[],int n)
{
    printf("Gantt chart\n");
    printf("-------------------\n");
    printf("|");
    for(int i=0;i<n;i++)
    {
        printf(" P%d  |",p[i].pid);

    }
    printf("\n");
    printf("-------------------\n");
    for(int i=0;i<n;i++)
    {
        printf("  %d    ",p[i].turn_t);
    }
    printf("\n");
}