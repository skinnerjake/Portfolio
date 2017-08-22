// Jake Skinner
// CS344
// 8/18/17
// exectuable creates a key for use in a OTP encoding/decoding process

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// helper function to generate a random capital letter or space. returns character
char randomLetter () {
	int i = rand() % 27;
	if (i == 0)
		return ' ';
	else 
		return (char) i+64;
}

// Executable function
int main(int argc, char* argv[]) {
  // seed random
	srand(time(NULL));

	// check args
	if (argc == 1) {
		perror("Not enough arguments\n");
		exit(2);
	}
	else if (argc > 2) {
		perror("Too many arguments\n");
		exit(2);
	}
	else {
	  // initialize char array of size argv1
		int length = atoi(argv[1]);
		char key[length+1];
		memset(key, '\0', length+1);
		int i;
		// for each char in array, generate random letter or space
		for (i = 0; i < length; i++)
			key[i] = randomLetter();
		// print to stdout
		printf("%s\n", key);
	}
	return 0;
}
