#pragma once
#include <vector>
#include <limits>
struct PathResult {
    std::vector<int> path;
    double cost = std::numeric_limits<double>::infinity();
    int expanded = 0;
    double milliseconds = 0.0;
    bool found() const { return !path.empty(); }
};
