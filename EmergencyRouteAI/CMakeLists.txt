cmake_minimum_required(VERSION 3.16)
project(EmergencyRouteAI LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(emergency_route_ai
    src/main.cpp
    src/Graph.cpp
    src/Dijkstra.cpp
    src/AStar.cpp
    src/AVLTree.cpp
    src/Benchmark.cpp
)
target_include_directories(emergency_route_ai PRIVATE include)
