#ifndef GRAPH_H
#define GRAPH_H

#include "GraphBase.hpp"
#include <stdio.h>
#include <unordered_map>
#include <limits.h>

class Node{
    public:
    std::string neigb;
    unsigned long weight;
    Node* next;
};

class Graph:public Node{
    public:

    
    void addVertex(std::string label) ;
    void removeVertex(std::string label);
    void addEdge(std::string label1, std::string label2, unsigned long weight);
    void removeEdge(std::string label1, std::string label2);
    void clear();
    
    

    unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);
    ~Graph(); // deconstructor

};



#endif