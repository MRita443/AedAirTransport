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

/**
 * Computes the number of flights that leave from a given airport
 * Time Complexity: O(outdegree(v)), where v is the node associated with the given Airport
 * @param airport - Airport whose number of flights should be calculated
 * @return Number of flights leaving from given Airport
 */
unsigned Graph::numFlights(const Airport &airport) const {
    unsigned total = 0;
    int v = airportToNode.at(airport);
    for (const Edge &e: nodes[v].adj) {
        total += e.airlines.size();
    }
    return total;
}

/**
 * Computes the number of Airlines that carry flights leaving from a given Airport
 * Time Complexity: O(outdegree(v) * N² + N) (worst case) | O(outdegree(v) * N) (average case), where N is the number of different airlines carrying flights from the given Airport and v is the node associated with the given Airport
 * @param airport - Airport whose number of Airlines should be calculated
 * @return Number of Airlines carrying flights leaving from given Airport
 */
unsigned Graph::numAirlines(const Airport &airport) const {
    airlineTable currentAirlines;
    int v = airportToNode.at(airport);
    for (Edge e: nodes[v].adj) {
        currentAirlines.merge(e.airlines);
    }
    return currentAirlines.size();
}

/**
 * Computes the number of cities reachable in a flight from a given Airport
 * Time Complexity: O(outdegree(v) * N) (worst case) | O(outdegree(v)) (average case), where N is the number of different cities directly reachable from the given Airport and v is the node associated with the given Airport
 * @param airport - Airport whose number of destinations should be calculated
 * @return Numbers of different cities reachable in direct flights from the given Airport
 */
unsigned Graph::numDestinations(const Airport &airport) const {
    cityTable currentCities;
    int v = airportToNode.at(airport);
    for (const Edge &e: nodes[v].adj) {
        int w = e.dest;
        currentCities.insert({nodes[w].airport.getCity(), nodes[w].airport.getCountry()});
    }
    return currentCities.size();
}

/**
 * Computes the number of countries reachable in a flight from a given Airport
 * Time Complexity: O(outdegree(v) * N) (worst case) | O(outdegree(v)) (average case), where N is the number of different countries directly reachable from the given Airport and v is the node associated to the given Airport
 * @param airport - Airport whose number of destination countries should be calculated
 * @return Numbers of different countries reachable in direct flights from the given Airport
 */
unsigned Graph::numCountries(const Airport &airport) const {
    unordered_set<string> currentCountries;
    int v = airportToNode.at(airport);
    for (const Edge &e: nodes[v].adj) {
        int w = e.dest;
        currentCountries.insert(nodes[w].airport.getCountry());
    }
    return currentCountries.size();
}

/**
 * Intersects two unordered_set<Airline>
 * Time Complexity: 0(n * m) (worst case) | O(n) (average case), where n is the size of the first table and m the size of the second table
 * @param table1 - First table
 * @param table2 - Second table
 * @return Intersection between the two given airline tables
 */
airlineTable Graph::intersectTables(const airlineTable &table1, const airlineTable &table2) {
    airlineTable intersection;
    for (auto i = begin(table1); i != end(table1); i++) {
        auto table2It = table2.find(*i);
        if (table2It != end(table2)) {
            intersection.insert(*table2It);
        }
    }
    return intersection;
}



