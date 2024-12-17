#include<stdio.h>
#include<stdlib.h>

int isRightAlloc(int Need[],int Available[],int n);

void main()
{
    int n,r;
    printf("Enter the no of processes\n");
    scanf("%d",&n);
    printf("Enter the no of resources\n");
    scanf("%d",&r);
    int Alloc[n][r],Need[n][r],Available[r];

    int Finish[n];

    printf("Enter the Allocation Matrix\n");
	for(int i=0;i<n;i++){
		for(int j=0;j<r;j++){
			scanf("%d",&Alloc[i][j]);
		}
	}

    printf("Enter the Need Matrix\n");
	for(int i=0;i<n;i++){
		for(int j=0;j<r;j++){
            Finish[i]=0;
			scanf("%d",&Need[i][j]);
		}
	}

    printf("Enter the Resource Availablity\n");
	for(int i=0;i<r;i++){
		printf("Resource R%d: ",i+1);
		scanf("%d",&Available[i]);
	}

    int count=n,cycle=0,k=0,b;
    while(count!=0)
    {
        for(int i=0;i<n;i++)
        {
            b=i;
            if(Finish[i]==0 && isRightAlloc(Need[i] ,Available,r)==1){
                Finish[i]=1;
                count--;
                for(int j=0;j<n;j++){
                    Available[j]+=Alloc[i][j];
                    Alloc[i][j]=0;
                    Need[i][j]=0;
                }
                cycle=0;

            }
            cycle++;
            i=b;
        }
        if(cycle>2*n){
            break;
        }
    }
if(count==0)
		printf("No Deadlock detected\n\n");
	else
		printf("DeadLock detected\n\n");



}
int isRightAlloc(int Need[],int Available[],int n)
{
    for(int i=0;i<n;i++)
    {
        if(Need[i]>Available[i])
        return 0;
    }
    return 1;
}





