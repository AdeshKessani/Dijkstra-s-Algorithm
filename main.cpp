/*

Grant Henderson U35152710​
Mario Sinclair U05063284​
Adesh Kessani U69434322​
​
The aim of this project is to develop a custom undirected, 
weighted Graph Abstract Data Type (ADT) using only the <string> and <vector> standard library classes 
to efficiently represent network structures.​
Furthermore, this project aims to implement Dijkstra's Algorithm within the created Graph ADT to 
accurately compute the shortest paths between any two vertices, 
demonstrating a practical application of graph theory and greedy algorithms.​
*/
#include <iostream>
#include <vector>
#include <string>

#include "Graph.hpp"

// Define a simple structure for graph edges
struct EdgeStruct {
    std::string a;  // start vertex
    std::string b;  // end vertex
    unsigned long w; // weight
};

int main() {
    Graph g;

    // === Graph 1: Simple weighted graph ===
    std::vector<std::string> simpleVertices { "1", "2", "3", "4", "5", "6" };
    std::vector<EdgeStruct> simpleEdges {
        {"1", "2", 7}, {"1", "3", 9}, {"1", "6", 14},
        {"2", "3", 10}, {"2", "4", 15},
        {"3", "4", 11}, {"3", "6", 2},
        {"4", "5", 6}, {"5", "6", 9}
    };

    // Add vertices and edges for Graph 1
    for (const auto& label : simpleVertices) g.addVertex(label);
    for (const auto& edge : simpleEdges) g.addEdge(edge.a, edge.b, edge.w);

    std::vector<std::string> path; // reusable path vector

    std::cout << "Graph 1 (Simple Graph):\n";
    std::cout << " - Shortest distance from 1 to 5: " << g.shortestPath("1", "5", path) << "\n";
    path.clear();
    std::cout << " - Shortest distance from 3 to 6: " << g.shortestPath("3", "6", path) << "\n";
    path.clear();
    std::cout << " - Shortest distance from 5 to 2: " << g.shortestPath("5", "2", path) << "\n\n";
    path.clear();

    // === Graph 2: Campus location graph ===
    std::vector<std::string> campusVertices {
        "BSN", "LIB", "ENB", "MSC", "CAS", "SUB", "SUN"
    };
    std::vector<EdgeStruct> campusEdges {
        {"BSN", "LIB", 871}, {"BSN", "CAS", 1672}, {"BSN", "MSC", 2355},
        {"SUN", "SUB", 1265}, {"LIB", "MSC", 1615},
        {"LIB", "SUN", 1847}, {"ENB", "SUN", 2885},
        {"ENB", "CAS", 454}, {"ENB", "LIB", 1078}
    };

    // Reset graph and load campus graph
    g.clear();
    for (const auto& label : campusVertices) g.addVertex(label);
    for (const auto& edge : campusEdges) g.addEdge(edge.a, edge.b, edge.w);

    std::cout << "Graph 2 (Campus Map):\n";
    std::cout << " - Shortest distance from ENB to SUN: " << g.shortestPath("ENB", "SUN", path) << "\n";
    path.clear();
    std::cout << " - Shortest distance from LIB to CAS: " << g.shortestPath("LIB", "CAS", path) << "\n";
    path.clear();
    std::cout << " - Shortest distance from MSC to SUB: " << g.shortestPath("MSC", "SUB", path) << "\n\n";
    path.clear();

    // === Graph 3: Numbered path graph ===
    std::vector<std::string> levelGraphVertices {
        "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"
    };
    std::vector<EdgeStruct> levelGraphEdges {
        {"0", "1", 1}, {"0", "4", 1}, {"1", "2", 2}, {"1", "5", 2}, {"2", "6", 1}, {"2", "3", 1},
        {"3", "7", 2}, {"4", "8", 2}, {"5", "6", 1}, {"5", "10", 4}, {"6", "11", 2}, {"7", "12", 1},
        {"8", "9", 3}, {"9", "10", 1}, {"10", "11", 2}, {"11", "12", 5}
    };

    // Load Graph 3
    g.clear();
    for (const auto& label : levelGraphVertices) g.addVertex(label);
    for (const auto& edge : levelGraphEdges) g.addEdge(edge.a, edge.b, edge.w);

    std::cout << "Graph 3 (Numbered Grid):\n";
    std::cout << " - Shortest distance from 1 to 12: " << g.shortestPath("1", "12", path) << "\n";
    path.clear();
    std::cout << " - Shortest distance from 3 to 11: " << g.shortestPath("3", "11", path) << "\n";
    path.clear();

    // Remove vertex and test how graph adjusts
    g.removeVertex("3");
    std::cout << " - Shortest distance from 8 to 7 after removing node 3: " << g.shortestPath("8", "7", path) << "\n";
    path.clear();

    return 0;
}
