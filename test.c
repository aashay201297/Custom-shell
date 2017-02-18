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
extern node *head;
extern pid_t pid;
extern int counter;

int spawn_proc(char * com,int in, int out)
{
	char *par[1000];
	char * Split_temp = strtok(com," "); // strtok to parse the command and storing them in params array
	for(int i = 0; i < 1000; i++) {
		par[i] = Split_temp;
		Split_temp = strtok(NULL," ");
		if(par[i] == NULL) break;
	}

	if ((pid = fork ()) == 0)
	{
		if (in != 0)
		{
			dup2 (in, 0);
			close (in);
		}

		if (out != 1)
		{
			dup2 (out, 1);
			close (out);
		}

		return execvp (par[0], par);
	}

	return pid;
}
int piping(char *comd)
{
	int save_in, save_out;
	int tempin=dup(0);
	int tempout=dup(1);
	save_in = dup(0);
	save_out = dup(1);
	int i;
	int in, fd [2];
	char * split;
	char com[100][100];
	if(comd[strlen(comd)-1] == '\n') 
	{
		comd[strlen(comd)-1] = '\0';
	}
	int temp=0;
	split = strtok(comd,"|"); //split by "|"
	while(split)
	{
		strcpy(com[temp],split);
		split = strtok(NULL,"|");
		temp++;
	}

	in = 0; // initial input stream
	char *par[1000];

	for (i = 0; i < temp-1; ++i)
	{
		if(i==0) // because input redirection can only be before the first pipe
		{
			parseCmm(com[i],par);
			setInput(par,tempin);
		}
		pipe (fd); 
		spawn_proc(com[i],in, fd [1]);
		close (fd [1]);
		in = fd [0]; // input for next piped command setting
	}
	// last piped command has to be executed differently
	parseCmm(com[i],par); // because the output redirection can only be in the last piped command
	setOutput(par,tempout);
	pid = fork(); // fork process



	// Error
	if (pid == -1) {
		char* error = strerror(errno);
		printf("fork: %s\n", error);
		dup2(save_in, 0);
		dup2(save_out,1);
		close(save_in);
		close(save_out);
		return 1;
	}

	// Child process
	else if (pid == 0) {
		// execute execvp
		if (in != 0)
			dup2 (in, 0);
		execvp(par[0], par);
		dup2(save_in, 0);
		dup2(save_out,1);
		close(save_in);
		close(save_out);

		// if error occured
		char* error = strerror(errno);
		printf("shell: %s: %s\n", par[0], error);
		return 0;
	}

	// Parent process
	else {
		int childStatus;
		waitpid(pid, &childStatus, 0);
		dup2(save_in, 0);
		dup2(save_out,1);
		close(save_in);
		close(save_out);
		return 1;
	}
}

