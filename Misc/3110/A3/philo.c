#include <stdio.h>       /* Input/Output */
#include <stdlib.h>      /* General Utilities */
#include <unistd.h>      /* Symbolic Constants */
#include <sys/types.h>   /* Primitive System Data Types */
#include <sys/wait.h>    /* Wait for Process Termination */
#include <errno.h>       /* Errors */
#include <strings.h>     /* Strings */
#include <pthread.h>     /* pthreads library */

/*Could be thrown in a struct*/
pthread_mutex_t chopsticks[1000];
int meals;
int numPhilos;
int finished;
int counter;

void * Dinner (void * value)
{

	int id = *((int*)value);	
	int done = 0;
	int otherStick = 0;
	int eatingBool = 0;

	/*Makes the philospher eat for the number of meals*/	
	printf("Philospher %d is thinking...\n", id);
	while (done < meals)
	{
		counter++;
		/*Ensures that the last philosopher takes the chopstick from the first*/
		otherStick = id -1;
		if (otherStick == -1)
		{

			otherStick = numPhilos;
		
		}

		/*Prevents deadlock if there is only one philospher waiting to eat, resets all of the mutexes*/
		if ((finished  +1) == numPhilos)
		{
			for (int i = 0; i < numPhilos; i++)
			{
				
				pthread_mutex_unlock(&chopsticks[i]);
			
			}
		
		}


		/*Use trylock to test if both can be picked up*/	
		if (pthread_mutex_lock(&chopsticks[id]) == 0)
		{
			/*Boolean is to ensure that they are able to eat, and don't unlock someone else*/
			if (pthread_mutex_lock(&chopsticks[otherStick]) == 0)
			{
				printf ("Philospher %d is eating...\n", id);
				eatingBool = 1;
			}
			
		
		}		

		sleep(1);
		/*Done eating releasing mutex*/
		if (eatingBool == 1)
		{

			done++;
			pthread_mutex_unlock(&chopsticks[id]);
			pthread_mutex_unlock(&chopsticks[otherStick]);
			printf("Philospher %d is thinking...\n", id);

		}
		
		if (finished == numPhilos)
		{
			break;
		}
	}
	/*Finished checks to see if they will eat again, if they are done, then it increments. Allows me to check how many are left to eat*/
	finished++;	
	/*Ensure that they are putting down the chopsticks when they are done*/
	pthread_mutex_unlock(&chopsticks[id]);
	pthread_mutex_unlock(&chopsticks[otherStick]);
	pthread_exit(NULL);

}

int main(int argc, char * argv[])
{
	
	int idPhilo[1000];
	int check;
	
		
	pthread_t philos[1000];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	finished = 0;
	counter = 0;

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

	/*Eating*/
	for (int i = 0; i < numPhilos; i++)
	{

		pthread_join(philos[i],NULL);	

	}

	/*Free the mutex*/
	for (int i = 0; i < numPhilos; i++)
	{
		
		pthread_mutex_destroy(&chopsticks[i]);

	}

	pthread_exit(NULL);

	return 0;

}