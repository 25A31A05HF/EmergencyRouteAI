EmergencyRoute AI — Optimized Route Planner for Emergency Vehicles
A C++17 academic prototype demonstrating graph pathfinding, an AVL Tree for hospital records, and performance comparisons for Advanced Data Structures & Algorithm Analysis.

Features
Dijkstra shortest-path algorithm using an adjacency list and min-priority queue.
Dijkstra using an adjacency matrix for comparison.
A* search using Manhattan distance on a 5x5 grid.
AVL Tree with insertion, deletion, balancing rotations, specialty search, and ID lookup.
Simulated traffic represented by higher road costs.
Benchmark output for runtime, expanded nodes, and route cost.
Handles invalid node IDs and missing hospital specialties.
Important limitations
This is a simulated academic prototype, not a live emergency-navigation product. It does not use GPS, live traffic APIs, real hospital availability, or medical triage. Road costs are illustrative. The sample specialty search ranks hospitals by route cost from node 0; adapt the starting node to the ambulance's actual position for a fuller implementation.

Requirements
C++17-compatible compiler (GCC, Clang, or MSVC)
CMake 3.16+ (optional but recommended)
Build with CMake
cmake -S . -B build
cmake --build build
Run the executable:

Windows: build\\Debug\\emergency_route_ai.exe (Visual Studio generator) or build\\emergency_route_ai.exe (other generators)
Linux/macOS: ./build/emergency_route_ai
Build with g++ directly
From the project root:

g++ -std=c++17 -O2 -Iinclude src/main.cpp src/Graph.cpp src/Dijkstra.cpp src/AStar.cpp src/AVLTree.cpp src/Benchmark.cpp -o emergency_route_ai
On Windows PowerShell, run:

.\emergency_route_ai.exe
Menu
Find route with Dijkstra
Find route with A*
Find suitable hospital by specialty
Simulate traffic congestion
Run algorithm benchmarks
Add hospital
Delete hospital by ID
Exit
Node IDs for the sample city are 0–24 in a 5x5 grid. A node ID is row * 5 + column.

Algorithm analysis
Dijkstra with adjacency list + binary heap: typically O((V+E) log V).
Dijkstra with adjacency matrix + linear minimum selection: O(V^2).
A* with a binary heap: commonly expressed as O((V+E) log V) in a graph-search implementation, though actual expansions depend strongly on the heuristic and graph.
AVL Tree search, insertion, and deletion: O(log H) where H is the number of stored hospitals (tree height remains logarithmic).
Adjacency matrix storage: O(V^2); adjacency list storage: O(V+E).
Deliverables checklist
 Build and run locally.
 Complete tests and record actual results.
 Add screenshots of route outputs and benchmark table.
 Update the report with team members, compiler details, test results, and limitations.
 Review and understand every module before viva.
