#include<stdio.h>
int checkService(int avail[],int need[],int n)
{
    for(int i=0;i<n;i++)
    {
        if(avail[i]<need[i])
        return 0;
    }
    return 1;
}
void main()
{
    int n,r;
    printf("Enter the no of process\n");
    scanf("%d",&n);
    printf("Enter the no of resources\n");
    scanf("%d",&r);
    int need[n][r];
    int max[n][r];
    int alloc [n][r];

    int avail[r];
    printf("Enter the avilable resource vector\n");
    for(int i=0;i<r;i++)
    scanf("%d",&avail[i]);
    printf("Enter the max matrix\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<r;j++)
        {
            scanf("%d",&max[i][j]);
        }
    }
    printf("Enter the allocation matrix\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<r;j++)
        {
            scanf("%d",&alloc[i][j]);
        }
    }
    printf("Need matrix\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<r;j++)
        {
            need[i][j]=max[i][j]-alloc[i][j];
            printf("%d ",need[i][j]);
        }
        printf("\n");
    }

    int count=0;
    int flag[n];
    for(int i=0;i<n;i++)
    {
        flag[i]=0;
    }
    int test,temp[n];
    while(count<n)
    {
        test=0;
        for(int i=0;i<n;i++){
            test++;
            if(checkService(avail,need[i],r)==1 && flag[i]==0)
            {
                test=0;
                temp[count]=i;
                flag[i]=1;
                for(int j=0;j<r;j++)
                {
                    avail[j]+=alloc[i][j];
                    need[i][j]=0;
                    alloc[i][j]=0;
                }
                printf("\n-----------------------------\n");
                printf("P%d has executed to completion\n",i);
                printf("Avail Matrix\n");
                for(int j=0;j<r;j++)
                    printf("%2d",avail[j]);
                    
                printf("the allocation matrix\n");
                for(int j=0;j<n;j++)
                {
                    for(int k=0;k<r;k++)
                    {
                        printf("%d ",alloc[j][k]);
                    }
                    printf("\n");
                }

                printf("the  need matrix\n");
                for(int j=0;j<n;j++)
                {
                    for(int k=0;k<r;k++)
                    {
                        printf("%d ",need[j][k]);
                    }
                    printf("\n");
                }
            }
        }
        if(test>2*n){
            printf("\nThere is no safe sequence\nDEADLOCK STATE\n");
            break;
        }
    }
    if(count==n){
        printf("\nSAFE SEQUENCE\n");
        for(int i=0;i<n;i++){
            printf("P%d => ",temp[i]);
        }
        printf("\n");
    }

}