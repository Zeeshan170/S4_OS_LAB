#include<stdio.h>
#include<stdlib.h>

int seekTime(int a,int b){
    if(a>b)
        return a-b;

    return b-a;
}

void copy(int arr[],int temp[],int n)
{
    for(int i=0;i<n;i++)
    {
        temp[i]=arr[i];
    }
}
void sort(int arr[],int n)
{
    int temp;
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }

}
int reqIndex(int arr[],int n,int p)
{
    for(int i=0;i<n;i++)
    {
        if(arr[i]>=p)
        return i;
    }

}

void fcfs(int arr[],int n,int p,int max)
{
    printf("FCFS disk\n");
    int seektime=0;
    printf("%d->",p);
    for(int i=0;i<n;i++)
    {
        seektime+=seekTime(p,arr[i]);
        if(i!=n-1)
        {
            printf("%d->",arr[i]);
        }
        else{
            printf("%d",arr[i]);
        }
        p=arr[i];
        printf("\nTotal Head Movements in FCFS = %d\n\n",seekTime);

    }
}

void scan(int arr[],int n,int p,int max)
{
    int temp[n];
    int seektime=0;
    copy(arr,temp,n);
    sort(temp,n);
    int index=reqindex(arr,n,p);
    seektime+=seekTime(p,max);

    printf("%d",p);
    for(int i=index;i<max;i++)
    {
        printf("%d->",temp[i]);
        p=temp[i];
    }
    printf("%d\n%d",max,max);
    for(int i=index-1;i>=0;i--)
    {
        printf("%d->",temp[i]);
    }

}
void main()
{
    int n,p,max;
    printf("Enter the max disk position\n");
    scanf("%d",&max);
    printf("Enetr the noof requests\n");
    scabf("%d",&n);
    int arr[n];
    printf("Enter the req\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    printf("Enter the current position of the disk arm\n");
    scanf("%d",&p);
    int choice;
	do{
		printf("1. FCFS\n");
		printf("2. SCAN\n");
		printf("3. CSCAN\n");
		printf("4. Exit\n");
		printf("Enter your choice: ");
		scanf("%d",&choice);

		switch(choice){
			case 1: 
				fcfs(arr,n,p,max);
				break;
			case 2:
				scan(arr,n,p,max);
				break;
			case 3: 
				cscan(arr,n,p,max);
				break;
			case 4: 
				break;
			default:
				printf("invalid input\n");
				break;
		}
	}while(choice != 4);


}