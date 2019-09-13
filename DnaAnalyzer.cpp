#include <iostream>
#include <fstream>
#define _USE_MATH_DEFINES //allows me to use the definition of PI from math.h
#include <math.h>
#include <time.h>
using namespace std;


//#define M_PI

string ReadFile(string fileName);
string PrintSummary();
void CountIndividualChars(string fileText);
void CountBigrams(string fileText);
float CalcVariance(string fileName);
void OutputToFile(string fileName);
float CalcGaussianDistribution(float mean, float variance);

//my counting variables for keeping track of the amount of each nucliotide and bigram
int numA = 0, numT = 0, numC = 0, numG = 0;
int numGC = 0, numGT = 0, numGA = 0, numGG = 0;
int numAA = 0, numAC = 0, numAG = 0, numAT = 0;
int numCA = 0, numCC = 0, numCG = 0, numCT = 0;
int numTA = 0, numTC = 0, numTG = 0, numTT = 0;
int totalChars = 0;
int totalBigrams = 0;
int totalLineLength = 0, totalLineCount = 0;
float lineLengthMean = 0, lineVariance = 0, lineStdDeviation = 0;
float GaussDistr = 0;

string fullFileText = "";

//this is the variable that will be reading the file
ifstream inputFile;

int main(int argc, char** argv)
{
	srand(time(NULL));

	//check to make sure that the user has given two inputs (including the argument to run the file itself)
	//if (argc != 2)
	//{
		//cout << "You must enter a file name.\n";
		//return 1;
	//}

	//read the file and get the string of the contents
	//fullFileText = ReadFile(argv[1]);

	char stay = 'y';

	while (stay == 'y')
	{

		string enteredFileName;
		cout << "Enter a file name to analyze:\n";
		cin >> enteredFileName;

		//open the file that was provided
		inputFile.open(enteredFileName);

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
		//set the text to all lower case
		fullFileText = lowerFileText;

		//check to make sure that there is an even number of characters. if its odd, then skip the last one.
		if (totalChars % 2 != 0)
		{
			totalChars--;
		}



		//calculate the mean length of each string
		lineLengthMean = totalChars / totalLineCount;

		//total line length = total chars
		totalLineLength = totalChars;

		//calculate the variance of the line lengths
		lineVariance = CalcVariance(enteredFileName);

		//calculate gaussian / normal distribution
		GaussDistr = CalcGaussianDistribution(lineLengthMean, lineVariance);

		cout << "GaussDistr: " << GaussDistr << endl;

		//print everything
		//PrintSummary();

		OutputToFile("StephenWhite.txt");

		cout << "Would you like to go again? (y or n)" << endl;
		cin >> stay;
		
	}
	cout << "Goodbye!!!!\n";
	return 0;
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
	cout << "Line length variance: " << lineVariance << endl;
	cout << "Standard deviatoin: " << lineStdDeviation << endl;

	//finally print it

	cout << "Done\n";
	
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

//this function will return the variance of the length of each line.
float CalcVariance(string fileName)
{
	//open up the file again
	inputFile.open(fileName);

	//get the sum of (line length - average line length) ^ 2
	float differenceSum = 0;
	string line;
	while (getline(inputFile, line))
	{
		differenceSum += pow(line.length() - lineLengthMean, 2);
	}
	inputFile.close();

	//divide by the number of lines - 1
	float variance = differenceSum / (totalLineCount - 1);

	//set standard deviation equal to the square root of variance
	lineStdDeviation = sqrt(variance);

	return variance;
}

//calculate the gaussian / normal distribution from the given hint
float CalcGaussianDistribution(float mean, float variance)
{
	

	float a = (float)rand() / (float)RAND_MAX;
	float b = (float)rand() / (float)RAND_MAX;

	float C = sqrt(-2 * log(a)) * cosf(2 * b * M_PI);

	float D = sqrt(variance) * C + mean;

	return D;

}

//Write all the stuffs to file
void OutputToFile(string fileName)
{
	ofstream outFile;
	outFile.open(fileName);

	outFile << "Stephen White\n002323381\nData Structures Section 1\nAssignment 1: C++ Review" << endl <<endl;

	outFile << "Total Number of characters: " << totalChars << endl;
	outFile << "Total number of bigrams: " << totalBigrams << endl;
	outFile << "Total number of lines: " << totalLineCount << endl;
	outFile << "Total length of lines: " << totalLineLength << endl;
	outFile << "Total number of A\'s: " << numA;
	outFile << "\tC\'s: " << numC;
	outFile << "\tG\'s:" << numG;
	outFile << "\tT\'s:" << numT << endl;

	outFile << "Total number of AA's: " << numAA << "\tAC's: " << numAC << "\tAG's: " << numAG << "\tAT's: " << numAT << endl;
	outFile << "Total number of CA's: " << numCA << "\tCC's: " << numCC << "\tCG's: " << numCG << "\tCT's: " << numCT << endl;
	outFile << "Total number of GA's: " << numGA << "\tGC's: " << numGC << "\tGG's: " << numGG << "\tGT's: " << numGT << endl;
	outFile << "Total number of TA's: " << numTA << "\tTC's: " << numTC << "\tTG's: " << numTG << "\tTT's: " << numTT << endl;

	outFile << "Average line length: " << lineLengthMean << endl;
	outFile << "Line length variance: " << lineVariance << endl;
	outFile << "Standard deviatoin: " << lineStdDeviation << endl;

	outFile << "Probability of A: " << ((float)numA / (float)totalChars) << "\tC:" << ((float)numC / (float)totalChars) << "\tG:" << ((float)numG / (float)totalChars) << "\tT:" << ((float)numT / (float)totalChars) << endl;
	outFile << "Probability of AA: " << ((float)numAA / (float)totalChars) << "\tAC:" << ((float)numAC / (float)totalChars) << "\tAG:" << ((float)numAG / (float)totalChars) << "\tAT:" << ((float)numAT / (float)totalChars) << endl;
	outFile << "Probability of CA: " << ((float)numCA / (float)totalChars) << "\tCC:" << ((float)numCC / (float)totalChars) << "\tCG:" << ((float)numCG / (float)totalChars) << "\tCT:" << ((float)numCT / (float)totalChars) << endl;
	outFile << "Probability of GA: " << ((float)numGA / (float)totalChars) << "\tGC:" << ((float)numGC / (float)totalChars) << "\tGG:" << ((float)numGG / (float)totalChars) << "\tGT:" << ((float)numGT / (float)totalChars) << endl;
	outFile << "Probability of TA: " << ((float)numTA / (float)totalChars) << "\tTC:" << ((float)numTC / (float)totalChars) << "\tTG:" << ((float)numTG / (float)totalChars) << "\tTT:" << ((float)numTT / (float)totalChars) << endl;

	outFile << endl << endl;

	float aProb = ((float)numA / (float)totalChars);
	float cProb = ((float)numC / (float)totalChars);
	float gProb = ((float)numG / (float)totalChars);
	float tProb = ((float)numT / (float)totalChars);

	//write the 1000 lines of stuff
	for (int i = 0; i < 1000; ++i)
	{
		float gauss = CalcGaussianDistribution(lineLengthMean, lineVariance);
		//find out how many of each nucleotide we need
		int neededA = gauss * aProb;
		int neededC = gauss * cProb;
		int neededG = gauss * gProb;
		int neededT = gauss * tProb;

		//now construct the line
		string line = "";
		
		for (int aIndex = 0; aIndex < neededA; ++aIndex)
			line += "a";
		for (int cIndex = 0; cIndex < neededC; ++cIndex)
			line += "c";
		for (int gIndex = 0; gIndex < neededG; ++gIndex)
			line += "g";
		for (int tIndex = 0; tIndex < neededT; ++tIndex)
			line += "t";

		outFile << line << endl;
	}



	outFile.flush();
	outFile.close();
	
}