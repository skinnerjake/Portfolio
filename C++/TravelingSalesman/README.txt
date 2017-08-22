CS325 Spring 2017
Project 3: Traveling Salesman Problem
Due 10 June 2017

Group 3 - Members:

	Scott Cooper
	Taylor Jones
	Jake Skinner
	
Files included:

	crap.cpp (main file)
	makefile
	README.txt
	
How to use:

	'Make' the file on the command-line by typing 'make'. This should produce an executable file 'main'.
	
	On the command-line, then input './main' followed by the name of one or more text files, including the file extension '.txt'. The files should contain integer data in the following format:
	
		id1	x1	y1
		id2	x2	y2
		id3	x3	y3
		...
		
	As indicated, each line will be dedicated to a node on a coordinate plane, with its ID# and x-y coordinates included. The main file will take the inputs, parse them, then find an approximate best path for the Traveling Salesman Problem, trying to make the shortest Hamiltonian Circuit through all the nodes on the plane.
	
	The approximate path is calculated, then output to a file with the same name as the input file, followed by '.tour', containing the path distance in the first line, followed by the order of ID#'s that the path takes.
	