/*****************************************************************************************
Name: Jacob Skinner
Date: Nov 13, 2016
Desc: This function validates user input of an integer.
*****************************************************************************************/

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
using std::string;
using std::cin;
using std::cout;
using std::stringstream;
using std::endl;

void getInt(int &num)
{
	string input;
	getline(cin, input);
	bool validate = true;
	if (input.empty())
		validate = false;
	for (int i = 0; i < input.length(); i++)
	{
		if (!(isdigit(input[i])))
		{
			validate = false;
			break;
		}
	}
		
	if (validate == true)
	{
		stringstream ss;
		ss.str(input);
		ss >> num;
	}
	else
	{
		cout << "Please input an integer." << endl;
		getInt(num);
	}
}