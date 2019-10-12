//название вершин задано числом (1 -> z1)
//названия дуг аналогично (1 -> x1 for mealy) (1.1 -> x1y1) (2 -> x2y0 for moore)

#include "stdafx.h"
#include "transformMachine.h"

using namespace std;

int main()
{
	ifstream inputFile("input.txt");
	ofstream outputFile("output.txt");

	int numOfInputCharsAlphabet;
	int numOfOutCharsAlphabet;
	int numOfVertex;
	string typeOfMachine;

	inputFile >> numOfInputCharsAlphabet >> numOfOutCharsAlphabet >> numOfVertex >> typeOfMachine;

	if (typeOfMachine == "moore")
	{
		transformToMealy(numOfInputCharsAlphabet, numOfVertex, inputFile, outputFile);
	}
	else if (typeOfMachine == "mealy")
	{
		transformToMoore(numOfInputCharsAlphabet, numOfVertex, inputFile, outputFile);
	}
}