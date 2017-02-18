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


int executeECHO(char** params)
{
	char *cmd=params[1];
	char *pch;
	//parsing to remove tabs and inverted commas
	pch = strtok (cmd," \t\"\'");
	  while (pch != NULL)
	  {
	    printf ("%s ",pch);
	    pch = strtok (NULL," \t\"\'");
	  }
	  printf("\n");
}
