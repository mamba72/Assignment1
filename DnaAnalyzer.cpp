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

	//open the file that was provided
	inputFile.open(argv[1]);

	//check to make sure that we can open the file in the first place
	if (!inputFile)
	{
		cout << "We were unable to open that file.\nTry a different one or close it before asking us to open it.\n";
		exit(1);
	}

	string fullFileText;
	string fileLine;
	//go through the file getting each line one at a time and adding them to the full string
	while (std::getline(inputFile, fileLine))
	{
		fullFileText = fullFileText + fileLine + "\n";
	}

	cout << "This is what was read from the file:\n";
	cout << fullFileText <<endl;

	int numA;
	int numC;
	int numG;
	int numT;
	int numGC;
	int numGT;
	int numGA;
	int numGG;
	int numAA;
	int numAC;
	int numAG;
	int numAT;
	int numCA, numCC, numCG, numCT;
	int numTA, numTC, numTG, numTT;





}