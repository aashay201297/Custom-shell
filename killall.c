#include<signal.h>
#include<stdlib.h>
#include<stdio.h>
typedef struct Node{
	pid_t pid_process;
	char pname[100];
	int num;
	struct Node *next;
}node;

extern node * head;
node * temp;
extern int counter;
//delete the whole link list
int killall()
{ 
	temp=head->next;
	while(temp)
	{   
		kill(temp->pid_process,15); // kills the process
		temp=temp -> next;
	}   
	return 1;  
}
