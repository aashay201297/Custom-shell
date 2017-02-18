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
pid_t pid;
extern node *head;
extern int counter;
int childStatus;
// char ** params;


void handler1(int sig)
{
	pid_t pid_h;
	pid_h = wait(NULL);
	printf("Pid %d exited.\n", pid_h);
}

int executeCmm(char ** params,int andPresent)
{
	signal(SIGCHLD, SIG_IGN);
	pid = fork(); // fork process
	if(andPresent)
	{
		insert(pid,params[0]);
	}
	// Error
	if (pid == -1) {
		char* error = strerror(errno);
		printf("fork: %s\n", error);
		return 1;
	}

	// Child process
	else if (pid == 0) {
		// execute execvp
		int i=0;
		while(params[i]!=NULL)
		{
			i++;
		}
		execvp(params[0], params);  
		printf("dion\n");
		// if error occured
		char* error = strerror(errno);
		printf("shell: %s: %s\n", params[0], error);
		return 0;
	}

	// Parent process
	else {
		if(!andPresent) //if foreground process then wait for the child process to finish
		{
			signal(SIGCHLD, SIG_DFL);
			waitpid(pid, &childStatus, WCONTINUED);
		}
		else  // if process is background then don't wait for the child process and print the pid when exited
		{
			signal(SIGCHLD, handler1);
		}
		return 1;
	}

}

