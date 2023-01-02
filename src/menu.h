#ifndef MENU_H
#define MENU_H

#include <string>
#include <fstream>
#include <sstream>
#include "graph.h"

class Menu
{
private:
    Graph graph = Graph(0);
    string static airlinesFilePath;
    string static airportsFilePath;
    string static flightsFilePath;

public:
    Menu();
    void extractAirlinesFile();
    void extractAirportsFile();
    void extractFlightsFile();
    void extractFileInfo();
};

#endif