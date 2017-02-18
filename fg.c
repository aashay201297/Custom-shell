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
extern pid_t pid;
extern node *head;
extern int counter;
extern int childStatus;
int fg(char **args)
{
	int count=0,pno,status;
	pno=atoi(args[1]); //returns int value of args[1]
	temp=head->next;
	if(pno>counter)
	{   
		printf("Invalid process number\n");
		return 0;
	}   
	while(temp)
	{
		if(temp->num == pno)
			break;
		temp=temp->next;
	}
	delete(temp->pid_process); //delete the process from link list
	waitpid(temp->pid_process,&childStatus,WCONTINUED); // resume the process in foreground
	return 0;      
}
