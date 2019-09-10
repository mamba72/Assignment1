#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char** argv)
{
	//check to make sure that the user has given two inputs (including the argument to run the file itself)
	if (argc != 2)
	{
		cout << "You must enter a file name.\n";
		return 1;
	}

	//this is the variable 
	ifstream inputFile;

	inputFile.open(argv[1]);






}