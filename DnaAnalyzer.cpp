#include <iostream>
#include <fstream>
#define _USE_MATH_DEFINES //allows me to use the definition of PI from math.h
#include <math.h>
#include <time.h>
#include <algorithm>
using namespace std;

//string ReadFile(string fileName);
void CountIndividualChars(string fileText);
void CountBigrams(string fileText);
float CalcVariance(string fileName);
void OutputToFile(string fileInputName);
float CalcGaussianDistribution(float mean, float variance);
void ResetCounterVars();

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
ofstream outFile;

int main(int argc, char** argv)
{

	if (argc != 2)
	{
		cout << "You did not enter a file Name." << endl;
		cout << "Ensure that you enter a second argument that is the text file that you want to open." << endl;
		exit(1);
	}

	//this ensures that the random numbers generated are actually random, otherwise they would be consistent within runs
	srand(time(NULL));

	outFile.open("StephenWhite.txt");

	outFile << "Stephen White\n002323381\nData Structures Section 1\nAssignment 1: C++ Review" << endl << endl;

	char stay = 'y';
	string enteredFileName;
	enteredFileName = argv[1];

	
	//the while loop that allows the user to input multiple files
	while (stay == 'y')
	{	

		//open the file that was provided
		inputFile.open(enteredFileName);

		//check to make sure that we can open the file in the first place
		if (!inputFile)
		{
			cout << "We were unable to open that file.\nTry a different one or close it before asking us to open it.\n";
			cout << "Enter a file name to analyze:\n";
			cin >> enteredFileName;
			continue;
		}

		string fullFileText;
		string fileLine;
		//go through the file getting each line one at a time and adding them to the full string
		while (std::getline(inputFile, fileLine))
		{
			totalLineCount++;
			fullFileText = fullFileText + fileLine + "\n";

			//now count the bigrams and characters in the line
			CountIndividualChars(fileLine);
			CountBigrams(fileLine);

		}

		//check to see if the file is not empty
		if (totalLineCount == 0)
		{
			inputFile.close();
			cout << "That file was empty. Please choose a different file." << endl;
			cout << "Enter a file name to analyze:\n";
			cin >> enteredFileName;
			continue;
		}
		else if (totalLineCount == 1)
		{
			cout << "CAUTION: your file only has one line. \nThis often times results in invalid probabilities, but I will do my best." << endl;
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

		//print everything to the file
		OutputToFile(enteredFileName);

		cout << "Would you like to go again? (y or n)" << endl;
		cin >> stay;
		
		//to ensure that the amounts counted from the previous run are not carried over into the next
		ResetCounterVars();

		if (stay == 'y')
		{
			cout << "Enter a file name to analyze:\n";
			cin >> enteredFileName;
		}

	}
	cout << "Goodbye!!!! :)\n";
	outFile.close();
	return 0;
}

//FUNCTIONS:

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
		//this was the most effective way I could find to concatinate two chars to a string
		string currentPair = " ";
		currentPair = string(1, fileText[i]);
		currentPair += string(1, fileText[i + 1]);

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
	//if the file only has 1 line, the variation is zero
	if (totalLineCount == 1)
	{
		return 0;
	}

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
	//generate my normalized random numbers
	float a = (float)rand() / (float)RAND_MAX;
	float b = (float)rand() / (float)RAND_MAX;

	float C = sqrt(-2 * log(a)) * cosf(2 * b * M_PI);

	float D = sqrt(variance) * C + mean;

	return D;

}

//Write all the stuffs to file
void OutputToFile(string fileInputName)
{
	//print the name of the file thats being read to better be able to separate the sections in the output file
	outFile << "File being analyzed: " << fileInputName << endl;

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
	outFile << "Standard deviation: " << lineStdDeviation << endl;

	outFile << "Probability of A: " << ((float)numA / (float)totalChars) << "\tC:" << ((float)numC / (float)totalChars) << "\tG:" << ((float)numG / (float)totalChars) << "\tT:" << ((float)numT / (float)totalChars) << endl;
	outFile << "Probability of AA: " << ((float)numAA / (float)totalBigrams) << "\tAC:" << ((float)numAC / (float)totalBigrams) << "\tAG:" << ((float)numAG / (float)totalBigrams) << "\tAT:" << ((float)numAT / (float)totalBigrams) << endl;
	outFile << "Probability of CA: " << ((float)numCA / (float)totalBigrams) << "\tCC:" << ((float)numCC / (float)totalBigrams) << "\tCG:" << ((float)numCG / (float)totalBigrams) << "\tCT:" << ((float)numCT / (float)totalBigrams) << endl;
	outFile << "Probability of GA: " << ((float)numGA / (float)totalBigrams) << "\tGC:" << ((float)numGC / (float)totalBigrams) << "\tGG:" << ((float)numGG / (float)totalBigrams) << "\tGT:" << ((float)numGT / (float)totalBigrams) << endl;
	outFile << "Probability of TA: " << ((float)numTA / (float)totalBigrams) << "\tTC:" << ((float)numTC / (float)totalBigrams) << "\tTG:" << ((float)numTG / (float)totalBigrams) << "\tTT:" << ((float)numTT / (float)totalBigrams) << endl;

	outFile << endl << endl;

	//calculate the probability of each character

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
		//add the calculated number of letters to the string
		for (int aIndex = 0; aIndex < neededA; ++aIndex)
			line += "a";
		for (int cIndex = 0; cIndex < neededC; ++cIndex)
			line += "c";
		for (int gIndex = 0; gIndex < neededG; ++gIndex)
			line += "g";
		for (int tIndex = 0; tIndex < neededT; ++tIndex)
			line += "t";

		//shuffle up the string so it isnt just a's c's and t's in order
		random_shuffle(line.begin(), line.end());
		// print that constructed string to the outfile
		outFile << line << endl;
	}
	//put a few more lines so it is easier to tell the difference between files
	outFile << endl << endl << endl;


	//no need to flush and close because this happens upon destruction anyways
	//outFile.flush();
	//outFile.close();
	
}

void ResetCounterVars()
{
	numA = 0, numT = 0, numC = 0, numG = 0;
	numGC = 0, numGT = 0, numGA = 0, numGG = 0;
	numAA = 0, numAC = 0, numAG = 0, numAT = 0;
	numCA = 0, numCC = 0, numCG = 0, numCT = 0;
	numTA = 0, numTC = 0, numTG = 0, numTT = 0;
	totalChars = 0;
	totalBigrams = 0;
	totalLineLength = 0, totalLineCount = 0;
	lineLengthMean = 0, lineVariance = 0, lineStdDeviation = 0;
	GaussDistr = 0;

	fullFileText = "";
}