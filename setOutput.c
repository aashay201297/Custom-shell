#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<linux/limits.h>
#include<signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<errno.h>
extern pid_t pid;
extern int counter;
typedef struct Node{
	pid_t pid_process;
	char pname[100];
	int num;

	struct Node *next;
}node;
extern node *head;



void setOutput(char **args, int tempout)
{
	int i=0;
	while(args[i]!=NULL)
	{
		if(strcmp(args[i],">")==0)
		{
			int fdout = open(args[i+1],O_RDWR|O_CREAT|O_TRUNC, 0777);
			dup2(fdout,1); //set output to fdout
			close(fdout);
			int j=i;
			while(args[j]!=NULL) // remove everything after ">"
			{
				args[j]=NULL;
				j++;
			}
			return 0;
		}
		if(strcmp(args[i],">>")==0)
		{
			int fdout = open(args[i+1],O_RDWR|O_APPEND|O_CREAT, 0777);
			dup2(fdout,1);
			close(fdout);
			int j=i;
			while(args[j]!=NULL) // remove everything after ">>"
			{
				args[j]=NULL;
				j++;
			}
			return 0;
		}
		i++;
	}
}
