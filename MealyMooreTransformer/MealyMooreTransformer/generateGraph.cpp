#include "generateGraph.h"
#include "stdafx.h"

using namespace std;

void generateGraph(int vertexCount, vector<string> weights, vector<Edge> edges)
{
	using Graph = boost::adjacency_list< boost::vecS, boost::vecS, boost::directedS, boost::property< boost::vertex_color_t, boost::default_color_type >, boost::property< boost::edge_weight_t, string>>;

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