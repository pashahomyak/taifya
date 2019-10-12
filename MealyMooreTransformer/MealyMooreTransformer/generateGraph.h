#pragma once
#include <vector>
#include <string>

using Edge = std::pair<int, int>;

void generateGraph(int vertexCount, std::vector<std::string> weights, std::vector<Edge> edges);