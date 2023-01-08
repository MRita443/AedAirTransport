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
 * Time Complexity: TODO: TIME COMPLEXITY
 * @param src - Number of the source node
 * @param dest - Number of the destination node
 * @param airline - Pointer to an Airlines whose flight connects the two nodes (Airports)
 */
void Graph::addEdge(int src, int dest, const Airline &airline) {
    if (src < 1 || src > n || dest < 1 || dest > n) return;

    auto existingEdgeIt = std::find_if(nodes[src].adj.begin(), nodes[src].adj.end(),
                                       [dest](Edge e) { return e.dest == dest; });
    if (existingEdgeIt != nodes[src].adj.end()) {
        existingEdgeIt->airlines.insert(airline);
    }
    else nodes[src].adj.push_back({dest, airlineTable({airline})});
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
 * Builds a list with the available airlines for a flight, removing the unwanted airlines.
 * Time Complexity: O(n^2)
 * 
 * @param available - List with available airlines for the flight
 * @param avoid - List with unwanted airlines
 */
list<Airline *> avoid_airlines(list<Airline *> available, list<Airline *> avoid) {
    auto it = available.begin();
    while (it != available.end()) {
        auto curr = it;
        it++;
        if (find(avoid.begin(), avoid.end(), *curr) != avoid.end()) available.erase(curr);
    }
    return available;
}

/**
 * Finds one of the routes with several flights that has the minimum ammount of flights.
 * Time Complexity: O(V+E) //TODO verifiquem-me isto pls (como tem o avoid_airlines() a meio tbm passa a O(n^2), não?)
 * 
 * @param source - Airport where the travel begins
 * @param destination - Airport where the travel ends
 * @param avoid - List of Airlines that are to avoid
 */
list<pair<airlineTable, string>>
Graph::shortest_path_bfs(list<int> source, int destination, airlineTable validAirlines) {
    if (std::find(source.begin(), source.end(), destination) != source.end()) return {};

    for (int i = 1; i <= n; i++) {
        nodes[i].visited = false;
        nodes[i].dist = -1;
        nodes[i].predecessing_trip = {};
    }
    queue<int> q; // queue of unvisited nodes
    for (int i: source) {
        q.push(i);
        nodes[i].visited = true;
        nodes[i].dist = 0;
        nodes[i].predecessing_trip = {{{}, nodes[i].airport.getCode()}};
    }

    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front();
        q.pop();
        // show node order
        //cout << u << " ";
        for (auto e: nodes[u].adj) {
            int w = e.dest;
            if (nodes[w].airport.getCode() == "YYZ") {
                int c = 0;
            }
            airlineTable available_airlines = intersectTables(validAirlines, e.airlines);
            if (!nodes[w].visited && !available_airlines.empty()) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].dist = nodes[u].dist + 1;
                auto a = nodes[w].predecessing_trip;
                nodes[w].predecessing_trip = nodes[u].predecessing_trip;
                auto b = nodes[w].predecessing_trip;
                nodes[w].predecessing_trip.push_back({available_airlines, nodes[w].airport.getCode()});
                auto c = nodes[w].predecessing_trip;
            }
        }
    }

    return nodes[destination].predecessing_trip;
}

/*
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
 * @return Number of different cities reachable in direct flights from the given Airport
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
 * @return Number of different countries reachable in direct flights from the given Airport
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

/**
 * BFS function that visits the graph and sets the distance variable for all nodes
 * Time Complexity: O(|V| +|E|)
 * @param v - Root node of the BFS
 */
void Graph::bfsDistance(int v) {
    for (int i = 1; i <= n; i++) {
        nodes[i].visited = false;
        nodes[i].dist = -1;
    }
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    nodes[v].dist = 0;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front();
        q.pop();
        // show node order
        //cout << u << " ";
        for (auto e: nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].dist = nodes[u].dist + 1;
            }
        }
    }
}

/**
 * Computes the number of airports reachable from the given Airport in less than x flights
 * Time Complexity: O(|V| + |E|)
 * @param airport - Source Airport
 * @param numFlights - Max number of flights
 * @return Number of airports reachable from the given Airport in less or numFlights flights
 */
unsigned Graph::numAirportsInXFlights(const Airport &airport, unsigned numFlights) {
    unsigned total = 0;
    int v = airportToNode.at(airport);
    bfsDistance(v);
    for (int i = 1; i <= n; i++) {
        if (nodes[i].dist <= numFlights) total++;
    }
    return total - 1; //Excluding the airport itself
}

/**
 * Computes the number of cities reachable from the given Airport in less than x flights
 * Time Complexity: O(|V|²) (worst case) | O(|V| + |E|) (average case)
 * @param airport - Source Airport
 * @param numFlights - Max number of flights
 * @return Number of cities reachable from the given Airport in less or numFlights flights
 */
unsigned Graph::numCitiesInXFlights(const Airport &airport, unsigned numFlights) {
    cityTable currentCities;
    int v = airportToNode.at(airport);
    bfsDistance(v);
    for (int i = 1; i <= n; i++) {
        if (nodes[i].dist <= numFlights)
            currentCities.insert({nodes[i].airport.getCity(), nodes[i].airport.getCountry()});
    }
    return currentCities.size() - 1; //Excluding the airport itself
}

/**
 * Computes the number of countries reachable from the given Airport in less than x flights
 * Time Complexity: O(|V|²) (worst case) | O(|V| + |E|) (average case)
 * @param airport - Source Airport
 * @param numFlights - Max number of flights
 * @return Number of countries reachable from the given Airport in less or numFlights flights
 */
unsigned Graph::numCountriesInXFlights(const Airport &airport, unsigned numFlights) {
    unordered_set<string> currentCountries;
    int v = airportToNode.at(airport);
    bfsDistance(v);
    for (int i = 1; i <= n; i++) {
        if (nodes[i].dist <= numFlights) currentCountries.insert(nodes[i].airport.getCountry());
    }
    return currentCountries.size() - 1; //Excluding the airport itself
}

