# EmergencyRoute AI
## Optimized Route Planner for Emergency Vehicles

### Abstract
EmergencyRoute AI is a C++17 academic prototype that models a small road network as a weighted graph. It demonstrates Dijkstra's algorithm and A* search for pathfinding, an AVL Tree for storing hospital records, and benchmark comparisons between graph representations and pathfinding strategies. Traffic is simulated by assigning larger weights to selected roads.

### Problem statement
Emergency vehicles need efficient routes through a road network. The prototype models road travel cost and identifies a minimum-cost route through a simulated city, then helps find hospitals matching a requested specialty.

### Objectives
1. Represent road intersections and connections as a weighted graph.
2. Implement Dijkstra's algorithm using adjacency lists and adjacency matrices.
3. Implement A* search with a Manhattan-distance heuristic on a grid.
4. Implement AVL Tree insertion, deletion, search, and balancing.
5. Compare runtime, expanded nodes, and route cost using repeatable experiments.

### Methodology
The sample city is a 5x5 grid with 25 nodes. Each node represents an intersection and each edge represents a road. Edge weights represent simulated travel costs. The graph supports both adjacency-list and adjacency-matrix views. Dijkstra and A* return a route, total cost, number of expanded nodes, and elapsed time. Hospital records are keyed by ID in an AVL Tree and can be filtered by specialty.

### Complexity
- Dijkstra with adjacency list and binary min-heap: `O((V+E) log V)` in the standard implementation.
- Dijkstra with adjacency matrix and linear minimum selection: `O(V^2)`.
- A* with a binary heap: worst-case graph-search complexity can be comparable to Dijkstra; heuristic quality affects how many nodes are expanded.
- AVL search, insertion, and deletion: `O(log H)`.
- Adjacency matrix space: `O(V^2)`; adjacency list space: `O(V+E)`.

### Testing and results
Run the test plan and copy actual outputs into this section. Do not report invented performance figures. Record machine/OS, compiler version, optimization flags, graph size, edge count, and number of repeated trials. Use the same graph and start/goal for fair comparisons.

| Algorithm | Representation | Average runtime (ms) | Expanded nodes | Path cost |
|---|---|---:|---:|---:|
| Dijkstra | Adjacency list | Fill from measured run | Fill | Fill |
| Dijkstra | Adjacency matrix | Fill from measured run | Fill | Fill |
| A* | Adjacency list | Fill from measured run | Fill | Fill |

### Limitations
The application uses a fixed sample map and simulated road costs. It does not connect to GPS, real traffic, hospital capacity systems, or emergency services. It should not be used for real-world dispatch decisions.

### Future enhancements
- GUI visualization of the grid and highlighted path.
- File-driven city maps and traffic updates at runtime.
- More rigorous repeated benchmark trials and CSV export.
- Hospital search by ambulance start location and specialty.
- Optional map library or real traffic integration, subject to project time and data availability.

### Conclusion
The prototype demonstrates core graph algorithms and balanced-tree operations in a single application. Benchmark results should be added after running tests on the team's environment.
