#define _POSIX_SOURCE
#include <stdio.h>       
#include <stdlib.h>      
#include <unistd.h>      
#include <signal.h>
#include <sys/types.h>   
#include <sys/wait.h>    
#include <errno.h> 
#include <string.h>

int main(int argc, char **argv)
{

	/*Input strings*/
	char * input = malloc(sizeof(char)*500);
	char ** commands = malloc(sizeof(char*)*100);
	char * token;
  char directory[100];
  

  
  int backgroundNum = 0;
  int status = 0;
	int tokenCounter = -1;
  int loopBool = 0;
  int waitBool = 0;

  pid_t * childBackground = malloc(sizeof(pid_t)*100);
  pid_t childpid;
	
	/*Shell loop*/
    
    while (loopBool==0)
    {
      waitBool = 0;
      /*Get directory and print it*/
      getcwd(directory,sizeof(directory));

      printf("%s> ",directory);
      fgets(input,499,stdin);

    	/*Input from the keyboard, and tokens*/
      /*Exit isn't built in*/
		  if (strcmp("exit\n",input) == 0)
    	{
           
        printf("logout\n");
        loopBool = 1;
    	   
      }
      
      /*Gets the input string and adds null terminator and tokens it*/
      input[strlen(input)-1] = '\0';
    	token = strtok(input," ");
      tokenCounter = -1;
        	
      while (token != NULL)
      {
            
        tokenCounter++;
    		commands[tokenCounter] = malloc(sizeof(char)*strlen(token));
    		strcpy(commands[tokenCounter],token);  		
        token = strtok(NULL," ");

    	}          
      
      /* Checks for a background process*/
      if(strcmp("&",commands[tokenCounter]) == 0)
      {

        commands[tokenCounter] = '\0';
        waitBool = 1;
            
      }

      /*Removesnewline character from fgets()*/
      tokenCounter ++;
      commands[tokenCounter] = NULL;

      /* Tried using cd in execvp() but wouldn't work,
      according to http://stackoverflow.com/questions/18686114/cd-command-not-working-with-execvp
      it must be hard coded*/
      if (strcmp("cd",commands[0]) == 0)
      {
      
        chdir(commands[1]);
      
      }
      else{    
      
        childpid = fork();

        if ( childpid >= 0 ) 
        {   /* fork succeeded */
      /*
       *   Child Process
       */
         if ( childpid == 0 && loopBool != 1) 
         {  

            execvp(commands[0],commands);
            printf("Invalid input.\n");
            exit(status);
            
         } 
         else 
         {   
          
            if (waitBool != 1)
            {
              
              waitpid(childpid,&status,0);
            
            }
            else
            {

              childBackground[backgroundNum] = childpid;
              backgroundNum++;

            }


         }
      } 
      else 
      {
      
         perror("fork");
         exit(-1);
      
      }
    }

    while (tokenCounter >= 0)
    {

      free(commands[tokenCounter]);
      tokenCounter--;
  
    }
        
  }
  
free(commands);
free(input);

while(backgroundNum >-1)
{

  kill(childBackground[backgroundNum],SIGKILL);
  backgroundNum--;

}


return(0);

}
