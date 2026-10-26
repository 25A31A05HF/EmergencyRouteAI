#pragma once
#include "Graph.h"
#include "PathResult.h"
#include <vector>
PathResult aStarGrid(const Graph& graph, int start, int goal, int width);
