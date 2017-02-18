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

//function definitions
int parseCmm(char * cmd, char ** params);
int executeCmm(char ** params,int andPresent);
int executeCD(char ** params,char * home);
void pinfo(char ** params,char *home);
char *replace_s(char *str, char *orig, char *rep);
	

int main()
{

	// char Command[1000];
	char curDir[1000];
	// char CommandStore[10007];
	char LoginUser[20];
	char * spliting;
	char com[100][100];


	int cmdCount = 0,i=0,temp=0;
	char cmd[MAX_COMMAND_LENGTH + 1],home[1000];
	char * params[MAX_NUMBER_OF_PARAMS + 1];
	getcwd(home,sizeof(home));
	while(1) 
	{
		temp=0;
		getcwd(curDir, sizeof(curDir)); //gets current working directory
		cuserid(LoginUser); //gets user id

		print(LoginUser,curDir,home); //function prints username of shell

		// Read command from stdout and exit if the command is exit
		if(fgets(cmd, sizeof(cmd), stdin) == NULL ) break;
		if(strcmp(cmd,"exit\n")==0) break;

		// remiving trailing newlines
		if(cmd[strlen(cmd)-1] == '\n') {
			cmd[strlen(cmd)-1] = '\0';
		}
	
		spliting = strtok(cmd,";"); //seperating different ; seperated commands
		
		while(spliting)
		{
			strcpy(com[temp],spliting);
			spliting = strtok(NULL,";");
			temp++;
		}
		for(i=0;i<temp;i++){
			int andPresent=parseCmm(com[i], params); // to check if the command is for background process
			
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
			
			//execute all the other commands using execvp
			else if(executeCmm(params,andPresent) == 0) break;
		}
	}

	return 0;
}

