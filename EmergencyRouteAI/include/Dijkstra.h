#pragma once
#include "Graph.h"
#include "PathResult.h"
PathResult dijkstra(const Graph& graph, int start, int goal);
PathResult dijkstraMatrix(const Graph& graph, int start, int goal);
