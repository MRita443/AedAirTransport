#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

class Menu {
private:
    unsigned static const COLUMN_WIDTH;
    unsigned static const COLUMNS_PER_LINE;

public:
    Menu();

    void initializeMenu();

    unsigned int flightsMenu();

    unsigned int infoMenu();

    void mainMenu();

    static bool checkInput(unsigned int checkLength = 0);
};

#endif
