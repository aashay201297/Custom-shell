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
extern int childStatus;

extern pid_t pid;
int counter;
node * head;
int N;
#define MAX_COMMAND_LENGTH 100
#define MAX_NUMBER_OF_PARAMS 10
char * params[MAX_NUMBER_OF_PARAMS + 1];

void handler(int signum)
{
	pid_t proc_id;

	(proc_id = waitpid(-1, &childStatus, WNOHANG));

	delete(proc_id);
}
//handler for ctrl-z
void sigstop(int p)
{
	kill (pid,20); // pause the process
	insert(pid,params[0]); // push it to the link list
	kill (pid,18); 
}
// handler for ctrl-c
void sigkill(int p){
	return;
}


//function definitions
int parseCmm(char * cmd, char ** params);
int executeCmm(char ** params,int andPresent);
int executeCD(char ** params,char * home);
void pinfo(char ** params,char *home);
char *replace_s(char *str, char *orig, char *rep);


int main()
{
	N=0;
	counter=1;
	int stdin_copy = dup(0);
	int stdout_copy = dup(1);

	char curDir[1000];
	char LoginUser[20];
	char * spliting;
	char com[100][100];
	head = (node *)malloc(sizeof(node));
	head -> next = NULL;
	int cmdCount = 0,i=0,temp=0;
	char cmd[MAX_COMMAND_LENGTH + 1],home[1000];
	getcwd(home,sizeof(home));
	while(1) 
	{
		dup2(stdin_copy, 0);
		dup2(stdout_copy, 1);
		close(stdin_copy);
		close(stdout_copy);
		signal(SIGCHLD,&handler);
		signal(SIGTSTP,&sigstop);      //for Ctrl+Z
		signal(SIGINT,&sigkill);       //for Ctrl+C

		temp=0;
		getcwd(curDir, sizeof(curDir)); //gets current working directory
		cuserid(LoginUser); //gets user id

		print(LoginUser,curDir,home); //function prints username of shell

		// Read command from stdout and exit if the command is exit
		if(fgets(cmd, sizeof(cmd), stdin) == NULL ) 
		{
			break;
		}
		if(strcmp(cmd,"exit\n")==0) break;

		// removing trailing newlines
		if(cmd[strlen(cmd)-1] == '\n') {
			cmd[strlen(cmd)-1] = '\0';
		}
		int tempin=dup(0);
		int tempout=dup(1);
		spliting = strtok(cmd,";"); //seperating different ; seperated commands

		while(spliting)
		{
			strcpy(com[temp],spliting);
			spliting = strtok(NULL,";");
			temp++;
		}

		for(i=0;i<temp;i++){

			char tempo[1024];
			strcpy(tempo,com[i]); // save the ';' seperated command
			int andPresent=parseCmm(com[i], params); // to check if the command is for background process		
			int pipePresent=parsePipe(tempo); // to check if pipe is present
			if(pipePresent)
			{
				piping(tempo); // call the piping function
			}
			
			else
			{
				setInput(params,tempin); // sets the input stream if input redirection is there
				setOutput(params,tempout); // sets the output stream if output redirection is there
				int j=0;
				// sets everything to null after the rediretion sign
				while(params[j]!=NULL && strcmp(params[j],"<")!=0 && strcmp(params[j],">")!=0 && strcmp(params[j],">>")!=0)
				{
					j++;
				}
				while(params[j]!=NULL)
				{
					params[j]=NULL;
					j++;
				}
				//execute cd command
				if(strcmp(params[0],"cd") == 0){
					executeCD(params,home);
				}

				//execute pwd command
				else if(strcmp(params[0],"pwd") == 0){
					executePWD(params,home);

				}

				//execute pinfo command (bonus)
				else if(strcmp(params[0],"pinfo") == 0){
					pinfo(params,home);
				}

				//execute echo command
				else if(strcmp(params[0],"echo")==0){
					executeECHO(params);
				}
				//execute killall command
				else if(strcmp(params[0],"killall")==0)
				{
					killall();
				}
				//execute fg command
				else if(strcmp(params[0],"fg")==0)
				{
					fg(params);
				}
				//execute listjobs
				else if(strcmp(params[0],"listjobs")==0)
				{
					listjobs(params);
				}
				//execute  sendsig
				else if(strcmp(params[0],"sendsig")==0)
				{
					sendsig(params);
				}
				//execute all the other commands using execvp
				else if(executeCmm(params,andPresent) == 0) break;
			}
			// printf("yo\n");
		}
	}

	return 0;
}

