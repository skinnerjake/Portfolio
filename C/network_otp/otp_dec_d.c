/*
Jake Skinner
8/13/17
CS344 - Project 4
Description:
Executable creates a server that will connect with up to 5 concurrent clients and
	1. handshake with client
	2. recieve cyphertext and key
	3. decode plaintext using key and return to client

Source code from Benjamin Brewster and gnu.org
*/

// library headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

// function prototypes
void error(const char*);
void closeFDs(int[], pid_t[]);
int countFDs(int[]);
void encrypt(int);


//
void encrypt(int socket) {
	char key[100000]; 
	char text[100000];
	char buffer[1024];
	char* pos;
	int bufferCount, charsWritten, charsRead, keyCount, end = 0, i, inc;
	memset(buffer, '\0', 1024);
	
	// handshake
	charsRead = recv(socket, buffer, 1023, 0);
	if (charsRead < 0) error("SERVER: recv");
	charsRead = send(socket, "D", 2, 0);
	if (charsRead < 0) error("SERVER: send");
	if (strcmp(buffer, "D") != 0) error ("SERVER: handshake");
	
	
	// receive text
	memset(buffer, '\0', sizeof(buffer));
	memset(text, '\0', sizeof(text));
	while (!strstr(buffer, "@")) {
		memset(buffer, '\0', sizeof(buffer));
		charsRead = recv(socket, buffer, sizeof(buffer) - 1, 0);
		if (charsRead < 0) error("CLIENT: recv");
		strcat(text, buffer);
	}
	
	// receive key
	memset(buffer, '\0', sizeof(buffer));
	memset(key, '\0', sizeof(key));
	while (!strstr(buffer, "@")) {
		memset(buffer, '\0', sizeof(buffer));
		charsRead = recv(socket, buffer, sizeof(buffer) - 1, 0);
		if (charsRead < 0) error("CLIENT: recv");
		strcat(key, buffer);
	}
	
	
	// encode the buffer
	for (i = 0; i < strlen(text)-1; i++) {
		/*
		text[i] += (key[i] - 64);
		if (text[i] == 91) text[i] = 0;
		if (text[i] > 91) text[i] -= 27;
		if (text[i] < 65) text[i] += 32;
		*/
		
		if (text[i] == ' ')
			text[i] = 0;
		else 
			text[i] -= 64;
		if (key[i] == ' ')
			key[i] = 0;
		else
			key[i] -= 64;
		text[i] -= key[i];
		if (text[i] < 0)
			text[i] += 27;
		if (text[i] == 0)
			text[i] += 32;
		else
			text[i] += 64;
	} 
	
	// return encoded buffer to client
	char* t = text;
	memset(buffer, '\0', sizeof(buffer));
	while (!strstr(buffer, "@")) {
		memset(buffer, '\0', sizeof(buffer));
		strncpy(buffer, t, sizeof(buffer)-1);
		t += strlen(buffer);
		charsWritten = send(socket, buffer, sizeof(buffer) - 1, 0);
		if (charsWritten < 0) error("CLIENT: send");
	}

	// exit process
	exit(0);
}


// helper function to count number of used file discriptors, not to exceed 5
int countFDs(int FD[]) {
	int i, count = 0;
	for (i = 0; i < 5; i++)
		if (FD[i] != -1)
			count++;
	return count;
}


// helper function to close file descriptors used in processes that have closed
void closeFDs(int FD[], pid_t PID[]) {
	int i, exitMethod;
	for (i = 0; i < 5; i++)
		if (waitpid(PID[i], &exitMethod, WNOHANG) > 0) {
			close(FD[i]);
			FD[i] = -1;
			PID[i] = 0;
		}
}


// helper function for reporting errors
void error(const char* msg) {
	perror(msg);
	exit(1);
}


// main executable function
int main(int argc, char* argv[]) {
	
	// intialize values
	int listenFD,
		port,
		FDcount,
		i;
	
	pid_t forkPID;
		
	pid_t childPID[5];
	int clientSocket[5];
	
	for (i = 0; i < 5; i++) {
		childPID[i] = 0;
		clientSocket[i] = -1;
	}
	
	struct sockaddr_in serverAddress, clientAddress;
	
	socklen_t clientSize;
	
	// usage (needs at least 2 args)
	if (argc < 2) { fprintf(stderr, "Usage: %s port\n", argv[0]); exit(1); }
	
	// set up server address
	memset( (char*)&serverAddress, '\0', sizeof(serverAddress) );
	port = atoi (argv[1]);
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	
	// set up listening socket
	listenFD = socket(AF_INET, SOCK_STREAM, 0);
	if (listenFD < 0) error("socket");
	
	// connect listening socket to port
	if (bind(listenFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) error("bind");
	
	
	// Flip listening socket on for up to 5 connections
	if (listen(listenFD, 5) < 0) error("listen");
	
	// continuous loop
	while (1) {
		
		
		// close file descriptors associated with closed processes
		FDcount = countFDs(clientSocket);
		
		if (FDcount == 5)
			closeFDs(clientSocket, childPID);
		
		// if less than 5 file descriptors are being used
		else {
			
			// accept new socket
			clientSize = sizeof(clientAddress);
			int newFD = accept(listenFD, (struct sockaddr*)&clientAddress, &clientSize);
			if (newFD < 0) error("accept");
			
			// if no error accepting new socket
			else {
				i = 0;
				while (clientSocket[i] != -1)
					i++;
						
				// save socket file descriptor
				clientSocket[i] = newFD;
				
				// fork new process
				forkPID = fork();
				switch (forkPID) {
					// error
					case -1: error("fork"); break;
					// child process - encrypt on open socket
					case 0: encrypt(clientSocket[i]); break;
					// parent process - save forkPID
					default: childPID[i] = forkPID;
				}
			}
		}
	}
	
	return 0;
}