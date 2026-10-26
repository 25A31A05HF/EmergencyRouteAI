#include "Dijkstra.h"
#include <queue>
#include <chrono>
#include <algorithm>
#include <stdexcept>

using Clock = std::chrono::steady_clock;
static void validate(const Graph& g, int s, int t) {
    if (s < 0 || t < 0 || s >= g.size() || t >= g.size())
        throw std::out_of_range("Start or destination node is invalid.");
}
static std::vector<int> rebuild(const std::vector<int>& prev, int s, int t) {
    if (s == t) return {s};
    if (prev[t] == -1) return {};
    std::vector<int> p;
    for (int cur = t; cur != -1; cur = prev[cur]) p.push_back(cur);
    std::reverse(p.begin(), p.end());
    if (p.empty() || p.front() != s) return {};
    return p;
}
PathResult dijkstra(const Graph& g, int s, int t) {
    validate(g, s, t);
    auto begin = Clock::now();
    const double INF = 1e100;
    std::vector<double> dist(g.size(), INF);
    std::vector<int> prev(g.size(), -1);
    using Item = std::pair<double,int>;
    std::priority_queue<Item, std::vector<Item>, std::greater<Item>> pq;
    dist[s] = 0; pq.push({0,s});
    int expanded = 0;
    while (!pq.empty()) {
        auto [d,u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;
        ++expanded;
        if (u == t) break;
        for (const auto& e : g.neighbors(u)) {
            double nd = d + e.cost;
            if (nd < dist[e.to]) {
                dist[e.to] = nd; prev[e.to] = u;
                pq.push({nd, e.to});
            }
        }
    }
    PathResult r;
    r.path = rebuild(prev, s, t); r.cost = dist[t]; r.expanded = expanded;
    r.milliseconds = std::chrono::duration<double,std::milli>(Clock::now()-begin).count();
    return r;
}
PathResult dijkstraMatrix(const Graph& g, int s, int t) {
    validate(g, s, t);
    auto begin = Clock::now();
    auto m = g.adjacencyMatrix();
    const double INF = 1e100;
    std::vector<double> dist(g.size(), INF);
    std::vector<int> prev(g.size(), -1);
    std::vector<bool> used(g.size(), false);
    dist[s] = 0; int expanded = 0;
    for (int iter = 0; iter < g.size(); ++iter) {
        int u = -1;
        for (int i = 0; i < g.size(); ++i)
            if (!used[i] && (u == -1 || dist[i] < dist[u])) u = i;
        if (u == -1 || dist[u] >= INF/2) break;
        used[u] = true; ++expanded;
        if (u == t) break;
        for (int v = 0; v < g.size(); ++v) {
            if (m[u][v] < INF/2 && dist[u] + m[u][v] < dist[v]) {
                dist[v] = dist[u] + m[u][v]; prev[v] = u;
            }
        }
    }
    PathResult r;
    r.path = rebuild(prev, s, t); r.cost = dist[t]; r.expanded = expanded;
    r.milliseconds = std::chrono::duration<double,std::milli>(Clock::now()-begin).count();
    return r;
}
