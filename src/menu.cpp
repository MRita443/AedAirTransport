#include "menu.h"

using namespace std;

string Menu::airlinesFilePath = "../dataset/airlines.csv";
string Menu::airportsFilePath = "../dataset/airports.csv";
string Menu::flightsFilePath = "../dataset/flights.csv";

Menu::Menu() {}

//Extract info from files
/**
 * Delegates extracting file info, calling the appropriate functions for each file
 */
void
Menu::extractFileInfo() {
    extractAirlinesFile();
    extractAirportsFile();
    extractFlightsFile();
}
/**
 * Extracts and stores the information of airlines.csv
 * Time Complexity: O(n²) (worst case) | 0(1) (average case), where n is the number of lines of airlines.csv
 */
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
                graph.addAirlineEntry(code, name, callsign, country);
            }
        }
    }
}
/**
 * Extracts and stores the information of airports.csv
 * Time Complexity: O(n²) (worst case) | 0(1) (average case), where n is the number of lines of airports.csv
 */
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

/**
 * Extracts and stores the information of flights.csv
 * Time Complexity: O(n), where n is the number of lines of flights.csv
 */
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
                graph.addEdge(graph.getAirportToNode().at(source),
                              graph.getAirportToNode().at(target), graph.getCodeToAirline().at(airlineCode));
            }
        }
    }
}

void Menu::initializeMenu() {
    extractFileInfo();
    //TODO: Add Menu Screens
}


