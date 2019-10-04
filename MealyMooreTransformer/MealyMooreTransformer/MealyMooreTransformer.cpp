#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

#include <boost/graph/graphviz.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <algorithm>

#define _SCL_SECURE_NO_WARNINGS

using namespace std;
using Edge = pair<int, int>;

void generateGraph(int vertexCount, vector<double> weights, vector<Edge> edges);

void makeSimpleDot1()
{
	using Edge = std::pair<int, int>;
	using Graph = boost::adjacency_list< boost::vecS, boost::vecS, boost::directedS, boost::property< boost::vertex_color_t, boost::default_color_type >, boost::property< boost::edge_weight_t, double>>;

	const int VERTEX_COUNT = 15;
	std::vector<Edge> edges = {
	{0, 4}, {0, 6}, {0, 1}, {1, 6}, {1, 11},
	{2, 6}, {2, 9}, {2, 11}, {3, 4}, {4, 5},
	{5, 8}, {6, 7}, {7, 8}, {8, 13},
	{9, 10}, {10, 13}, {11, 12}, {12, 13}, {13, 14},
	};
	std::vector<double> weights(edges.size());
	std::fill(weights.begin(), weights.end(), 1.0);
	weights[1] = 0.5;
	weights[2] = 2.5;
	weights[3] = 4.3;
	Graph graph(edges.begin(), edges.end(), weights.begin(),
		VERTEX_COUNT);

	boost::dynamic_properties dp;
	dp.property("weight", boost::get(boost::edge_weight,
		graph));
	dp.property("label", boost::get(boost::edge_weight,
		graph));
	dp.property("node_id", boost::get(boost::vertex_index,
		graph));
	std::ofstream ofs("test.dot");
	boost::write_graphviz_dp(ofs, graph, dp);
}

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
		map<string, string> yIndexez;
		string currY;
		for (size_t i = 0; i < numOfVertex; i++)
		{
			inputFile >> currY;
			yIndexez["q" + to_string(i)] = "q" + to_string(i) + currY;
		}

		vector<Edge> edges;
		vector<double> weights;
		string element;

		for (int i = 0; i < numOfInputCharsAlphabet; i++)
		{
			for (int j = 0; j < numOfVertex; j++)
			{
				inputFile >> element;

				outputFile << yIndexez[element] << " ";

				edges.push_back({ j, stoi(element.substr(1)) });
				string doubleWeight = (to_string(i + 1) + "." + yIndexez[element].substr(yIndexez[element].find_first_of('y') + 1));
				double currWeight = stod(doubleWeight);
				weights.push_back(currWeight);
			}
			outputFile << endl;
		}
		generateGraph(numOfVertex, weights, edges);
	}
	else if (typeOfMachine == "mealy")
	{
		vector<vector<string>> inputTable(numOfInputCharsAlphabet, vector<string>(numOfVertex));

		string element;

		map<string, string> zItems;
		map<string, string> zItemsReverse;
		for (int i = 0; i < numOfInputCharsAlphabet; i++)
		{
			for (int j = 0; j < numOfVertex; j++)
			{
				inputFile >> element;
				inputTable[i][j] = element;

				auto it1 = zItemsReverse.find(element);
				if (it1 == zItemsReverse.end())
				{
					//zItemsReverse[element] = "z" + to_string(zItemsReverse.size());
					zItemsReverse[element] = to_string(zItemsReverse.size());
					zItems["z" + to_string(zItems.size())] = element;
				}
			}
		}

		//using Edge = pair<string, string>;
		vector<Edge> edges;
		vector<double> weights;

		vector<vector<string>> resultTable(numOfInputCharsAlphabet, vector<string>(zItems.size()));
		for (int i = 0; i < numOfInputCharsAlphabet; i++)
		{
			for (int j = 0; j < zItems.size(); j++)
			{
				string currItem = "z" + to_string(j);
				auto yIndex = zItems[currItem].find("y");
				int index = stoi(zItems[currItem].substr(1, yIndex));

				string resultItem = zItemsReverse[inputTable[i][index]];
				
				resultTable[i][j] = resultItem;
				outputFile << "z" + resultItem << " ";

				edges.push_back({j, stoi(resultItem)});
				//weights.push_back("x" + to_string(i));
				weights.push_back(i + 1);
			}
			outputFile << endl;
		}
		generateGraph(numOfVertex, weights, edges);
	}
}

void generateGraph(int vertexCount, vector<double> weights, vector<Edge> edges)
{
	using Graph = boost::adjacency_list< boost::vecS, boost::vecS, boost::directedS, boost::property< boost::vertex_color_t, boost::default_color_type >, boost::property< boost::edge_weight_t, double>>;

	Graph graph(edges.begin(), edges.end(), weights.begin(), vertexCount);

	boost::dynamic_properties dp;
	dp.property("weight", boost::get(boost::edge_weight,
		graph));
	dp.property("label", boost::get(boost::edge_weight,
		graph));
	dp.property("node_id", boost::get(boost::vertex_index,
		graph));
	std::ofstream ofs("test.dot");
	boost::write_graphviz_dp(ofs, graph, dp);
}