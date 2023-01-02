#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <list>
#include <vector>
#include <queue>
#include <iostream>
#include "airline.h"

using namespace std;

class Graph {
    struct Edge {
        int dest;   // Destination node
        list<Airline *> airlines; // An integer weight
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;   // As the node been visited on a search?
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    vector<Node> nodes; // The list of nodes being represented

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, list<Airline> airlines);

    void addNode(string code, string name, string city, string country, float latitude, float longitude)

    // Depth-First Search: example implementation
    //void dfs(int v);

    // Breadth-First Search: example implementation
    //TODO: Multi-source BFS
    void bfs(int v);

    // ----- Functions to implement in this class -----
    //int distance(int a, int b);
    //int diameter();
};

#endif
