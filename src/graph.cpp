#include "graph.h"

using namespace std;

// Constructor: nr nodes
Graph::Graph(int num) : n(num), nodes(num + 1) {
}

// Add edge from source to destination flown by certain airlines
void Graph::addEdge(int src, int dest, list<Airline *> airlines) {
    if (src < 1 || src > n || dest < 1 || dest > n) return;
    nodes[src].adj.push_back({dest, airlines});
}

void Graph::addEdge(int src, int dest, Airline &airline) {
    if (src < 1 || src > n || dest < 1 || dest > n) return;
    nodes[src].adj.push_back({dest, list<Airline *>({&airline})});
}

void Graph::addNode(string code, string name, string city, string country, float latitude, float longitude) {
    nodes.push_back({new Airport(code, name, city, country, latitude, longitude)});
    airportToNode[code] = ++n;
}

int Graph::getN() const {
    return n;
}

void Graph::setN(int n) {
    Graph::n = n;
}

const vector<Graph::Node> &Graph::getNodes() const {
    return nodes;
}

void Graph::setNodes(const vector<Node> &nodes) {
    Graph::nodes = nodes;
}

const unordered_map<string, int> &Graph::getAirportToNode() const {
    return airportToNode;
}

void Graph::setAirportToNode(const unordered_map<string, int> &airportToNode) {
    Graph::airportToNode = airportToNode;
}
