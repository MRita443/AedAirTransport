#include "menu.h"

using namespace std;

string Menu::airlinesFilePath = "../dataset/airlines.csv";
string Menu::airportsFilePath = "../dataset/airports.csv";
string Menu::flightsFilePath = "../dataset/flights.csv";

Menu::Menu() {
    graph = Graph(); //TODO: Switch Graph constructor
}

//Extract info from files
/**
 * Receives info from the three files and extracts it.
 */
void
Menu::extractFileInfo() {
    extractAirlinesFile();
    extractAirportsFile();
    extractFlightsFile();
}

void Menu::extractAirlinesFile() {

    ifstream airlines(airlinesFilePath);

    string currentParam, currentLine;
    string code, name, callsign, country;

    int counter = 0;

    getline(airlines, currentParam); //Ignore first line with just descriptors

    while (getline(airlines, currentLine)) {
        istringstream iss(currentLine);
        while (getline(iss, currentParam, ',')) {
            switch (counter++) {
                case 0: {
                    code = currentParam;
                    break;
                }
                case 1: {
                    name = currentParam;
                    break;
                }
                case 2: {
                    callsign = currentParam;
                    break;
                }
                case 3: {
                    country = currentParam;
                    counter = 0;
                    break;
                }
            }
            if (counter == 0) {
                //TODO: Define how airlines will be present in Graph class and connect with flights file
                graph.addNode(code, name, callsign, country);
            }
        }
    }
}

void Menu::extractAirportsFile() {
    {
        ifstream airports(airportsFilePath);

        string currentParam, currentLine;
        string code, name, city, country;
        float latitude, longitude;

        int counter = 0;

        getline(airports, currentParam); //Ignore first line with just descriptors

        while (getline(airports, currentLine)) {
            istringstream iss(currentLine);
            while (getline(iss, currentParam, ',')) {
                switch (counter++) {
                    case 0: {
                        code = currentParam;
                        break;
                    }
                    case 1: {
                        name = currentParam;
                        break;
                    }
                    case 2: {
                        city = currentParam;
                        break;
                    }
                    case 3: {
                        country = currentParam;
                        break;
                    }
                    case 4: {
                        latitude = stof(currentParam);
                        break;
                    }
                    case 5: {
                        longitude = stof(currentParam);
                        counter = 0;
                        break;
                    }
                }
                if (counter == 0) {
                    graph.addNode(code, name, city, country, latitude, longitude);
                }
            }
        }
    }
}


void Menu::extractFlightsFile() {

    ifstream flights(flightsFilePath);

    string currentParam, currentLine;
    string source, target, airlineCode;

    int counter = 0;

    getline(flights, currentParam); //Ignore first line with just descriptors

    while (getline(flights, currentLine)) {
        istringstream iss(currentLine);
        while (getline(iss, currentParam, ',')) {
            switch (counter++) {
                case 0: {
                    source = currentParam;
                    break;
                }
                case 1: {
                    target = currentParam;
                    break;
                }
                case 2: {
                    airlineCode = currentParam;
                    counter = 0;
                    break;
                }
            }
            if (counter == 0) {
                //TODO: Define how flights will be present in Graph class and connect with flights file
                graph.addEdge(code, name, callsign, country);
            }
        }
    }
}