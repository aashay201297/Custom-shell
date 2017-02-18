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



int executePWD(char ** params, char * home)
{
	char dir[1000];
	getcwd(dir,sizeof(dir));
	printf("%s\n",dir );
}
