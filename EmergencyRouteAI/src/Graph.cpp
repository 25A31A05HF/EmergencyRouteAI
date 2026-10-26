#include "Graph.h"
#include <stdexcept>

Graph::Graph(int nodes) : adj(nodes) {}
int Graph::size() const { return static_cast<int>(adj.size()); }

void Graph::addRoad(int u, int v, double cost, bool bidirectional) {
    if (u < 0 || v < 0 || u >= size() || v >= size())
        throw std::out_of_range("Road endpoint is outside the graph.");
    if (cost < 0) throw std::invalid_argument("Road costs must be non-negative.");
    adj[u].push_back({v, cost});
    if (bidirectional) adj[v].push_back({u, cost});
}
const std::vector<Edge>& Graph::neighbors(int u) const { return adj.at(u); }
const std::vector<std::vector<Edge>>& Graph::adjacencyList() const { return adj; }

std::vector<std::vector<double>> Graph::adjacencyMatrix() const {
    const double INF = 1e100;
    std::vector<std::vector<double>> m(size(), std::vector<double>(size(), INF));
    for (int i = 0; i < size(); ++i) {
        m[i][i] = 0;
        for (const auto& e : adj[i]) {
            if (e.cost < m[i][e.to]) m[i][e.to] = e.cost;
        }
    }
    return m;
}
