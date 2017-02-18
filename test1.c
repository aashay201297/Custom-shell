#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
typedef struct Node{
  pid_t pid;
  char pname[100];
  struct Node *next;
 }node;


int spawn_proc (int in, int out, char *com)
{
	pid_t pid;
	char *par[1000];
	// int andPresent=0; //variable to check if the process is background
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
	// printf("reasched\n");
	int save_in, save_out;
	int tempin=dup(0);
	int tempout=dup(1);
	save_in = dup(0);
	save_out = dup(1);
	int i;
	// pisd_t pid;
	int in, fd [2];
	char * split;
	char com[100][100];
	if(comd[strlen(comd)-1] == '\n') 
	{
		comd[strlen(comd)-1] = '\0';
	}
	int temp=0;
	split = strtok(comd,"|"); //seperating different ; seperated commands
	while(split)
	{
		strcpy(com[temp],split);
		split = strtok(NULL,"|");
		temp++;
	}

	/* The first process should get its input from the original file descriptor 0.  */
	in = 0;

	/* Note the loop bound, we spawn here all, but the last stage of the pipeline.  */
		char *par[1000];

	for (i = 0; i < temp-1; ++i)
	{
		if(i==0)
		{
			parseCmm(com[i],par);
			setInput(par,tempin);
		}
		pipe (fd);
		spawn_proc (in, fd [1], com[i]);
		close (fd [1]);
		in = fd [0];
	}
	// printf("com=%s\n",com[i]);
	// char * Split_temp = strtok(com[i]," "); // strtok to parse the command and storing them in params array
	// 	printf("string=\n");

	// for(int i = 0; i < 1000; i++)
	// {
	// 	par[i] = Split_temp;
	// 	// printf("%s\n",Split_temp );
	// 	Split_temp = strtok(NULL," ");
	// 	if(par[i] == NULL) break;
	// }
	//new
	parseCmm(com[i],par);
	// printf("setout\n");
	setOutput(par,tempout);
	// i=0;
	// while(par[i]!=NULL)
	// {
	// 	printf("%s ",par[i] );
	// 	i++;
	// }
	// setOutput(par,tempout);
	pid_t pid = fork(); // fork process

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
	/* Time passes, STDIN_FILENO isn't what it used to be. */
	dup2(save_in, 0);
	dup2(save_out,1);
	close(save_in);
	close(save_out);
}

