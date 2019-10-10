#pragma once
#include <vector>

using Edge = std::pair<int, int>;

void generateGraph(int vertexCount, std::vector<double> weights, std::vector<Edge> edges);