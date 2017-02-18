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

//function to replace home directory by ~
char *replace_str(char *str, char *orig, char *rep)
{
	static char buffer[4096];
	char *p;

	if(!(p = strstr(str, orig)))  
	{
		strcpy(buffer,str);
		return buffer;
	} 

	strncpy(buffer, str, p-str); 
	buffer[p-str] = '\0';

	sprintf(buffer+(p-str), "%s%s", rep, p+strlen(orig));

	return buffer;
}

//prints the shell initials
int print(char * LoginUser, char * curDir, char * home){
	char hostName[100];
	char c[10000];
	gethostname(hostName,sizeof(hostName));
	strcpy(c,replace_str(curDir,home,"~"));
	printf("%s@%s: %s $ ",LoginUser,hostName,c);
	return 0;
}
