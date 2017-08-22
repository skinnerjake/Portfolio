/*
Jake Skinner
8/13/17
CS344 - Project 4
Description:
Executable creates a client that will connect a server and
	1. handshake with server
	2. send plaintext and key
	3. recieve encoded cyphertext from server and print to stdout

Source code from Benjamin Brewster and gnu.org
*/

// library headers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>

// helper function for dealing with errors
void error(const char *msg) { perror(msg); exit(1); } 


// main executable function
int main(int argc, char* argv[]) {
	
	// initialize values
	int socketFD, 
		port, 
		charsWritten,
		charsRead,
		bufferRead,
		textRead,
		keyRead,
		bufferFD,
		textFD,
		keyFD;
	
	struct sockaddr_in serverAddress;
	
	struct hostent* serverHostInfo;
	
	char buffer[1024];
	char key[100000];
	char text[100000];
	char output[100000];
	char* k = key;
	char* t = text;
	
	// usage and args
	if (argc < 4) { fprintf(stderr, "Usage: %s hostname port\n", argv[0]); exit(1); }
	
	// set up serverAddress
	memset( (char*)&serverAddress, '\0', sizeof(serverAddress) );
	port = atoi(argv[3]);
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverHostInfo = gethostbyname("localhost");
	if (serverHostInfo == NULL) { fprintf(stderr, "CLIENT: ERROR, no such host\n"); exit(1); }
	
	// copy address
	memcpy( (char*)&serverAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length ); 
	
	// creat socket FD
	socketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (socketFD < 0) error("CLIENT: socket");
	
	// connect socket to server
	if (connect( socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress) ) < 0) error("CLIENT: connect");
	
	// handshake with server
	memset(buffer, '\0', sizeof(buffer));
	strcpy(buffer, "E");
	charsWritten = send(socketFD, buffer, strlen(buffer), 0);
	if (charsWritten < 0) error ("CLIENT: send");
	memset(buffer, '\0', sizeof(buffer));
	charsRead = recv(socketFD, buffer, sizeof(buffer) - 1, 0);
	if (charsRead < 0) error ("CLIENT: recv");
	if (strcmp(buffer, "E") != 0) error("CLIENT: handshake");
	
	// open text and key as read only
	textFD = open(argv[1], O_RDONLY);
	if (textFD < 0) error ("CLIENT: open textFD");
	keyFD = open(argv[2], O_RDONLY);
	if (keyFD < 0) error("CLIENT: open keyFD");
	
	// get text and append '@'
	memset(text, '\0', sizeof(text));
	textRead = read(textFD, text, sizeof(text)-1);
	if (textRead < 0) error ("CLIENT: read text");
	text[strlen(text)-1] = '@';
	
	int i;
	for (i = 0; i < strlen(text) - 1; i++) {
		if ((text[1] < 'A' && text[i] != ' ') || (text[i] > 'Z'))
			error("Bad file!");
	}
	
	// get key and append '@'
	memset(key, '\0', sizeof(key));
	read(keyFD, key, sizeof(key)-1);
	key[strlen(text)] = '\0';
	key[strlen(key)-1] = '@';
	
	if (strlen(key) < strlen(text)) error("Key too short");
	
	// send text
	memset(buffer, '\0', sizeof(buffer));
	while (!strstr(buffer, "@")) {
		memset(buffer, '\0', sizeof(buffer));
		strncpy(buffer, t, sizeof(buffer)-1);
		t += strlen(buffer);
		charsWritten = send(socketFD, buffer, sizeof(buffer) - 1, 0);
		if (charsWritten < 0) error("CLIENT: send");
	}

	
	// send key
	memset(buffer, '\0', sizeof(buffer));
	while (!strstr(buffer, "@")) {
		memset(buffer, '\0', sizeof(buffer));
		strncpy(buffer, k, sizeof(buffer)-1);
		k += strlen(buffer);
		charsWritten = send(socketFD, buffer, sizeof(buffer) - 1, 0);
		if (charsWritten < 0) error("CLIENT: send");
	}
	
	memset(buffer, '\0', sizeof(buffer));
	memset(output, '\0', sizeof(output));
	// receive encrypted text
	while (!strstr(buffer, "@")) {
		memset(buffer, '\0', sizeof(buffer));
		charsRead = recv(socketFD, buffer, sizeof(buffer) - 1, 0);
		if (charsRead < 0) error("CLIENT: recv");
		strcat(output, buffer);
	}
	
	output[strlen(output)-1] = '\0';
	printf("%s\n", output);
	close(bufferFD);
	close(keyFD);
	close(socketFD);
	return 0;
}