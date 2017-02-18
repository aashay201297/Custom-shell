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

int parseCmm(char* cmd, char** params)
{
	int andPresent=0; //variable to check if the process is background
	char * Split_temp = strtok(cmd," "); // strtok to parse the command and storing them in params array
	for(int i = 0; i < MAX_NUMBER_OF_PARAMS; i++) {
		params[i] = Split_temp;
		if(Split_temp!='\0')
		{
			if(strcmp(Split_temp,"&")==0 )
			{
				andPresent=1;
				params[i]=NULL;
			}

		}
		Split_temp = strtok(NULL," ");
		if(params[i] == NULL) return andPresent;
	}
}

int parsePipe(char* com)
{
	int pipePresent=0; 
	int l=strlen(com);
	int i;
	for(i=0;i<l;i++)
	{
		if(com[i]=='|')
		{
			pipePresent=1;
		}
	}	
	return pipePresent;	
}
