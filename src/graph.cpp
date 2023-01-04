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
void Graph::addEdge(int src, int dest, list<Airline> connectingAirlines) {
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
void Graph::addEdge(int src, int dest, Airline airline) {
    if (src < 1 || src > n || dest < 1 || dest > n) return;
    nodes[src].adj.push_back({dest, list<Airline>({airline})});
}

/**
 * Adds a new node to the graph, creating the corresponding Airport object
 * Time Complexity: O(n) (worst case) | O(1) (average case)
 * @param code - Code of the new Airport
 * @param name - Name of the new Airport
 * @param city - City of the new Airport
 * @param country - Country of the new Airport
 * @param latitude - Latitude of the new Airport
 * @param longitude - Longitude of the new Airport
 */
void Graph::addNode(string code, string name, string city, string country, float latitude, float longitude) {
    Airport newAirport = Airport(code, name, city, country, latitude, longitude);
    nodes.push_back({newAirport});
    airportToNode[newAirport] = ++n;
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

const airportMap<string> &Graph::getAirportToNode() const {
    return airportToNode;
}

void Graph::setAirportToNode(const airportMap<string> &airportToNode) {
    Graph::airportToNode = airportToNode;
}

const airlineTable &Graph::getAirlines() const {
    return airlines;
}

void Graph::setAirlines(const airlineTable &airlines) {
    Graph::airlines = airlines;
}

/**
 * Adds a new entry to codeToAirline, creating the corresponding Airline object
 * Time Complexity: O(n) (worst case) | O(1) (average case)
 *
 * @param code - Code of the new Airline
 * @param name - Name of the new Airline
 * @param callsign - Callsign of the new Airline
 * @param country - Country of the new Airline
 */
void Graph::addAirlineEntry(string code, string name, string callsign, string country) {
    airlines.insert(Airline(code, name, callsign, country));
}

