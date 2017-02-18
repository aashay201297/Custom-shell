#include<signal.h>
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

extern node * head;
node * temp;
extern int counter;
int sendsig(char **args)
{
	int count=0,pno,pid,sig;
	pno=atoi(args[1]); // stores process number
	sig=atoi(args[2]); // stores signal number
	temp=head->next;
	if(pno>counter)
	{   
		printf("Less Processes\n");
		return 1;
	}   
	while(temp)
	{   
		if(temp->num == pno)
		{
			break;
		}
		temp=temp->next;
	}   
	kill(temp->pid_process,sig);
	return 1;  
}
