#pragma once
#include <string>
#include <vector>
#include <utility>

struct Edge {
    int to;
    double cost;
};

class Graph {
public:
    explicit Graph(int nodes = 0);
    int size() const;
    void addRoad(int u, int v, double cost, bool bidirectional = true);
    const std::vector<Edge>& neighbors(int u) const;
    const std::vector<std::vector<Edge>>& adjacencyList() const;
    std::vector<std::vector<double>> adjacencyMatrix() const;
private:
    std::vector<std::vector<Edge>> adj;
};
