#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct 
{

	int cpuTime;
	int ioTime;
    int number;

} burst;

typedef struct 
{

	int arrive;
	int number;
	int counter;
	int totalBurst;
	int burstCount;
	burst ** burstArray;

} thread;

typedef struct process {

    int number;
    int threadCount;
    thread ** threadArray;

} process;


int main (int argc, char *argv[])
{

	int detailFlag = 0;
//	int verboseFlag = 0;
//	int quantum = 0;

	int totalTime = 0; 
	int averageTurnAround = 0;
	int cpuUse = 0;
	int numProcess=0;
	int temp = 0;  

 	int threadSwitch=0;
  	int processSwitch=0;
  	int processNum=0;
  	int numthread=0;

  	int threadNum=0;
  	int arriveTime=0;
  	int numCPU=0;

  	int cpuTime=0;
  	int ioTime=0;
  	//int head = 0;
  	int tail = 0;
  	int j = 0;

	process ** processArray;
	thread ** queue = malloc(sizeof(burst*)*20);
	
	/*Checks for flags*/
	printf ("Opening file->->->\n");
		
	for (int i = 0; i < argc; i++)
	{
			
			
		if (strcmp ("-d",argv[i]) == 0)
		{
			printf ("Detailed print out\n");
			detailFlag = 1;

		}
		else if (strcmp ("-v",argv[i]) == 0)
		{

			printf ("Verbose mode set\n");
			//verboseFlag = 1;
				
		}
		else if (strcmp ("-r",argv[i]) == 0)
		{
	
			printf ("%s\n",argv[i+1] );
			//quantum = atoi(argv[i+1]);
	
		}
	}
	/* Gets the number of processes, switch time between threads and proccess switch time*/
    fscanf (stdin, "%d %d %d", &numProcess, &threadSwitch, &processSwitch);
    processArray = malloc (sizeof(process)*numProcess);
	/*Loops through and adds them to processArray*/
	for (int i=0; i<numProcess;i++)
	{


    	processArray[i] = malloc (sizeof(process)*1);
    	fscanf (stdin, "%d %d", &processNum, &numthread);
    	processArray[i]->threadArray = malloc (sizeof(thread)*numthread);
    	processArray[i]->number = processNum;
    	processArray[i]->threadCount = numthread;
    	/*printf ("%d %d\n", processNum, numthread);
*/
    	/*Loops through the threads*/
    	for (int q=0; q<numthread;q++)
    	{
    		
    		processArray[i]->threadArray[q] = malloc (sizeof(thread)*1);
      		fscanf (stdin, "%d %d %d", &threadNum, &arriveTime, &numCPU);
      		processArray[i]->threadArray[q]->number = threadNum;
      		processArray[i]->threadArray[q]->arrive = arriveTime;
      		processArray[i]->threadArray[q]->burstCount = numCPU;
      		processArray[i]->threadArray[q]->counter = 0;
      		processArray[i]->threadArray[q]->burstArray = malloc (sizeof(burst)*numCPU);
      	/*	printf ("%d %d %d\n", threadNum, arriveTime, numCPU);
      	*/
      		/*Adds the individual bursts*/
	    	for (j=0; j<numCPU-1;j++)
    		{
      			

      			processArray[i]->threadArray[q]->burstArray[j] = malloc (sizeof(burst)*1);
       			fscanf (stdin, "%d %d %d",&temp, &cpuTime,&ioTime);
       			processArray[i]->threadArray[q]->burstArray[j]->number = temp;
      			processArray[i]->threadArray[q]->burstArray[j]->cpuTime = ioTime;
      			processArray[i]->threadArray[q]->burstArray[j]->cpuTime= cpuTime;
       			/*printf ("%d %d %d \n", temp, cpuTime, ioTime);
    	*/
    		}	

    		processArray[i]->threadArray[q]->burstArray[j] = malloc (sizeof(burst)*1);
     		fscanf (stdin, "%d %d",&temp, &cpuTime);
    	 	processArray[i]->threadArray[q]->burstArray[j]->number = temp;
	      	processArray[i]->threadArray[q]->burstArray[j]->ioTime = 0;
      		processArray[i]->threadArray[q]->burstArray[j]->cpuTime = cpuTime;
     	/*	printf ("%d %d\n", temp, cpuTime);
  		*/
  		}

    }



    for (int i=0; i<numProcess;i++)
    {
    
        printf ("Process Number: %d has %d threads.\n", processArray[i]->number, processArray[i]->threadCount);
    	
    	for (int q=0; q<processArray[i]->threadCount;q++)
    	{

      		printf ("Thread %d:\n", processArray[i]->threadArray[q]->number);
      		printf ("*Arrive time of %d with %d bursts\n", processArray[i]->threadArray[q]->arrive, processArray[i]->threadArray[q]->burstCount);
      		
      		for (j=0; j<processArray[i]->threadArray[q]->burstCount;j++)
      		{
       		
       			printf ("~~Burst Number %d has a CPU Time of %d and IO time of %d\n",processArray[i]->threadArray[q]->burstArray[j]->number, processArray[i]->threadArray[q]->burstArray[j]->cpuTime,processArray[i]->threadArray[q]->burstArray[j]->cpuTime);
     		
     		}

  		}
  		
    }  


    for (int i = 0; i < numProcess ; i++)
    {
    	for (int j = 0; j < processArray[i]->threadCount; j++)
    	{
    		
    		if (cpuTime >= processArray[i]->threadArray[j]->arrive)
    		{
    			
    			queue[tail] =  processArray[i]->threadArray[j];
    			queue[tail] =  processArray[i]->threadArray[j];
    			tail++;

    		}

    	}
    }

    for (int i = 0; i < tail; i++)
    {
    	
    	totalTime += queue[tail]->burstArray[queue[tail]->counter]->cpuTime;
    	queue[tail]->counter++;
    
    }

    if (detailFlag == 1)
    {
    	
    	printf ("Total Time required is %d \n",totalTime);
    	printf ("Average Turnaround Time is %d time units \n",averageTurnAround);
    	printf ("CPU Utilization is %d\n",cpuUse);

    }

    for (int i = 0; i < 20; ++i)
    {
    	
    	free(queue[i]);

    }
    free(queue);

    for (int i = 0; i < numProcess; i++)
    {
    	for (int q = 0; q < numthread; q++)
    	{
    		for (int i = 0; j < numCPU; j++)
    		{
    			free(processArray[i]->threadArray[q]->burstArray[j]);
    		}

    		free(processArray[i]->threadArray[q]);
    	}
    	free(processArray[i]->threadArray);
    	free(processArray[i]);
    }

    free(processArray);
    

    return (0);
}


