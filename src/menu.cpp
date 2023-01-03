#include "menu.h"

using namespace std;

unsigned const Menu::COLUMN_WIDTH = 45;
unsigned const Menu::COLUMNS_PER_LINE = 3;
string const Menu::airlinesFilePath = "../dataset/airlines.csv";
string const Menu::airportsFilePath = "../dataset/airports.csv";
string const Menu::flightsFilePath = "../dataset/flights.csv";

Menu::Menu() = default;

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


void Menu::mainMenu() {

    unsigned char commandIn = '\0';
    string line;

    while (commandIn != 'q') {
        if (commandIn == '\0') { //If program just started or returned from a different menu, print header

            //Header
            cout << setw(COLUMN_WIDTH * COLUMNS_PER_LINE / 2) << setfill('-') << right << "AIR TRANSPORT";
            cout << setw(COLUMN_WIDTH * COLUMNS_PER_LINE / 2) << left << " LOOKUP SYSTEM" << endl;

            cout << setw(COLUMN_WIDTH) << setfill(' ') << "Flights: [1]" << setw(COLUMN_WIDTH)
                 << "Information: [2]" << endl;
            cout << setw(COLUMN_WIDTH) << "Quit: [q]" << endl;
        }
        cout << endl << "Press the appropriate key to the function you'd like to access: ";
        cin >> commandIn;
        if (!checkInput(1)) {
            commandIn = '\0';
            continue;
        }
        switch (commandIn) {
            case '1': {
                commandIn = flightsMenu();
                break;
            }
            case '2': {
                // commandIn = infoMenu();
                break;
            }
            case 'q': {
                cout << "Thank you for using our Air Transport Lookup System!";
                break;
            }
            default: {
                cout << "Please press one of listed keys." << endl;
                break;
            }
        }
    }
}


unsigned Menu::flightsMenu() {
    unsigned char commandIn;
    list<Airport *> departure, arrival;

    while (commandIn != 'q') {
        //Header
        cout << setw(COLUMN_WIDTH * COLUMNS_PER_LINE / 2) << setfill('-') << right << "FLIG";
        cout << setw(COLUMN_WIDTH * COLUMNS_PER_LINE / 2) << left << "HTS" << endl;

        for (string currentSelection: {"departure", "arrival"}) {
            cout << setw(COLUMN_WIDTH) << setfill(' ') << "Airport: [1]" << setw(COLUMN_WIDTH)
                 << "City: [2]" << setw(COLUMN_WIDTH) << "Location: [3]" << endl;
            cout << setw(COLUMN_WIDTH) << "Back: [b]" << setw(COLUMN_WIDTH) << "Quit: [q]" << endl;

            cout << endl << "Please select how to input your " << currentSelection << " location: " << endl;
            cin >> commandIn;

            while (commandIn != 'q') {
                if (!checkInput(1)) {
                    commandIn = '\0';
                    continue;
                }
                switch (commandIn) {
                    case '1': {
                        string airportCode;
                        cout << "Please enter the code of your preferred " << currentSelection << " airport: ";
                        cin >> airportCode;
                        if (!checkInput(3)) break;

                        //TODO: Check if Airport exists
                        if (currentSelection == "departure")
                            departure = {//TODO: Get Airport by Code
                            };
                        else
                            arrival = {//TODO: Get Airport by Code
                            };
                        break;
                    }
                    case '2': {
                        string city;
                        cout << "Please enter your preferred city of " << currentSelection << ": ";
                        cin >> city;
                        if (!checkInput()) break;
                        //TODO: Check if City exists

                        string country;
                        cout << "Please enter the country this city is located in: ";
                        cin >> country;
                        if (!checkInput()) break;
                        //TODO: Check if the city exists in this country

                        if (currentSelection == "departure")
                            departure = {//TODO: Get Airport by City
                            };
                        else
                            arrival = {//TODO: Get Airport by City
                            };
                        break;
                    }
                    case '3': {
                        float latitude, longitude, maxDistance;
                        cout << "Please enter the latitude of your preferred " << currentSelection << " location: ";
                        cin >> latitude;
                        if (!checkInput()) break;

                        cout << "Please enter the longitude of your preferred " << currentSelection << " location: ";
                        cin >> longitude;
                        if (!checkInput()) break;

                        //TODO: Check if location is valid

                        cout << "Please enter the max distance of the airport to your preferred " << currentSelection
                             << " location: ";
                        cin >> maxDistance;
                        if (!checkInput()) break;

                        if (currentSelection == "departure")
                            departure = {//TODO: Get Airport by location
                            };
                        else
                            arrival = {//TODO: Get Airport by location
                            };
                        break;
                    }
                    case 'b': {
                        int a = 1;
                        return '\0';
                    }
                    case 'q': {
                        cout << "Thank you for using our Air Transport Lookup System!" << endl;
                        break;
                    }
                    default:
                        cout << "Please press one of listed keys." << endl;
                        break;
                }
            }
        }
    }
    return commandIn;
}

unsigned Menu::infoMenu() {
 return 0;
}


/**
 * Checks if the input given by the user is appropriate or not
 * Time Complexity: O(1)
 * @param checkLength - Integer indicating if the length of the input should be checked or not, and, if so, its valid max length
 * @return Returns true if the input is appropriate and false if it isn't
 */
bool Menu::checkInput(unsigned int checkLength) {

    //checkLength = 0 Don't check length
    //checkLength = 1 Check for length 1
    //checkLength = 2 Check for max length 2
    //...

    if (!cin) // User didn't input what expected
    {
        cin.clear(); // Reset failbit
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Skip bad input
        cout << "Please enter an appropriate input." << endl;
        return false;
    }

    if (checkLength > 0) {
        string line;
        getline(cin, line);
        if (line.length() > checkLength) {
            cout << "Please enter an appropriate input." << endl;
            return false;
        }
    }
    return true;
}

void Menu::initializeMenu() {
    extractFileInfo();
    //TODO: Add Menu Screens
}

