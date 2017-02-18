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
// traverse the link list and print every process in the link list
int listjobs(char **args)
{
	temp=head->next;
	while(temp)
	{   
		printf("[%d] %s [%d]\n",temp->num,temp->pname,temp->pid_process);
		temp=temp -> next;
	}   
	return 1;
}
