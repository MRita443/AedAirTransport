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
        airlineTable airlines; // The airlines whose flights connect the two nodes
    };

    struct Node {
        Airport airport; //The Airport this node represents
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;   // As the node been visited on a search?
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    vector<Node> nodes; // The list of nodes being represented
    airportMap<int> airportToNode;
    airlineTable airlines;

public:
    // Constructor: nr nodes and direction (default: undirected)
    explicit Graph(int nodes);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, const airlineTable &connectingAirlines);

    void addEdge(int src, int dest, const Airline &airline);

    void addNode(const Airport &airport);

    // Depth-First Search: example implementation
    //void dfs(int v);

    // Breadth-First Search: example implementation
    //TODO: Multi-source BFS
    void bfs(int v);

    int getN() const;

    void setN(int n);

    const vector<Node> &getNodes() const;

    void setNodes(const vector<Node> &nodes);

    const airportMap<int> &getAirportToNode() const;

    void setAirportToNode(const airportMap<int> &airportToNode);

    const airlineTable &getAirlines() const;

    void setAirlines(const airlineTable &airlines);


    // ----- Functions to implement in this class -----
    //int distance(int a, int b);
    //int diameter();
    int findAirportNode(const string &code);
};

#endif
