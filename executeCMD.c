#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_NUMBER_OF_PARAMS 10

void handler(int sig)
{
	pid_t pid;
	pid = wait(NULL);
	printf("Pid %d exited.\n", pid);
}

int executeCmm(char ** params,int andPresent)
{
	signal(SIGCHLD, SIG_IGN);
	pid_t pid = fork(); // fork process

	// Error
	if (pid == -1) {
		char* error = strerror(errno);
		printf("fork: %s\n", error);
		return 1;
	}

	// Child process
	else if (pid == 0) {
		// execute execvp
		execvp(params[0], params);  

		// if error occured
		char* error = strerror(errno);
		printf("shell: %s: %s\n", params[0], error);
		return 0;
	}

	// Parent process
	else {
		int childStatus;
		if(!andPresent) //if foreground process then wait for the child process to finish
		{
			signal(SIGCHLD, SIG_DFL);
			waitpid(pid, &childStatus, 0);
		}
		else  // if process is background then don't wait for the child process and print the pid when exited
			signal(SIGCHLD, handler);
		return 1;
	}
}

