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

#include "Graph.hpp"
using namespace std;

// Global unordered maps to store graph data
unordered_map<string, Node*> adjlist; // Adjacency list: maps vertex label to its edge list
unordered_map<string, unsigned long> m; // (Unused but declared as in original)

Graph::~Graph() { // deconstructor
    clear(); 
}

void Graph::addVertex(string label) {
    // Create a new vertex with no edges (null pointer)
    Node* edges = nullptr;
    adjlist[label] = edges;
}

void Graph::removeVertex(string label) {
    // Remove all edges pointing to the vertex
    for (auto it = adjlist.begin(); it != adjlist.end(); ++it) {
        if (it->first == label) continue;
        removeEdge(it->first, label);
    }

    // Erase the vertex itself
    adjlist.erase(label);
}

void Graph::addEdge(string label1, string label2, unsigned long weight) {
    // Exit if either vertex is not found
    if (adjlist.find(label1) == adjlist.end() || adjlist.find(label2) == adjlist.end())
        return;

    // Prevent self-loop
    if (label1 == label2) return;

    // Create and add edge from label1 to label2
    Node* p = new Node();
    p->neigb = label2;
    p->weight = weight;
    p->next = adjlist[label1];
    adjlist[label1] = p;

    // Create and add reciprocal edge for undirected graph
    Node* l = new Node();
    l->neigb = label1;
    l->weight = weight;
    l->next = adjlist[label2];
    adjlist[label2] = l;
}

void Graph::removeEdge(string label1, string label2) {
    Node* p = adjlist[label1];
    if (p == nullptr) return;

    // Remove first node if it matches label2
    if (p->neigb == label2) {
        adjlist[label1] = p->next;
        delete p;
        return;
    }

    // Otherwise traverse and remove match
    while (p->next != nullptr) {
        if (p->next->neigb == label2) {
            Node* temp = p->next;
            p->next = temp->next;
            delete temp;
            break;
        }
        p = p->next;
    }
}

// Helper function to get the unvisited node with the smallest known distance
string minStr(unordered_map<string, unsigned long> shortest, unordered_map<string, bool> visited) {
    unsigned long min = ULONG_MAX;
    string min_str;

    for (auto x : adjlist) {
        if (!visited[x.first] && shortest[x.first] <= min) {
            min = shortest[x.first];
            min_str = x.first;
        }
    }
    return min_str;
}

// Recursive function to build path from end to start using pathmap
vector<string> emp(string startLabel, string endLabel, vector<string>& path, unordered_map<string, string> pathmap) {
    if (startLabel == endLabel) return path;

    string needed = pathmap[endLabel];
    path.push_back(needed);
    return emp(startLabel, needed, path, pathmap);
}

// Clear all graph data
void Graph::clear() {
    adjlist.clear();
}

// Dijkstra's algorithm to compute shortest path and distance
unsigned long Graph::shortestPath(string startLabel, string endLabel, vector<string>& path) {
    unordered_map<string, unsigned long> shortest; // Stores shortest distances
    unordered_map<string, bool> visited;           // Tracks visited nodes
    unordered_map<string, string> pathmap;         // Stores predecessors for path reconstruction

    // Initialize distances and visited flags
    for (auto x : adjlist) {
        if (startLabel == x.first) {
            shortest[x.first] = 0;
        } else {
            shortest[x.first] = ULONG_MAX;
        }
        visited[x.first] = false;
    }

    // Perform Dijkstra’s algorithm
    for (size_t i = 0; i < adjlist.size() - 1; ++i) {
        string min_str = minStr(shortest, visited);
        visited[min_str] = true;

        Node* z = adjlist[min_str];
        while (z != nullptr) {
            if (!visited[z->neigb] &&
                shortest[min_str] != ULONG_MAX &&
                (shortest[min_str] + z->weight < shortest[z->neigb])) {

                shortest[z->neigb] = shortest[min_str] + z->weight;
                pathmap[z->neigb] = min_str;
            }
            z = z->next;
        }
    }

    // Reconstruct path
    path.push_back(endLabel);
    path = emp(startLabel, endLabel, path, pathmap);
    reverse(path.begin(), path.end());

    return shortest[endLabel];
}
