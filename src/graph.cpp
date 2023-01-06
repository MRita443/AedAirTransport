#include "graph.h"
#include <map>
#include <algorithm>
using namespace std;

// Constructor: nr nodes
Graph::Graph(int num) : n(num), nodes(num + 1) {
}

/**
 * Adds an edge to the graph
 * Time Complexity: O(1)
 * @param src - Number of the source node
 * @param dest - Number of the destination node
 * @param airlines - List of pointers to the Airlines whose flights connect the two nodes (Airports)
 */
void Graph::addEdge(int src, int dest, list<Airline *> airlines) {
    if (src < 1 || src > n || dest < 1 || dest > n) return;
    nodes[src].adj.push_back({dest, airlines});
}
/**
 * Adds an edge to the graph
 * Time Complexity: O(1)
 * @param src - Number of the source node
 * @param dest - Number of the destination node
 * @param airline - Pointer to an Airlines whose flight connects the two nodes (Airports)
 */
void Graph::addEdge(int src, int dest, Airline *airline) {
    if (src < 1 || src > n || dest < 1 || dest > n) return;
    nodes[src].adj.push_back({dest, list<Airline *>({airline})});
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

const unordered_map<string, Airline *> &Graph::getCodeToAirline() const {
    return codeToAirline;
}

void Graph::setCodeToAirline(const unordered_map<string, Airline *> &codeToAirline) {
    Graph::codeToAirline = codeToAirline;
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
    codeToAirline[code] = new Airline(code, name, callsign, country);
}

/**
 * Builds a list with the available airlines for a flight, removing the unwanted airlines.
 * Time Complexity: O(n^2)
 * 
 * @param available - List with available airlines for the flight
 * @param avoid - List with unwanted airlines
 */
list<Airline *> avoid_airlines(list<Airline *> available, list<Airline *> avoid){
    auto it = available.begin();
    while (it != available.end()){
        auto curr = it;
        it++;
        if (find(avoid.begin(),avoid.end(),*curr) != avoid.end()) available.erase(curr);
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
list<pair<int,list<Airline *>>> Graph::shortest_path_bfs(vector<int> source, int destination, list<Airline *> avoid = {}){
    if (std::find(source.begin(),source.end(), destination) != source.end()) return {};

    for (int i = 1; i<=this->n; i++) nodes[i].predecessing_trip = {-1,{}};
    
    vector<int> q;
    for (int n : source){
        q.push_back(n);
        nodes[n].visited = true;
        nodes[n].predecessing_trip.first = 0; // 0 como "nulo"
    }
    
    while (!q.empty()){
        int u = q.back();
        q.pop_back();

        for (Edge e : nodes[u].adj){
            int w = e.dest;
            list<Airline *> airlines = e.airlines;
            list<Airline *> available_airlines = avoid_airlines(airlines,avoid);
            if (!nodes[w].visited && !available_airlines.empty()){  
                nodes[w].visited = true;
                nodes[w].predecessing_trip = {u,available_airlines};
                q.push_back(w);
            }
        }
        
        if (std::find(q.begin(),q.end(), destination) != q.end()) break;
    }

    if (!nodes[destination].visited) return {};

    list<pair<int,list<Airline *>>> travel;
    int current = destination;
    do{
        travel.push_front(nodes[current].predecessing_trip);
        current = nodes[current].predecessing_trip.first;
    }while (nodes[current].predecessing_trip.first != 0);

    return travel;
}