# Test Plan

Run these checks manually using the menu and record the outputs.

1. Route validity: Dijkstra from node 0 to node 24 returns a route and finite cost.
2. Same-node case: start 7, destination 7 returns node 7 with cost 0.
3. Invalid node: use node 25; the program should report an error.
4. Specialty lookup: search `Cardiology`; Heart Care Centre should appear.
5. Missing specialty: search `Dental`; program should report no matching hospital.
6. AVL insertion: add a hospital with a new ID and search for its specialty.
7. AVL deletion: delete hospital ID 103 and confirm it no longer appears.
8. Benchmark: run option 5 and verify Dijkstra list, Dijkstra matrix, and A* list report the same optimal path cost on the uniform 10x10 grid.
9. Disconnection test: for an extra test, temporarily remove roads around a node in `makeCity()` and confirm an unreachable destination is handled.
10. Traffic test: change a road cost in `makeCity()`, rebuild, and compare the chosen route/cost.

Record actual outputs and your compiler/environment in the report.
