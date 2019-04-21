#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

pthread_mutex_t lockResources;
pthread_cond_t condition;

int main()
{

int d=0,t=0,j,rn,i,pr,count=0;
bool safe = false;
int ins[5],avail[5],allocated[10][5],need[10][5],MAX[10][5],P[10];
system("color F0"); 
printf("\nEnter Number Of Processes : = : ");
scanf("%d", &pr);

int f[pr];
for (i = 0; i < pr; i++) 
{
    f[i] = 0;
}

printf("\nEnter Number Of Resources : = : ");
scanf("%d", &rn);

sleep(1);
printf("\nEnter MAX Availabel Resources  : = : \n");
for(i=0;i<rn;i++)
{  
avail[i]=0;
printf("\n");
printf("%c :=: ",(i+65));
scanf("%d",&ins[i]);

}

printf("\nEnter the Each Instance Of Resources Allocation  : = : \n ");

for(i=0;i<rn;i++)
printf("    %c",(i+65));
printf("\n");
for(i=0;i<pr;i++)
{
P[i]=i;
printf("P[%d] ",P[i]);
for(j=0;j<rn;j++)
{
scanf("    %d",&allocated[i][j]);
avail[j]+=allocated[i][j];
}
}

printf("\nEnter the MAX Need Of Each  Resources : = : \n ");
for(i=0;i<rn;i++)
{
printf("    %c",(i+65));
avail[i]=ins[i]-avail[i];
}
printf("\n");
for(i=0;i <pr;i++)
{
printf("P[%d]  ",i);
 for(j=0;j<rn;j++)
  scanf("%d", &MAX[i][j]);
}

//need of every process 
for(i=0;i<pr;i++)
{ 
for(j=0;j<rn;j++)
{
 need[i][j] = MAX[i][j]-allocated[i][j];
}
}


//printf("\n");

int y = 0,k,ans[pr],allpr = 0; 
for (k = 0; k < pr; k++) 
{ 
		for (i = 0; i < pr; i++) 
		{ 
			if (f[i] == 0) 
			{ 

				int flag = 0; 
				for (j = 0; j < rn; j++) 
				{ 
					if (need[i][j] > avail[j]) 
						flag = 1; 
					break; 
				} 

				if (flag == 0) { 
					ans[allpr++] = i; 
					for (y = 0; y < rn; y++) 
						avail[y] += allocated[i][y];; 
					f[i] = 1; 
				} 
			} 
		} 
	}
//result of all process 
system("color E0");
system("cls");	
	
printf("\n");
printf("Process | Allocation  | Max Need  | Rem. Need |\n");
printf("\n");
printf("\t  %c   %c   %c     %c   %c   %c   %c   %c   %c",(65),(66),(67),(65),(66),(67),(65),(66),(67));
printf("\n");
for(i=0;i <pr;i++)
{  
//process and allocation 
printf("\nP[%d] 	|   ",i);
//allocation
for(j=0;j<rn;j++)
{  
    printf(" %d ",allocated[i][j]);
}
for ( j = 0; j < rn; j++ )
{  
if((j+2)==(rn+1))
{
    printf(" | ");
}
}
//max need
for(j=0;j<rn;j++)
{  
    printf(" %d ",MAX[i][j]);
}
for ( j = 0; j < rn; j++ )
{  
if((j+2)==(rn+1))
{
    printf(" | ");
}
}
//need of each process 
for(j=0;j<rn;j++)
{  
    printf(" %d ",need[i][j]);
}
for ( j = 0; j < rn; j++ )
{  
if((j+2)==(rn+1))
{
    printf(" | ");
}
}
}
		
			
//here we check all process are executed or not 
printf("\n\n"); 	 
if(allpr==pr)
{
   
printf(" : = : SAFE Sequence For All Process : = :\n"); 
printf("\n");
	printf("\t <");
	for (i = 0; i < rn+1; i++) 
	{
		printf(" P%d,", ans[i]);
		sleep(1);
    }
	printf(" P%d", ans[rn+1]);
    printf(">");
}
    
else
{
    printf("Process are NOT in Safe State DeadLock Occur ");
}
	return (0);
	
	pthread_cond_broadcast(&condition);
    pthread_mutex_unlock(&lockResources);
	pthread_exit(NULL);

}

