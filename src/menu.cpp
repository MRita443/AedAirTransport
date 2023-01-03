#include "menu.h"

using namespace std;

unsigned const Menu::COLUMN_WIDTH = 45;
unsigned const Menu::COLUMNS_PER_LINE = 3;
string const Menu::airlinesFilePath = "../dataset/airlines.csv";
string const Menu::airportsFilePath = "../dataset/airports.csv";
string const Menu::flightsFilePath = "../dataset/flights.csv";

Menu::Menu() {}

void Menu::initializeMenu() {

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
                //commandIn = flightsMenu();
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

/*
unsigned Menu::flightsMenu() {
    unsigned char commandIn;
    string menu = "hub";

    while (commandIn != 'q') {
        //Header
        cout << setw(COLUMN_WIDTH * COLUMNS_PER_LINE / 2) << setfill('-') << right << "DATA ALT";
        cout << setw(COLUMN_WIDTH * COLUMNS_PER_LINE / 2) << left << "ERATIONS" << endl;

        cout << setw(COLUMN_WIDTH) << setfill(' ') << "Alter students: [1]" << setw(COLUMN_WIDTH)
             << "Alter UCs: [2]" << setw(COLUMN_WIDTH) << "Alter Classes: [3]" << endl;
        cout << setw(COLUMN_WIDTH) << "Back: [b]" << setw(COLUMN_WIDTH) << "Quit: [q]" << endl;


        while (commandIn != 'q' && menu == "hub") {
            cout << endl << "Press the appropriate key to the function you'd like to access: ";
            cin >> commandIn;
            if (!checkInput(1)) {
                commandIn = '\0';
                continue;

            }
            switch (commandIn) {
                case '1': {
                    menu = "students";
                    break;
                }
                case '2': {
                    menu = "ucs";
                    break;
                }
                case '3': {
                    menu = "classes";
                    break;
                }
                case 'b': {
                    return '\0';
                }
                case 'q': {
                    cout << "Thank you for using LEIC Schedule Management System!" << endl;
                    break;
                }
                default:
                    cout << "Please press one of listed keys." << endl;
                    break;
            }
        }

        if (menu == "students") {
            cout << setw(COLUMN_WIDTH * COLUMNS_PER_LINE / 2) << setfill('-') << right << "STUDENT A";
            cout << setw(COLUMN_WIDTH * COLUMNS_PER_LINE / 2) << left << "LTERATIONS" << endl;

            cout << setw(COLUMN_WIDTH) << setfill(' ') << "Add a new student: [1]" << setw(COLUMN_WIDTH)
                 << "Remove a student: [2]" << setw(COLUMN_WIDTH) << "Alter a student's number: [3]" << endl;
            cout << setw(COLUMN_WIDTH) << "Alter a student's name: [4]" << setw(COLUMN_WIDTH) << endl;
            cout << setw(COLUMN_WIDTH) << "Back: [b]" << setw(COLUMN_WIDTH) << "Quit: [q]" << endl;
        }

        while (commandIn != 'q' && menu == "students") {
            cout << endl << "Press the appropriate key to the function you'd like to access: ";
            cin >> commandIn;
            if (!checkInput(1)) {
                commandIn = '\0';
                continue;

            }

            switch (commandIn) {
                case '1': {
                    unsigned studentNum;
                    string studentName;
                    cout << "Enter the number of the student you'd like to add: ";
                    cin >> studentNum;

                    if (!checkInput()) break;
                    else if (scheduler.findStudent(studentNum) != nullptr) studentAlreadyExists();
                    else {
                        cout << "Enter the name of the student you'd like to add: ";
                        cin >> studentName;
                        if (!checkInput()) break;
                        shared_ptr <Student> newStudent(new Student(studentNum, studentName));
                        scheduler.addStudent(newStudent);
                        cout << "Student successfully added." << endl;
                        CHANGES = true;
                    }
                    break;
                }
                case '2': {
                    unsigned studentNum;
                    cout << "Enter the number of the student you'd like to remove: ";
                    cin >> studentNum;
                    if (!checkInput()) break;

                    shared_ptr <Student> studentToRemove = scheduler.findStudent(studentNum);
                    if (studentToRemove == nullptr) studentDoesntExist();
                    else {
                        scheduler.removeStudent(studentToRemove);
                        cout << "Student successfully removed." << endl;
                        CHANGES = true;
                    }
                    break;
                }
                case '3': {
                    unsigned studentNum, newStudentNum;
                    cout << "Enter the number of the student you'd like to alter: ";
                    cin >> studentNum;
                    if (!checkInput()) break;

                    shared_ptr <Student> studentToAlter = scheduler.findStudent(studentNum);
                    if (studentToAlter == nullptr) studentDoesntExist();
                    else {
                        cout << "Enter the new number for this student: ";
                        cin >> newStudentNum;
                        if (!checkInput()) break;
                        else if (scheduler.findStudent(newStudentNum) != nullptr) studentAlreadyExists();
                        else {
                            scheduler.removeStudent(studentToAlter);
                            studentToAlter->setStudentCode(newStudentNum);
                            scheduler.addStudent(studentToAlter);
                            cout << "Student successfully altered." << endl;
                            CHANGES = true;LEIC Schedule Management
                        }
                    }
                    break;
                }
                case '4': {
                    unsigned studentNum;
                    string newStudentName;
                    cout << "Enter the number of the student you'd like to alter: ";
                    cin >> studentNum;
                    if (!checkInput()) break;

                    shared_ptr <Student> studentToAlter = scheduler.findStudent(studentNum);
                    if (studentToAlter == nullptr) studentDoesntExist();
                    else {
                        cout << "Enter the new name for this student: ";
                        cin >> newStudentName;
                        if (!checkInput()) break;
                        scheduler.removeStudent(studentToAlter);
                        studentToAlter->setStudentName(newStudentName);
                        scheduler.addStudent(studentToAlter);
                        cout << "Student successfully altered." << endl;
                        CHANGES = true;
                    }
                    break;
                }
                case 'b': {
                    menu = "hub";
                    break;
                }
                case 'q': {
                    cout << "Thank you for using LEIC Schedule Management System!" << endl;
                    break;
                }
                default: {
                    cout << "Please press one of listed keys." << endl;
                    break;
                }
            }
        }

    }
}

unsigned Menu::infoMenu() {

}*/


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

