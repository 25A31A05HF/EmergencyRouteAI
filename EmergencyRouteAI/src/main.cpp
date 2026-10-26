#include "Graph.h"
#include "Dijkstra.h"
#include "AStar.h"
#include "AVLTree.h"
#include "Benchmark.h"
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <algorithm>

static Graph makeCity() {
    // 5x5 grid. Node IDs are row*5 + column; road costs simulate travel time.
    Graph g(25);
    for (int y=0; y<5; ++y) for (int x=0; x<5; ++x) {
        int u=y*5+x;
        if (x<4) g.addRoad(u,u+1, (y==2 && x==1) ? 8 : 2);
        if (y<4) g.addRoad(u,u+5, (x==3 && y==1) ? 7 : 2);
    }
    // A few alternative connections make route choices more interesting.
    g.addRoad(1,7,2.5); g.addRoad(7,13,2.5); g.addRoad(13,19,2.5);
    return g;
}
static void showPath(const PathResult& r) {
    if (!r.found()) { std::cout << "No route found.\n"; return; }
    std::cout << "Route: ";
    for (size_t i=0;i<r.path.size();++i) {
        std::cout << r.path[i] << (i+1<r.path.size() ? " -> " : "\n");
    }
    std::cout << "Travel cost: " << r.cost << "\nExpanded nodes: " << r.expanded
              << "\nRuntime (ms): " << r.milliseconds << "\n";
}
static void printHospitals(const std::vector<Hospital>& hs) {
    if(hs.empty()) { std::cout << "No hospital found for that specialty.\n"; return; }
    for(const auto& h:hs)
        std::cout << "ID " << h.id << " | " << h.name << " | " << h.specialty
                  << " | map node " << h.node << '\n';
}
int main() {
    Graph city=makeCity();
    AVLTree hospitals;
    hospitals.insert({101,"Central General Hospital","General",12});
    hospitals.insert({102,"Heart Care Centre","Cardiology",18});
    hospitals.insert({103,"City Trauma Hospital","Trauma",4});
    hospitals.insert({104,"East General Hospital","General",24});
    hospitals.insert({105,"Neuro Health Centre","Neurology",8});

    while(true) {
        std::cout << "\n=== EmergencyRoute AI ===\n"
                  << "1. Find route with Dijkstra\n"
                  << "2. Find route with A*\n"
                  << "3. Find suitable hospital by specialty\n"
                  << "4. Simulate traffic congestion\n"
                  << "5. Run algorithm benchmarks\n"
                  << "6. Add hospital\n"
                  << "7. Delete hospital by ID\n"
                  << "0. Exit\nChoice: ";
        int choice;
        if(!(std::cin>>choice)) break;
        if(choice==0) break;
        if(choice==1 || choice==2) {
            int s,t;
            std::cout << "Start node (0-24): "; std::cin>>s;
            std::cout << "Destination node (0-24): "; std::cin>>t;
            try {
                auto r = choice==1 ? dijkstra(city,s,t) : aStarGrid(city,s,t,5);
                showPath(r);
            } catch(const std::exception& e) { std::cout << "Error: " << e.what() << '\n'; }
        } else if(choice==3) {
            std::string specialty;
            std::cout << "Specialty (General/Cardiology/Trauma/Neurology): ";
            std::cin >> specialty;
            auto hs=hospitals.findSpecialty(specialty);
            if(hs.empty()) { printHospitals(hs); continue; }
            std::sort(hs.begin(),hs.end(),[&](const Hospital& a,const Hospital& b) {
                return dijkstra(city,0,a.node).cost < dijkstra(city,0,b.node).cost;
            });
            std::cout << "Reachable candidates ordered by travel cost from node 0:\n";
            printHospitals(hs);
            std::cout << "Note: this demo uses node 0 as the ambulance location.\n";
        } else if(choice==4) {
            std::cout << "Traffic simulation is built into the sample map: selected roads have higher costs.\n"
                      << "For a route test, compare node 0 to node 24 using Dijkstra and A*.\n"
                      << "To model a new incident, update the road weights in makeCity() and rebuild.\n";
        } else if(choice==5) {
            runBenchmarks();
        } else if(choice==6) {
            Hospital h;
            std::cout << "Hospital ID: "; std::cin>>h.id;
            std::cout << "Single-word hospital name: "; std::cin>>h.name;
            std::cout << "Specialty (single word): "; std::cin>>h.specialty;
            std::cout << "Map node (0-24): "; std::cin>>h.node;
            if(h.node<0 || h.node>=city.size()) std::cout << "Invalid map node.\n";
            else { hospitals.insert(h); std::cout << "Hospital saved in AVL Tree.\n"; }
        } else if(choice==7) {
            int id; std::cout << "Hospital ID to delete: "; std::cin>>id;
            std::cout << (hospitals.erase(id) ? "Hospital deleted.\n" : "Hospital ID not found.\n");
        } else {
            std::cout << "Unknown choice.\n";
        }
    }
    std::cout << "Goodbye.\n";
    return 0;
}
