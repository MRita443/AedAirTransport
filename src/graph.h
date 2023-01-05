#ifndef GRAPH_H_
#define GRAPH_H_

#include <list>
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
#include "airline.h"
#include "airport.h"

using namespace std;

class Graph {
    struct Edge {
        int dest;   // Destination node
        list<Airline> airlines; // An integer weight
    };

    struct Node {
        Airport airport; //The Airport this node represents
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;   // As the node been visited on a search?
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    vector<Node> nodes; // The list of nodes being represented
    airportMap<string> airportToNode;
    airlineTable airlines;

public:
    // Constructor: nr nodes and direction (default: undirected)
    explicit Graph(int nodes);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, list<Airline> connectingAirlines);

    void addEdge(int src, int dest, Airline airline);

    void addNode(Airport airport);

    // Depth-First Search: example implementation
    //void dfs(int v);

    // Breadth-First Search: example implementation
    //TODO: Multi-source BFS
    void bfs(int v);

    int getN() const;

    void setN(int n);

    const vector<Node> &getNodes() const;

    void setNodes(const vector<Node> &nodes);

    const airportMap<string> &getAirportToNode() const;

    void setAirportToNode(const airportMap<string> &airportToNode);

    const airlineTable &getAirlines() const;

    void setAirlines(const airlineTable &airlines);


    // ----- Functions to implement in this class -----
    //int distance(int a, int b);
    //int diameter();
};

#endif
