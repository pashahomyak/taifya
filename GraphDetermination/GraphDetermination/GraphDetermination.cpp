#include "stdafx.h"

using namespace std;


vector<string> getReplacedStringToElements(string element)
{
	vector<string> elems;

	std::stringstream ss(element);
	std::string item;
	while (getline(ss, item, 'q'))
	{
		elems.push_back("q" + item);
	}

	sort(elems.begin(), elems.end());
	if (elems.capacity() > 1)
	{
		elems.erase(elems.begin());
		elems.resize(elems.size());
	}
	
	auto last = unique(elems.begin(), elems.end());
	elems.erase(last, elems.end());
	elems.resize(elems.size());

	return elems;
}

bool checkVertexInConversions(string vertex, map<Nav, string>& conversions)
{
	bool inMap = false;

	for (auto element : conversions)
	{
		if (element.first.first == vertex)
		{
			inMap = true;
			break;
		}
	}

	return inMap;
}

string generateVertexConversionValue(Nav pair, map<Nav, string>& conversions)
{
	string value;

	vector<string> elements = getReplacedStringToElements(pair.first);

	vector<string> valueParts;

	for (string element : elements)
	{
		auto it = conversions.find({ element, pair.second });

		if (it != conversions.end())
		{
			if (valueParts.empty())
			{
				auto v1 = getReplacedStringToElements(it->second);
				valueParts = v1;
			}
			else
			{
				vector<string> temp;
				
				auto v1 = getReplacedStringToElements(it->second);
				set_union(valueParts.begin(), valueParts.end(),
					v1.begin(), v1.end(), std::back_inserter(temp));

				valueParts = temp;

				temp.clear();
			}
		}
	}

	sort(valueParts.begin(), valueParts.end());
	auto last = unique(valueParts.begin(), valueParts.end());
	valueParts.erase(last, valueParts.end());

	for (string valuePart : valueParts)
	{
		value += valuePart;
	}

	return  value;
}

void generateEdges(vector<string> &vertexes, map<Nav, string> &conversions, int numOfRow)
{
	vector<string> temp;
	
	for (auto edge : vertexes)
	{
		if (!checkVertexInConversions(edge, conversions))
		{
			for (int i = 0; i < numOfRow; i++)
			{
				Nav pair = { edge, i };
				string resultValue = generateVertexConversionValue(pair, conversions);

				if (resultValue != "")
				{
					conversions[pair] = resultValue;

					auto it = find(vertexes.begin(), vertexes.end(), resultValue);
					if (it == vertexes.end())
					{
						temp.push_back(resultValue);
					}
				}
			}
			
		}
	}

	if (!temp.empty())
	{
		for (auto element : temp)
		{
			vertexes.push_back(element);
		}
		
		generateEdges(vertexes, conversions, numOfRow);
		
		temp.clear();
	}
}

void graphView(vector<string> vertexes, map<Nav, string> conversions)
{
	std::ofstream outputGraph("outputGraph.dot");

	outputGraph << "digraph G {" << std::endl;

	for (const auto& vertex : vertexes)
	{
		outputGraph << vertex << ";" << std::endl;
	}

	for (auto element : conversions)
	{
		outputGraph << element.first.first << "->" << element.second << "  [label=x" << element.first.second << "];" << std::endl;
	}

	outputGraph << "}" << std::endl;
}

void printTable(vector<string> vertexes, map<Nav, string> conversions, ostream& output, int numOfRow)
{
	for (auto i = 0; i < numOfRow; i++)
	{
		for (auto j = 0; j < vertexes.size(); j++)
		{
			string el = conversions[{vertexes[j], i}];
			if (el != "")
			{
				output << el << " ";
			}
			else
			{
				output << "-" << " ";
			}
		}
		output << endl;
	}
}

vector<string> fillUniqueVertexes(vector<string> vertexes, int numOfColumn)
{
	vector<string> uniqueVertexes;
	
	for (int i = 0; i < numOfColumn; i++)
	{
		uniqueVertexes.push_back("q" + std::to_string(i));
	}
	for (auto vertex : vertexes)
	{
		auto iter = find(uniqueVertexes.begin(), uniqueVertexes.end(), vertex);
		if (iter == uniqueVertexes.end())
		{
			uniqueVertexes.push_back(vertex);
		}
	}

	return uniqueVertexes;
}

int main()
{
	ifstream inputFile("input.txt");
	ofstream outputFile("output.txt");

	int numOfRow;
	int numOfColumn;

	inputFile >> numOfRow >> numOfColumn;

	map<Nav, string> conversions;

	string element;
	vector<string> vertexes;
	
	for (int i = 0; i < numOfRow; i++)
	{
		for (int j = 0; j < numOfColumn; j++)
		{
			inputFile >> element;

			if (element != "-")
			{
				conversions[{ "q" + std::to_string(j), i }] = element;
				vertexes.push_back(element);
			}
		}
	}

	generateEdges(vertexes, conversions, numOfRow);
	
	vector<string> uniqueVertexes = fillUniqueVertexes(vertexes, numOfColumn);

	printTable(uniqueVertexes, conversions, outputFile, numOfRow);
	graphView(uniqueVertexes, conversions);
}