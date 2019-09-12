#include <iostream>
#include <fstream>
using namespace std;

string ReadFile(string fileName);
string PrintSummary();
void CountIndividualChars(string fileText);
void CountBigrams(string fileText);

//my counting variables for keeping track of the amount of each nucliotide and bigram
int numA = 0, numT, numC = 0, numG = 0;
int numGC = 0, numGT = 0, numGA = 0, numGG = 0;
int numAA = 0, numAC = 0, numAG = 0, numAT = 0;
int numCA = 0, numCC = 0, numCG = 0, numCT = 0;
int numTA = 0, numTC = 0, numTG = 0, numTT = 0;
int totalChars = 0;
int totalBigrams = 0;
int totalLineLength = 0, totalLineCount = 0;
int lineLengthMean = 0, lineVariance = 0, lineStdDeviation = 0;

string fullFileText = "";

int main(int argc, char** argv)
{
	//check to make sure that the user has given two inputs (including the argument to run the file itself)
	if (argc != 2)
	{
		cout << "You must enter a file name.\n";
		return 1;
	}

	//read the file and get the string of the contents
	//fullFileText = ReadFile(argv[1]);
#pragma region Reading the file

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
		totalLineCount++;
		fullFileText = fullFileText + fileLine + "\n";

		CountIndividualChars(fileLine);
		CountBigrams(fileLine);

	}

	//make every letter lower case
	string lowerFileText;
	for (int i = 0; i < fullFileText.length(); ++i)
	{
		lowerFileText += tolower(fullFileText[i]);
	}

	inputFile.close();

	fullFileText = lowerFileText;

#pragma endregion

	//print the contents to ensure that the file is correct. (mostly for testing)
	cout << "This is what was read from the file:\n";
	cout << fullFileText <<endl;

	//my counting variables for keeping track of the amount of each nucliotide and bigram
	/*int numA, numT, numC = 0, numG = 0;
	int numGC, numGT, numGA, numGG;
	int numAA, numAC, numAG, numAT;
	int numCA, numCC, numCG, numCT;
	int numTA, numTC, numTG, numTT;
	int totalChars = 0;
	int totalBigrams = 0;
	int totalLineLength = 0, totalLineCount = 0;*/

	//count the individual letters
	/*
	for (char letter : fullFileText)
	{
		int curLineLength = 0;

		//ensure that the letter its counting is only a nucleotide. (to avoid the \n i inserted after each line)
		if (letter == 'a')
			numA++;
		else if (letter == 'c')
			numC++;
		else if (letter == 'g')
			numG++;
		else if (letter == 't')
			numT++;
		else if (letter == '\\')//check to see if at the end of the line
		{
			totalLineLength += curLineLength;
			totalLineCount++;
			curLineLength = 0;
			continue;
		}
		//if the character is not a nucleotide, skip and continue through the loop without counting it
		else
			continue;

		curLineLength++;
		totalChars++;
	}

	cout << "Finished Counting Chars " << totalChars << "\n";
	*/

	//check to make sure that there is an even number of characters. if its odd, then skip the last one.
	if (totalChars % 2 != 0)
	{
		totalChars--;
	}

	cout << "Full file text: \n" << fullFileText << endl;

	cout << "Ensure Counting Chars is even " << totalChars << "\n";

	//count every pair of nucleotides (bigrams)
	/*
	for (int i = 0; i < totalChars; i += 2)
	{
		//cout << "I = " << i << endl;
		string currentPair = " ";
		currentPair = string(1, fullFileText[i]);
		currentPair += string(1, fullFileText[i + 1]);

		cout << "Current Pair: " << currentPair << endl;

		if (currentPair == "aa")
			numAA++;
		else if (currentPair == "ac")
			numAC++;
		else if (currentPair == "ag")
			numAG++;
		else if (currentPair == "at")
			numAT++;
		else if (currentPair == "ca")
			numCA++;
		else if (currentPair == "cc")
			numCC++;
		else if (currentPair == "cg")
			numCG++;
		else if (currentPair == "ct")
			numCT++;
		else if (currentPair == "ga")
			numGA++;
		else if (currentPair == "gc")
			numGC++;
		else if (currentPair == "gg")
			numGG++;
		else if (currentPair == "gt")
			numGT++;
		else if (currentPair == "ta")
			numTA++;
		else if (currentPair == "tc")
			numTC++;
		else if (currentPair == "tg")
			numTG++;
		else if (currentPair == "tt")
			numTT++;
		else
			continue;

		totalBigrams++;
		//i += 2;
	}
	*/


	//calculate the mean length of each string
	lineLengthMean = totalChars / totalLineCount;


	

	//print everything
	PrintSummary();
}

//FUNCTIONS:

//this function will read the text file and return the string contents of the file
//this function will ensure that the text is lowercase
string ReadFile(string fileName)
{
	//this is the variable 
	ifstream inputFile;

	//open the file that was provided
	inputFile.open(fileName);

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
		totalLineCount++;
		fullFileText = fullFileText + fileLine + "\n";
	}

	//make every letter lower case
	string lowerFileText;
	for (int i = 0; i < fullFileText.length(); ++i)
	{
		lowerFileText += tolower(fullFileText[i]);
	}

	inputFile.close();

	return lowerFileText;
}

//this will write everything to a file
void WriteToFile()
{

}

//prints the summary of the statistics
string PrintSummary()
{
	//string outputString = "";
	//build the output string
	cout << "Total Number of characters: " << totalChars << endl;
	cout << "Total number of bigrams: " << totalBigrams <<endl;
	cout << "Total number of lines: " << totalLineCount << endl;
	cout << "Total length of lines: " << totalLineLength <<endl;
	cout << "Total number of A\'s: " << numA;
	cout << "\tC\'s: " << numC;
	cout << "\tG\'s:" << numG;
	cout << "\tT\'s:" << numT << endl;

	cout << "Total number of AA's: " << numAA << "\tAC's: " << numAC << "\tAG's: " << numAG << "\tAT's: " << numAT << endl;
	cout << "Total number of CA's: " << numCA << "\tCC's: " << numCC << "\tCG's: " << numCG << "\tCT's: " << numCT << endl;
	cout << "Total number of GA's: " << numGA << "\tGC's: " << numGC << "\tGG's: " << numGG << "\tGT's: " << numGT << endl;
	cout << "Total number of TA's: " << numTA << "\tTC's: " << numTC << "\tTG's: " << numTG << "\tTT's: " << numTT << endl;

	cout << "Average line length: " << lineLengthMean << endl;

	//finally print it

	cout << "Done\n";
	exit(0);
}

//counts the individual chars of the given string
void CountIndividualChars(string fileText)
{
	for (char letter : fileText)
	{
		int curLineLength = 0;

		//ensure that the letter its counting is only a nucleotide. (to avoid the \n i inserted after each line)
		if (letter == 'a')
			numA++;
		else if (letter == 'c')
			numC++;
		else if (letter == 'g')
			numG++;
		else if (letter == 't')
			numT++;
		else if (letter == '\\')//check to see if at the end of the line
		{
			totalLineLength += curLineLength;
			totalLineCount++;
			curLineLength = 0;
			continue;
		}
		//if the character is not a nucleotide, skip and continue through the loop without counting it
		else
			continue;

		curLineLength++;
		totalChars++;
	}

	cout << "Finished Counting Chars " << totalChars << "\n";
}

void CountBigrams(string fileText)
{
	//count every pair of nucleotides (bigrams)
	for (int i = 0; i < totalChars; i += 2)
	{
		//cout << "I = " << i << endl;
		string currentPair = " ";
		currentPair = string(1, fileText[i]);
		currentPair += string(1, fileText[i + 1]);

		//cout << "Current Pair: " << currentPair << endl;

		if (currentPair == "aa")
			numAA++;
		else if (currentPair == "ac")
			numAC++;
		else if (currentPair == "ag")
			numAG++;
		else if (currentPair == "at")
			numAT++;
		else if (currentPair == "ca")
			numCA++;
		else if (currentPair == "cc")
			numCC++;
		else if (currentPair == "cg")
			numCG++;
		else if (currentPair == "ct")
			numCT++;
		else if (currentPair == "ga")
			numGA++;
		else if (currentPair == "gc")
			numGC++;
		else if (currentPair == "gg")
			numGG++;
		else if (currentPair == "gt")
			numGT++;
		else if (currentPair == "ta")
			numTA++;
		else if (currentPair == "tc")
			numTC++;
		else if (currentPair == "tg")
			numTG++;
		else if (currentPair == "tt")
			numTT++;
		else
			continue;

		totalBigrams++;
		//i += 2;
	}
}

