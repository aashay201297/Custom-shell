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
node * head, * end, * lead, * follow;
extern int childStatus;
extern int counter;
extern node * head;
//function to delete background processes from link list
void delete(pid_t p_id)		
{
	if(head->next != NULL)
		follow = head->next;
	if(follow!=NULL)
	{
	if(follow->next != NULL && follow->pid_process != p_id)
	{
		lead = follow->next;

		while(lead != NULL)
		{
			if(lead->pid_process == p_id)
			{
				printf("%s [%d] %d\n", lead->pname, p_id, WEXITSTATUS(childStatus));
				follow->next = lead->next;
				free(lead);
				break;	
			}
			else
			{
				follow = lead;
				lead = follow->next;
			}
		}
		return;
	}

	else if(follow->pid_process == p_id)
	{
		printf("%s [%d] %d\n", follow->pname, p_id,WEXITSTATUS(childStatus));
		head->next = follow->next;
		free(follow);
		return;
	}
}
}
