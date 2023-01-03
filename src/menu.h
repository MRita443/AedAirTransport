#ifndef MENU_H
#define MENU_H


#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include "graph.h"

class Menu {
private:
    Graph graph = Graph(0);
    string static const airlinesFilePath;
    string static const airportsFilePath;
    string static const flightsFilePath;
    unsigned static const COLUMN_WIDTH;
    unsigned static const COLUMNS_PER_LINE;

public:
    Menu();

    void initializeMenu();

    void extractAirlinesFile();

    void extractAirportsFile();

    void extractFlightsFile();

    void extractFileInfo();


    void initializeMenu();

    unsigned int flightsMenu();

    unsigned int infoMenu();

    void mainMenu();

    static bool checkInput(unsigned int checkLength = 0);
};

