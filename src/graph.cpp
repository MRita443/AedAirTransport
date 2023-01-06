#include "graph.h"

using namespace std;

// Constructor: nr nodes
Graph::Graph(int num) : n(num), nodes(num + 1) {
}

/**
 * Adds an edge to the graph
 * Time Complexity: O(1)
 * @param src - Number of the source node
 * @param dest - Number of the destination node
 * @param connectingAirlines - List of Airlines whose flights connect the two nodes (Airports)
 */
void Graph::addEdge(int src, int dest, const airlineTable &connectingAirlines) {
    if (src < 1 || src > n || dest < 1 || dest > n) return;
    nodes[src].adj.push_back({dest, connectingAirlines});
}

/**
 * Adds an edge to the graph
 * Time Complexity: O(1)
 * @param src - Number of the source node
 * @param dest - Number of the destination node
 * @param airline - Pointer to an Airlines whose flight connects the two nodes (Airports)
 */
void Graph::addEdge(int src, int dest, const Airline &airline) {
    if (src < 1 || src > n || dest < 1 || dest > n) return;
    nodes[src].adj.push_back({dest, airlineTable({airline})});
}

/**
 * Adds a new node to the graph
 * Time Complexity: O(n) (worst case) | O(1) (average case)
 * @param airport - Airport the new node will represent
 */
void Graph::addNode(const Airport &airport) {
    nodes.push_back({airport});
    airportToNode[airport] = ++n;
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
/**
 * Returns the index of the node representing the airport with the given code
 * @param code - Code of the Airport whose node index should be found
 * @return Index of the node representing the given airport, or 0 if no node represents it
 */
int Graph::findAirportNode(const string &code) {
    auto it = airportToNode.find(Airport(code));
    return it != airportToNode.end() ? it->second : 0;
}

const airportMap<int> &Graph::getAirportToNode() const {
    return airportToNode;
}

void Graph::setAirportToNode(const airportMap<int> &airportToNode) {
    Graph::airportToNode = airportToNode;
}

const airlineTable &Graph::getAirlines() const {
    return airlines;
}

void Graph::setAirlines(const airlineTable &airlines) {
    Graph::airlines = airlines;
}


