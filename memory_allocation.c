#include<stdio.h>
#include<stdlib.h>

typedef struct 
{
    int size,rem,flag;
}MemoryBlocks;

void printalloc(MemoryBlocks B[],int n)
{
    printf("Block  Size  Allocation\n");
    for(int i=0;i<n;i++)
    {
        printf("%d  %d",i+1,B[i].size);
        if(B[i].flag==1)
        {
            printf("  %d",B[i].size-B[i].rem);
            


        }
        else{
            printf("  -");
        }
        printf("\n");
    }
}
void takeinput(MemoryBlocks B[],int n)
{
    printf("ENter the size\n");
    for(int i=0;i<n;i++)
    {
        printf("B%d\n",i+1);
        scanf("%d",&B[i].size);
		B[i].flag = 0;
		B[i].rem = B[i].size;
        

    }
}

void firstfit(MemoryBlocks B[],int a,int n)
{
    for(int i=0;i<n;i++)
    {
        if(B[i].size>=a && B[i].flag==0)
        {
            B[i].flag=1;
            B[i].rem-=a;
            printf("Memory Allocated in block%d\n",i+1);
            printalloc(B,n);
            return;
        }
        else{
            printf("Cannt be alloacted\n");
        }
    }
}

void bestfit(MemoryBlocks B[],int a,int n)
{
    int min,k=-1;
    for(int i=0;i<n;i++)
    {
        if(B[i].size>=a && B[i].flag==0)
        {
            if(k==-1)
            {
                min=B[i].size;
                k=i;
            }
            else{
                if(min>B[i].size)
                {
                    min=B[i].size;
                    k=i;
                }
            }
        }
    }
    if(k==-1)
    {
        printf("Cannot allocate\n");
    }
    else{
        printf("Alloacted in B%d",k+1);
        B[k].flag=1;
        B[k].rem-=a;
        printalloc(B,n);


    }
}

void worstfit(MemoryBlocks B[],int a,int n)
{
    int l=-1,k=-1;
    for(int i=0;i<n;i++)
    {
        if(B[i].size>l && B[i].flag==0)
        {
            l=B[i].size;
            k=i;

        }
    }
    if(B[k].rem<a)
    {
        printf("Not allocated\n");
        return;

    }
    else{
        printf("Allocated in block %d",k+1);
        B[k].flag=1;
        B[k].rem-=a;
        printalloc(B,n);
    }
}

void main()
{
    int n;
    printf("Enter the max no of blocks\n");
    scanf("%d",&n);
    MemoryBlocks B[n];
    takeinput(B,n);

    int a;
    int ch;
    while(1)
    {
        printf("Enter the requesting memory size: ");
		scanf("%d",&a);
		printf("Alocation Strategies\n");
		printf("1. First Fit\n");
		printf("2. Best Fit\n");
		printf("3. Worst Fit\n");
		printf("Enter your choice : ");
		scanf("%d",&ch);

		switch(ch){
			case 1:
				firstfit(B,a,n);
				break;
			case 2: 
				bestfit(B,a,n);
				break;
			case 3: 
				worstfit(B,a,n);
				break;
			default: 
				printf("Enter valid choice!\n");
				break;
        }

    }


}