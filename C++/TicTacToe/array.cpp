#include <iostream>
using namespace std;

int main()
{
	system("clear");
	
	int array[4][4];
	for (int x = 0; x < 4; x++)
	{
		array[x][0] = 1;
		array[x][1] = 2;
		array[x][2] = 3;
		array[x][3] = 4;
	}
	
	for (int y = 0; y<4; y++)
	{
		for (int x = 0; x<4; x++)
			cout << array[x][y] << " ";
		cout << endl;
	}


	if (array[0][0] == array[1][0] == array[2][0] == array[3][0])
		cout << "Equivalence works!" << endl;

	return 0;
}