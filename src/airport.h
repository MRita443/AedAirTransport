#ifndef AIRPORT_H
#define AIRPORT_H

#include <string>
#include "position.h"

class Airport {
private:
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    Position location = Position(0, 0);
public:
    Airport();
    Airport(const std::string &code, const std::string &name, const std::string &city, const std::string &country,
            const float &latitude, const float &longitude);
};

#endif