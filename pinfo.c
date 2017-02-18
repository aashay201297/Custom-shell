#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_PATHNAME_LENGTH 100
extern pid_t pid;
extern int counter;
typedef struct Node{
	pid_t pid_process;
	char pname[100];
	int num;

	struct Node *next;
}node;
extern node *head;

//function to replace home directory by ~
char *replace_s(char *str, char *orig, char *rep)
{
	static char buffer[4096];
	char *p;

	if(!(p = strstr(str, orig)))  // If orig string in str string
	{
		strcpy(buffer,str);
		return buffer;
	} 

	strncpy(buffer, str, p-str); // Copy characters from str string start to orig string
	buffer[p-str] = '\0';

	sprintf(buffer+(p-str), "%s%s", rep, p+strlen(orig));

	return buffer;
}

void pinfo(char ** params,char * home)
{
	char procPath[MAX_PATHNAME_LENGTH]; 
	strcpy(procPath, "/proc/"); //procPath = '/proc/'

	// If pid given, use that, else get info for shell process
	if(params[1]) strcat(procPath, params[1]);// procPath = '/proc/pid/'
	else strcat(procPath, "self"); //procPath = '/proc/self'

	// read process id and status
	// Create stat path string
	char statPath[MAX_PATHNAME_LENGTH];
	strcpy(statPath, procPath); strcat(statPath, "/stat"); // statPath=/proc/pid/stat/

	errno = 0;
	FILE * stat = fopen(statPath, "r"); // reading statPath to get pid, process name
	if(errno)
	{
		fprintf(stderr, "Error reading %s: %s\n", statPath, strerror(errno));
		return ;
	}
	int pid_info; char status; char name[20];
	fscanf(stat, "%d", &pid_info); fscanf(stat, "%s", name); fscanf(stat, " %c", &status);

	fprintf(stdout, "pid: %d\n", pid_info); // printing pid
	fprintf(stdout, "Process Status: %c\n", status); // printing process status
	fclose(stat);

	errno = 0;
	strcpy(statPath, procPath); strcat(statPath, "/statm"); // statPath=/proc/pid/statm
	FILE * mem = fopen(statPath, "r"); // for reading number of virtual pages
	if(errno)
	{
		fprintf(stderr, "Error reading %s: %s\n", statPath, strerror(errno));
		return ;
	}
	int memSize; fscanf(mem, "%d", &memSize);
	fprintf(stdout, "Memory: %d\n", memSize);
	fclose(mem);

	char exePath[MAX_PATHNAME_LENGTH];
	int i=99;
	while(i>=0)
	{
		exePath[i]='\0';
		i--;
	}


	strcpy(statPath, procPath); strcat(statPath, "/exe"); // statPath = /proc/pid/exe
	errno = 0;
	readlink(statPath, exePath, sizeof(exePath)); //read symbolic link of the given pid and store it in exePath
	if(errno)
	{
		fprintf(stderr, "Error reading symbolic link %s: %s\n", statPath, strerror(errno));
		return;
	}
	char c[1000]; //the string with home directory replaces by ~
	i=999;
	while(i>=0)
	{
		c[i]='\0';
		i--;
	}
	strcpy(c,replace_s(exePath,home,"~"));
	fprintf(stdout, "Executable Path: %s\n", c);

	return;
}
