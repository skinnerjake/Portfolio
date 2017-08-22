/*

Christofides Algorithm:

    Create a minimum spanning tree T of G.
    Let O be the set of vertices with odd degree in T. By the handshaking lemma, O has an even number of vertices.
    Find a minimum-weight perfect matching M in the induced subgraph given by the vertices from O.
    Combine the edges of M and T to form a connected multigraph H in which each vertex has even degree.
    Form an Eulerian circuit in H.
    Make the circuit found in previous step into a Hamiltonian circuit by skipping repeated vertices (shortcutting).

	
MST(G)
	1) Create a set mstSet that keeps track of vertices already included in MST.
	2) Assign a key value to all vertices in the input graph. Initialize all key values as INFINITE. Assign key value as 0 for the first vertex so that it is picked first.
	3) While mstSet doesn’t include all vertices
	….a) Pick a vertex u which is not there in mstSet and has minimum key value.
	….b) Include u to mstSet.
	….c) Update key value of all adjacent vertices of u. To update the key values, iterate through all adjacent vertices. For every adjacent vertex v, if weight of edge u-v is less than the previous key value of v, update the key value as weight of u-v
	
*/

#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <stack>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;


int** input(string fileName, int& lineCount) {
    
	// Variables
	int** table;
	int i = 0;
    string line;
	cout << fileName << endl;
    //open file
    fstream fp;
	fp.open(fileName);
	
	// Make sure file was successfuly opened
    if(!fp.is_open())
    {
        cout << "File not found, Please try again." << endl;
		return NULL;
	} else {
        cout << "File found, extracting data from file..." << endl;
    
		// Get the number of inputs
		while( getline(fp, line))
			lineCount++;
		
		// Initialize first array of table to size lineCount
		table = new int*[lineCount];
		
		// Reset the file stream to the beginning of file
		fp.clear();
		fp.seekg(0, ios::beg);
		
		// Get input
		do {table[i] = new int[3];
			fp >> table[i][0] >> table[i][1] >> table[i][2];
			i++;
		} while (!fp.eof());
		
		// Close filestream and return table
		fp.close();
		return table;
	}
}

int distance (int* coord1, int* coord2) {
	double x = coord1[1] - coord2[1],
		y = coord1[2] - coord2[2];
	int value = sqrt(x * x + y * y) + 0.5;
	return value;
};

// prints 2D Array
void print2dArray(int** array, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
			cout << array[i][j] << " ";
		cout << endl;
	}
};


int** getEdgeArray (int** coordinates, int size) {
	
	// Initilize 2D array
	int** edges = new int*[size];
	for (int i = 0; i < size; i++)
		edges[i] = new int[size];
	
	// Calculate half the edges
	for (int i = 0; i < size; i++)
		for (int j = i; j < size; j++)
			edges[i][j] = distance(coordinates[i], coordinates[j]);
		
	// Transpose values
	for (int i = 0; i < size; i++)
		for (int j = 0; j < i; j++)
			edges[i][j] = edges[j][i];

	// Return array
	return edges;
};

int* MST (int** edges, int size) {
	
	// Create contatiners for parent nodes and visited
	int* tree = new int[size];
	int closest[size];
	bool visited[size];
	
	// Initialize values
	for (int i = 0; i < size; i++) {
		tree[i] = -1;
		visited[i] = false;
		closest[i] = 0;
	}
	
	// starting node = 0
	visited[0] = true;
	int recent = 0; // last vertex visited
	
	for (int count = 0; count < size-1; count++) {
		
		int min = INT_MAX;
		int start = -1;
		int end = -1;
		// update closest vertices  array
		for (int v2 = 0; v2 < size; v2++)
			if (edges[recent][v2] < edges[closest[v2]][v2] && recent != v2)
				closest[v2] = recent;
			
		// find closest verex that hasn't already been visited
		for (int v2 = 0; v2 < size; v2++)
			if (!visited[v2] && edges[closest[v2]][v2] < min){
				min = edges[closest[v2]][v2];
				start = closest[v2];
				end = v2;
			}
		// update tree
		tree[end] = start;
		// update visited
		visited[end] = true;
		// update v1
		recent = end;
	}

	return tree;
};


int* vectorDegree(int* MST, int size) {
	// container that holds the degree of each vector
	int* degree = new int[size];
	
	// for each node
	for (int i = 0; i < size; i++) {
		
		// Each node is connected to something else in the tree
		degree[i] = 1;
		
		// unless it is the first vertex
		if (MST[i] == -1) degree[i] -= 1;
		
		// for each other node that could connect to it
		for (int j = 0; j < size; j++)
			// if the other node connects
			if (i != j && MST[j] == i)
				// increase the degree
				degree[i]++;
	}
	return degree;
}

int* minimumPairs(int* degree, int** edges, int* MST, int &eulerStart, int size) {
	
	// Initilize pair container
	int* pairs = new int[size];
	for (int i = 0; i < size; i++)
		pairs[i] = -1;
	
	// pair as many other vertices as you can; should only be 2 odd degree vertices left at most
	for (int v1 = 0; v1 < size-1; v1++) {
		if (degree[v1] % 2 != 0) {
			int minEdge = INT_MAX;
			int bestVertex = -1;
			for (int v2 = v1 + 1; v2 < size; v2++) {
				// if the second vertex is odd degree and neither vertex is already in MST
				if (degree[v2] % 2 != 0 && MST[v1] != v2 && MST[v2] != v1) {
					// Set minEdge and bestVertex if it is the smallest pair so far
					if (edges[v1][v2] < minEdge){
						bestVertex = v2;
						minEdge = edges[v1][v2];
					}
				}
			}
			
			// if an optimal pair was found
			if (bestVertex != -1) {
				pairs[v1] = bestVertex;
				degree[v1]++;
				degree[bestVertex]++;
			}
			
			// Euler circuit can be formed in a graph with two odd degree nodes
			// only if the circuit starts at an one of the odd degree nodes
			else
				eulerStart = v1;
		}
	}
	return pairs;
};

// create 2d multigraph of MST and minimum pairing
vector<vector<int> > multigraph (int* set1, int* set2, int size) {

	vector<vector<int> > H (size, vector<int> (0));
	
	for (int i = 0; i < size; i++) {
		if (set1[i] != -1) {
			H[i].push_back(set1[i]);
			H[set1[i]].push_back(i);
		}
		if (set2[i] != -1) {
			H[i].push_back(set2[i]);
			H[set2[i]].push_back(i);
		}
	}
	
	return H;
};

// Helper function for deleting edges from the Multigraph\
// Deletes the 
void deleteEdge (vector<vector<int> > &G, int v1, int v2) {
	int loc = 0;
	while (G[v1][loc] != v2)
		loc++;
	G[v1].erase(G[v1].begin()+loc);
	
	loc = 0; 
	while (G[v2][loc] != v1)
		loc++;
	G[v2].erase(G[v2].begin()+loc);
};

// algorithm from http://www.graph-magics.com/articles/euler.php
int* EulerCircuit (vector<vector<int> > H, int const &start, int size) {
	
	// The Euler circuit has variable length, but it can't be longer than 2V
	int* circuit = new int[size*2];
	for (int i = 0; i < size*2; i++)
		circuit[i] = -1;

	// index for circuit
	int i = 0;
	// The stack is used to keep track of visited nodes that have no more neighbors
	stack<int> visited;
	
	int loc = start; // start at node with odd degree (if there is one);
	while (!visited.empty() || !H[loc].empty()) {
		// If vector has no neighbors,
		if (H[loc].empty()){
			circuit[i++] = loc;
			loc = visited.top();
			visited.pop();
		}
		// else 
		else {
			// Push current location to the stack
			visited.push(loc);
			// Find the next neighbor
			int neighbor = H[loc][0];
			// delete the edge connecting current vertex and neighbor
			deleteEdge(H, loc, neighbor);
			// current vertex is now the neighbor
			loc = neighbor;
		}
	}
	// get last node
	circuit[i++] = loc;
	return circuit;
};

int* Hamiltonian (int* path, int size) {
	
	//Boolean container for vertices you have visited so they arent repeated
	bool visited[size];
	for (int i = 0; i < size; i++)
		visited[i] = 0;
	
	// New container for Hamiltonian path
	int* C = new int[size];
	
	// iterator indexes
	int i = 0;
	int j = 0;
	
	// While there are inputs from the Euler Circuit (-1 was a appended as a sentinel)
	while (path[i] != -1) {
		// If you have not visited
		if (!visited[path[i]]) {
			// Now you have
			visited[path[i]] = true; 
			// Add the element to the new array C
			C[j] = path[i];
			// increment the new array
			j++;
		}
		// increment the Euler path array whether the value was added or not
		i++;
	}
	return C;
};

int calcDistance(int* path, int** edges, int length) {
	int distance = 0;
	for (int i = 0; i < length - 1; i++)
		distance += edges[path[i]][path[i+1]];
	distance += edges[path[0]][path[length-1]];
	return distance;
};

void twoOpt (int* path, int** edges, int size) {
	int length = 1;
	reverse(path, path+size);
	for (int i = 0; i < size - 1; i+= length) {
		for (int j = i+length; j < size; j+= length) {
			// compare length if you swapped vertices between i an j
			int a = 0,
				b = 0;
			
			// add first edge (path[i] and its predecesor)
			if (i == 0) {
				a += edges[path[i]][path[size-1]];
				b += edges[path[j]][path[size-1]];
			} else {
				a += edges[path[i]][path[i-1]];
				b += edges[path[j]][path[i-1]];
			}
			
			//add second edge (path[j] and the next node)
			if (j == size-1) {
				a += edges[path[j]][path[0]];
				b += edges[path[i]][path[0]];
			} else {
				a += edges [path[j]][path[j+1]];
				b += edges [path[i]][path[j+1]];
			}
			
			// if the length can be shortened, reverse the array
			if (b < a)
				reverse(path+i, path+j+1);
		}
	}
};

void printResults(int** coords, int** edges, int* path, int size, string fileName){
	fileName += ".tour";
	fstream file;
	file.open(fileName, fstream::out);
	if (file.is_open()) {
		cout << "Output file " << fileName << " opened successfully" << endl;
		int pathDistance = calcDistance(path, edges, size);
		file << pathDistance << endl;
		for (int i = 0; i < size; i++)
			file << coords[path[i]][0] << endl;
		file << coords[path[0]][0] << endl;
	}
	else 
		cout << "Problem opening output file " << fileName << endl;
	file.close();
};


int main(int argc, char *argv[]) {
	string fileName;
	for (int i = 1; i < argc; i++) {
		fileName= argv[i];
		int eulerStart = 0;
		int vectorCount = 0;
		int** coordinates = input(fileName, vectorCount);
		if (coordinates) {
			int** edges = getEdgeArray(coordinates, vectorCount);
			int* T = MST(edges, vectorCount);
			int* O = vectorDegree(T, vectorCount); 
			int* P = minimumPairs(O, edges, T, eulerStart, vectorCount);
			vector<vector<int> > H = multigraph(T, P, vectorCount);
			int* E = EulerCircuit(H, eulerStart, vectorCount);
			int* C = Hamiltonian(E, vectorCount);
			twoOpt(C, edges, vectorCount);
			twoOpt(C, edges, vectorCount);
			twoOpt(C, edges, vectorCount);
			twoOpt(C, edges, vectorCount);
			twoOpt(C, edges, vectorCount);
			twoOpt(C, edges, vectorCount);
			printResults(coordinates, edges, C, vectorCount, fileName);
		}
	}
	return 0;
}