#include "AStar.h"
#include <queue>
#include <chrono>
#include <algorithm>
#include <cmath>
#include <stdexcept>

PathResult aStarGrid(const Graph& g, int s, int t, int width) {
    if (s < 0 || t < 0 || s >= g.size() || t >= g.size())
        throw std::out_of_range("Start or destination node is invalid.");
    if (width <= 0) throw std::invalid_argument("Grid width must be positive.");
    auto begin = std::chrono::steady_clock::now();
    auto heuristic = [=](int node) {
        int x1 = node % width, y1 = node / width;
        int x2 = t % width, y2 = t / width;
        return static_cast<double>(std::abs(x1-x2) + std::abs(y1-y2));
    };
    const double INF = 1e100;
    std::vector<double> gScore(g.size(), INF);
    std::vector<int> prev(g.size(), -1);
    using Item = std::pair<double,int>;
    std::priority_queue<Item, std::vector<Item>, std::greater<Item>> open;
    gScore[s] = 0; open.push({heuristic(s), s});
    int expanded = 0;
    while (!open.empty()) {
        auto [f,u] = open.top(); open.pop();
        (void)f;
        if (u == t) break;
        ++expanded;
        for (const auto& e : g.neighbors(u)) {
            double tentative = gScore[u] + e.cost;
            if (tentative < gScore[e.to]) {
                gScore[e.to] = tentative; prev[e.to] = u;
                open.push({tentative + heuristic(e.to), e.to});
            }
        }
    }
    PathResult r;
    if (s == t) r.path = {s};
    else if (prev[t] != -1) {
        for (int cur=t; cur!=-1; cur=prev[cur]) r.path.push_back(cur);
        std::reverse(r.path.begin(), r.path.end());
        if (r.path.front() != s) r.path.clear();
    }
    r.cost = gScore[t]; r.expanded = expanded;
    r.milliseconds = std::chrono::duration<double,std::milli>(
        std::chrono::steady_clock::now()-begin).count();
    return r;
}
