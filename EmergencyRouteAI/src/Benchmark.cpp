#include "Benchmark.h"
#include "Graph.h"
#include "Dijkstra.h"
#include "AStar.h"
#include <iostream>
#include <iomanip>

static void printResult(const char* name, const PathResult& r) {
    std::cout << std::left << std::setw(23) << name
              << std::right << std::setw(12) << std::fixed << std::setprecision(4) << r.milliseconds
              << std::setw(14) << r.expanded
              << std::setw(12);
    if (r.found()) std::cout << r.cost; else std::cout << "unreachable";
    std::cout << '\n';
}
void runBenchmarks() {
    // 10x10 grid: each adjacent road costs 1. The Manhattan heuristic is admissible.
    const int w=10, n=w*w;
    Graph g(n);
    for(int y=0;y<w;++y) for(int x=0;x<w;++x) {
        int u=y*w+x;
        if(x+1<w) g.addRoad(u,u+1,1);
        if(y+1<w) g.addRoad(u,u+w,1);
    }
    int s=0, t=n-1;
    std::cout << "\nBenchmark: 10x10 grid, start 0, destination 99\n";
    std::cout << std::left << std::setw(23) << "Algorithm"
              << std::right << std::setw(12) << "Time(ms)"
              << std::setw(14) << "Expanded"
              << std::setw(12) << "Path cost" << '\n';
    auto dl=dijkstra(g,s,t);
    auto dm=dijkstraMatrix(g,s,t);
    auto as=aStarGrid(g,s,t,w);
    printResult("Dijkstra + list",dl);
    printResult("Dijkstra + matrix",dm);
    printResult("A* + list",as);
    std::cout << "Note: timings vary by computer and run. Use repeated trials for report-quality averages.\n";
}
