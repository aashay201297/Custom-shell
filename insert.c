#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
typedef struct Node{
	pid_t pid_process;
	char pname[100];
	int num;
	struct Node *next;
}node;

extern node * head;
extern pid_t pid;
extern node *head;
extern int counter;

//insert background processes in the link list
void insert(pid_t proc_id, char name[])
{
	node * n = (node *)malloc(sizeof(node));
	n->pid_process = proc_id;
	n->next = NULL;
	n->num=counter;
	counter++;
	node *temp= head;
	while(temp->next)
	{
		temp=temp->next;
	}
	temp->next=n;
	return;
}
