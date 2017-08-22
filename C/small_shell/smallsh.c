// Jake Skinner
// 8/8/17
// CS344 - Summer '17
// Project 3 - smallsh


// libraries
#include <stdio.h> 		// printf
#include <string.h> 	// memset, strcmp, strcpy, strcat
#include <stdlib.h> 	// malloc, free, exit, pid_t
#include <unistd.h>		// chdir
#include <fcntl.h>		// oflag
#include <sys/types.h>	// file mode bits, exec(), fork()
#include <signal.h>		// sigaction, sigset_t

// prototypes
void prompt(char*[], int);
void replacePID(char*);
void run(char*[], char[]);
void printArgs(char*[]);
void clearArgs(char*[], int[]);
void changeDir(char*[]);
void redirectIO(char*[], int[]);
void removeArg(char*[], int);
void forkoff(char*[], int[], char[]);
void catchSIGINT(int);
void catchSIGTSTP(int);
void catchSIGCHILD(int);
// 
int FGMode = 0;
/*
void catchSIGCHILD(int signo) {
	int childExitStatus;
	char childName [100];
	pid_t child = NULL;
	while ((child = waitpid(-1, &childExitStatus, WNOHANG))) {
		memset(childName, '\0', 100);
		background
	}
}
*/

// signal catcher for sigint
void catchSIGINT(int signo) {
	exit(0);
}

// signal catcher for sigtstp
void catchSIGTSTP(int signo) {
	char* on = "\nEntering foreground-only mode (& is now ignored)\n";
	char* off = "\nExiting foreground-only mode\n";
	fflush(stdout);
	if (FGMode) {
		FGMode = 0;
		write(STDOUT_FILENO, off, 30);
	}
	else {
		FGMode = 1;
		write(STDOUT_FILENO, on, 50);
	}
}

// function to fork and execute commands that aren't built in.
void forkoff(char* args[], int fd[], char status[]) {

	struct sigaction SIGINT_action = {0};
	SIGINT_action.sa_handler = SIG_IGN;
	SIGINT_action.sa_flags = 0;
	sigaction(SIGINT, &SIGINT_action, NULL);

	int childExitStatus = -5;
	pid_t forkPID = -5;
	
	int bg = 0, i = 0;
	while (strcmp(args[i+1], ""))
		i++;
	
	// determine if background process
	if ((!strcmp (args[i], "&")))
		bg = 1;
	
	forkPID = fork();
	
	switch (forkPID) {
	
		// error
		case -1: perror("fork()"); exit(1); break;
		
		// child process
		case 0: {
			
			// count args
			int c = 0;
			
			while ((strcmp(args[c], "")))
				c++;
			
			
			// if foreground
			if (!bg) {
				SIGINT_action.sa_handler = catchSIGINT;
				sigaction(SIGINT, &SIGINT_action, NULL);
				c++;
				if (fd[0] != 0)
					dup2(fd[0], 0);
				if (fd[1] != 1)
					dup2(fd[1], 1);
			}
			
			// if background
			else {
				// deal with file descriptors
				if (fd[0] != 0)
					dup2(fd[0], 0);
				else {
					int handle = open("/dev/null", O_RDONLY, 0666);
					dup2(handle, 0);
				}
				if (fd[1] != 1)
					dup2(fd[1], 1);
				else {
					int handle = open("/dev/null", O_WRONLY, 0666);
					if (handle < 0)
						perror("couldn't find file");
						exit(1);
					dup2(handle, 1);
					
				// get and print process ID
				int pid = getpid();
				printf("background pid is %d\n", pid);
				}
			}
			
			//build new array ending with null
			char* newArgs[c];
			for (i = 0; i < c-1; i++)
				newArgs[i] = args[i];
			newArgs[i] = NULL;
			
			
			execvp(newArgs[0], newArgs);
			perror("command not found");
			exit(2);
			break;
		}	
		// parent process
		default: {
			
			// if not background process, wait for child
			if (FGMode || !bg) {
				memset(status, '\0', 100);
				waitpid(forkPID, &childExitStatus, 0);
				if (WIFSIGNALED(childExitStatus) != 0) {
					int termSignal = WTERMSIG(childExitStatus);
					printf(status, "terminated by signal %d\n", termSignal);
					sprintf(status, "terminated by signal %d\n", termSignal);
				}
				else {
					int exitStatus = WEXITSTATUS(childExitStatus);
					sprintf(status, "exit status %d\n", exitStatus);
				}
			}
			else
				printf("background pid is %d\n", forkPID);
			break;
		}
	}
}

// helper function to remove arguments when determining IO
void removeArg(char* args[], int loc) {
	// delete contents of argument
	memset(args[loc], '\0', 100);
	char* temp = args[loc];
	
	// move argument to end of argument list
	int i = loc;
	
	do {
		args[i] = args[i+1];
		i++;
	} while ((strcmp(args[i],"")));
	args[i] = temp;
}

// helper functino to redirect file descriptors
void redirectIO(char* args[], int fd[]) {
	int i = 0;
	int handle = 0;
	// while args exist
	while ((strcmp(args[i], ""))) {
		if ((!strcmp(args[i], "<"))) {
			// redirect next arg file descriptor as stdin
			handle = open(args[i+1], O_RDONLY, 0666);
			if (handle < 0) {
				perror("source open()"); 
				return;
			}
			else {
				fd[0] = handle;
				removeArg(args, i);
				removeArg(args, i);
			}
		}
		else if ((!strcmp(args[i], ">"))) {
			
			// redirect next arg file descriptor as stdout
			handle = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
			
			if (handle < 0) {
				perror("target open()");
				return;
			}
			else {
				fd[1] = handle;
				removeArg(args, i);
				removeArg(args, i);
			}
		}
		else
			i++;
	}
	
}

// helper function to change directory when "cd" is input
void changeDir(char* args[]) {
	
	// get current working directory
	char cwd[100];
	getcwd(cwd, sizeof (cwd));
	int result;
	
	// if no arg2 or it is '.', stay in current directory
	if (!strcmp(args[1], "") || !strcmp(args[1], "."))
		return;
	
	// if arg2 is '..', go up a directory
	else if (!strcmp(args[1], "..")) {
		char* p = &cwd[strlen(cwd)-1];
		while (*p != '/') {
			*p = '\0';
			p--;
		}
		*p = '\0';
		result = chdir(cwd);
	}
	
		
	// if arg2 is anything else, try to change directories
	else {
		strcat(cwd, "/");
		strcat(cwd, args[1]);
		result = chdir(cwd);
	}
	
	// if unsuccessful, return error
	if (result)
		perror("cd");
}

// helper function to clear arguments in between function calls
void clearArgs(char* args[], int fd[]) {

	// reset argument memory
	int i = 0;
	for (i = 0; i < 512; i++) 
		memset(args[i], '\0', 100);
	
	// reset file pointers
	close(0);
	close(1);
	dup2(fd[0], 0);
	dup2(fd[1], 1);
}

// utility function to print arguments
void printArgs(char* args[]) {
	int i = 0;
	while ((args[i] && strcmp(args[i], ""))) {
		printf("Arg #%d: %s\n", i, args[i]);
		i++;
	}
}

// helper function to replace '$$' with process ID
void replacePID(char* arg) {
	
	char temp[100];
	memset(temp, '\0', 100);
	char pid[10];
	memset(pid, '\0', 10);
	sprintf(pid, "%d", (int) getpid());
	
	char* loc = NULL;
	if ((loc = strstr(arg, "$$"))) {
		int resize = (int) (loc - arg);
		strncpy(temp, arg, resize);
		strcat(temp, pid);
		strcat(temp, loc+2);
		strcpy(arg, temp);
	}
}

// function recieves input from user and inputs arguments into an array
void prompt(char* args[], int argsSize) {
	
	int i = 0;
	
	// clear buffer and write to screen
	fflush(stdout);
	write(2, ": ", 2);
	
	// create an input array
	int max = 2048;
	char input[max];
	memset(input, '\0', max);
	
	// read arguments from stdin and fix newline
	read(0, input, max);
	
	input[strlen(input)-1] = '\0';
	
	
	char* rest = input;
	char* token = NULL;
	
	// while there is space-delineated input left
	while ((token = strtok_r(rest, " " , &rest))) {
		// copy next input and replace $$ -> processID
		strcpy(args[i], token);
		replacePID(args[i]);
		i++;
	}
}

// function that interprets user input
void run(char* args[], char status[]) {
	
	int fd[2];
	fd[0] = 0;
	fd[1] = 1;
	
	int s = -1;
	
	// if args[0] is null, a comment, or "exit", do nothing else
	if ((!strcmp(args[0], "") || !strcmp(args[0], "exit") || args[0][0] == '#'))
		return;
	
	// change directory
	else if (!strcmp(args[0], "cd"))
		changeDir(args);
	
	// status
	else if (!strcmp(args[0], "status"))
		printf("%s", status);
	
	// else, redirect input output and execute code
	else {
		
		redirectIO(args, fd);
		forkoff(args, fd, status);
	}
}

// main executable function
int main() {
	
	// signal set for catching ^Z - SIGTSTP
	struct sigaction SIGTSTP_action = {0};
	SIGTSTP_action.sa_handler = catchSIGTSTP;
	SIGTSTP_action.sa_flags = 0;
	sigaction(SIGTSTP, &SIGTSTP_action, NULL);
	
	// initialize values
	int argsSize = 512,
		i = 0, 
		fd[2];
		
	char status [100];
	memset(status, '\0', 100);
	
	// save stdio descriptors 
	fd[0] = dup(0);
	fd[1] = dup(1);
	
	// allocate memory for arguments
	char* args[512];
	for (i = 0; i < 512; i++)
		args[i] = malloc(100);
	
	do {
		clearArgs(args, fd);
		
		// parse user input from commandline
		
		prompt(args, argsSize);
		// interpret args and run commands
		run(args, status);
		
	} while (!args[0] || strcmp(args[0], "exit")); 
	// !args[0] condition prevents strcmp on NULL
	
	// free allocated memory
	for (i = 0; i < 512; i++)
		free(args[i]);
		
	return 0;
}