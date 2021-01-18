#include <stdio.h>       /* Input/Output */
#include <stdlib.h>      /* General Utilities */
#include <unistd.h>      /* Symbolic Constants */
#include <sys/types.h>   /* Primitive System Data Types */
#include <sys/wait.h>    /* Wait for Process Termination */
#include <errno.h>       /* Errors */
#include <strings.h>     /* Strings */
#include <pthread.h>     /* pthreads library */

pthread_mutex_t chopsticks[1000];
int finished;
int meals;
int numPhilos;
void * Dinner (void * value)
{

	int id = *((int*)value);	
	int done = 0;
	/*Makes the philospher eat for the number of meals*/
	printf("Philospher %d is thinking...\n", id);
	while(done < meals)
	{
		/*Use Mutex to stop philosphers eating*/
		
		if ( pthread_mutex_trylock(&chopsticks[id]) == 0)
		{
			if ( id !=1)
			{
					
				if ( pthread_mutex_trylock(&chopsticks[id-1]) != 0)
				{
						
					pthread_mutex_unlock(&chopsticks[id-1]);

				}

			}
			else
			{

				if ( pthread_mutex_trylock(&chopsticks[numPhilos]) != 0 )
				{
					
					pthread_mutex_unlock(&chopsticks[numPhilos]);					
										
				}

			}	
			
		}
		done++;
		sleep(1);
		printf("Philospher %d is eating...\n", id);
		if (pthread_mutex_unlock(&chopsticks[id]) == 0)
		{

			if ( id !=1)
			{
					
				if ( pthread_mutex_unlock(&chopsticks[id-1]) == 0)
				{
					
					
				}
				else
				{

					printf("Can't unlock %d\n",id );

				}

			}
			else
			{

				if ( pthread_mutex_unlock(&chopsticks[numPhilos]) == 0 )
				{

					printf("Philospher %d is eating...\n", id);

				}
				else
				{

					printf("Can't unlock %d\n",id );

				}


			}

		}

		printf("Philospher %d is thinking...\n", id);

	}

	pthread_exit(NULL);

}

int main(int argc, char * argv[])
{

	int check;

	int idPhilo[1000];	
	//int current;
	pthread_t philos[1000];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	
	if (argc <2)
	{
		printf("Invalid Arguments\n");
		exit(0);
	}

	numPhilos = atoi(argv[1]);
	meals = atoi(argv[2]);

	/*initialize thread*/
	for (int i = 0; i < numPhilos; i++)
	{
		idPhilo[i] = i+1;
		check = pthread_create(&philos[i], &attr, Dinner, &idPhilo[i]);
		pthread_mutex_init(&chopsticks[i],NULL);
		if (check)
		 {

		 	printf("Error creating thread %d \n",i);

		 } 

	}

	finished = 0;
	/*Eating*/
	for (int i = 0; i < numPhilos; i++)
	{

		pthread_join(philos[i],NULL);	

	}

	for (int i = 0; i < numPhilos; i++)
	{
		
		pthread_mutex_destroy(&chopsticks[i]);

	}


	pthread_exit(NULL);

	return 0;

}