#include "transformMachine.h"
#include "stdafx.h"
#include "generateGraph.h"

using namespace std;

void transformToMoore(int numOfInputCharsAlphabet, int numOfVertex, ifstream& inputFile, ofstream& outputFile)
{
	vector<vector<string>> inputTable(numOfInputCharsAlphabet, vector<string>(numOfVertex));

	string element;

	vector<string> sortedElements;

	map<string, string> zItems;
	map<string, string> zItemsReverse;
	for (int i = 0; i < numOfInputCharsAlphabet; i++)
	{
		for (int j = 0; j < numOfVertex; j++)
		{
			inputFile >> element;

			sortedElements.push_back(element);

			inputTable[i][j] = element;
		}
	}

	sort(sortedElements.begin(), sortedElements.end());
	sort(sortedElements.begin(), sortedElements.end(), compareLength);

	for (auto el : sortedElements)
	{
		auto it = zItemsReverse.find(el);
		if (it == zItemsReverse.end())
		{
			zItemsReverse[el] = to_string(zItemsReverse.size());
			zItems["z" + to_string(zItems.size())] = el;
		}
	}

	vector<Edge> edges;
	vector<string> weights;

	vector<vector<string>> resultTable(numOfInputCharsAlphabet, vector<string>(zItems.size()));
	for (int i = 0; i < numOfInputCharsAlphabet; i++)
	{
		for (size_t j = 0; j < zItems.size(); j++)
		{
			string currItem = "z" + to_string(j);
			auto yIndex = zItems[currItem].find("y");
			int index = stoi(zItems[currItem].substr(1, yIndex));

			string resultItem = zItemsReverse[inputTable[i][index]];

			resultTable[i][j] = resultItem;
			outputFile << "z" + resultItem << " ";

			edges.push_back({ j, stoi(resultItem) });
			weights.push_back("x" + to_string(i));
		}
		outputFile << endl;
	}
	generateGraph(numOfVertex, weights, edges);
}

void transformToMealy(int numOfInputCharsAlphabet, int numOfVertex, std::ifstream& inputFile, std::ofstream& outputFile)
{
	map<string, string> yIndexes;
	string currY;
	for (int i = 0; i < numOfVertex; i++)
	{
		inputFile >> currY;
		yIndexes["q" + to_string(i)] = "q" + to_string(i) + currY;
	}

	vector<Edge> edges;
	vector<string> weights;
	string element;

	for (int i = 0; i < numOfInputCharsAlphabet; i++)
	{
		for (int j = 0; j < numOfVertex; j++)
		{
			inputFile >> element;

			outputFile << yIndexes[element] << " ";

			edges.push_back({ j, stoi(element.substr(1)) });
			string currWeight = ("x" + to_string(i) + "y" + yIndexes[element].substr(yIndexes[element].find_first_of('y') + 1));
			weights.push_back(currWeight);
		}
		outputFile << endl;
	}
	generateGraph(numOfVertex, weights, edges);
}

bool compareLength(string s1, string s2) { return (s1.length() < s2.length()); }