#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <error.h>
#include <errno.h>

#define RED "\e[0;31m"
#define BLACK "\e[0;30m"
#define DOLLAR "+$"
#define MAXARG 10
#define ARGSIZE 10

void PS1()
{
	fprintf(stderr, RED DOLLAR BLACK ""); 
}

char **command_input()
{
	
	char *buffer;
	char **arg = (char**)malloc(MAXARG*ARGSIZE*sizeof(char));
	ssize_t n=0;
	PS1();
	ssize_t ret = getline(&buffer, &n, stdin);
	buffer[ret-1]='\0';
	int in_place = 0;
	char * token = strtok(buffer, " ");
	while( token != NULL ) {
		arg[in_place] = token;
		in_place++;
		token = strtok(NULL, " ");
	 
	}
	arg[in_place] = NULL;
	return arg;
}

void execute()
{
	char *arge;
	char **arg =  command_input();
	execvp(arg[0] ,arg);
	error(1, errno, "error executing %s", arge);
}

void main(int argc, char **argv)
{
	system("clear");
	while(1){
	pid_t pid = fork();
	int stat = 0;

	switch(pid)
	{
	case 0:
		while (1) {
			execute();
		}
		break;
	case -1:
	        printf("Child process error, errno = %d\n",errno);
		break;
	default:
		wait(&stat);
		if (WEXITSTATUS(stat) != 0) {
			printf("Child process error, errno = %d\n",WEXITSTATUS(stat));
		}
		break;
		
	}
    }
}
