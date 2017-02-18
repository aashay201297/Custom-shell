#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
typedef struct Node{
	pid_t pid_process;
	char pname[100];
	int num;

	struct Node *next;
}node;
#define MAX_COMMAND_LENGTH 100
#define MAX_NUMBER_OF_PARAMS 10
extern pid_t pid;
extern node *head;
extern int counter;

int executeCD(char ** params,char * home){
	if(params[1]){
		if(!strcmp(params[1],"~")) // if cd ~ is called
		{
			chdir(home);
		}
		else
		{
			if(chdir(params[1])<0) // if error in chdir then print error
			{
				perror("bash");
			}
		}
	}
	else // if only cd is given then change to home directory
	{
		chdir(home);

	}
	return 0;
}
