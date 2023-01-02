#ifndef AIRLINE_H
#define AIRLINE_H

#include <string>

class Airline {
private:
    std::string code;
    std::string name;
    std::string callsign;
    std::string country;
public:
    Airline(std::string code, std::string name, std::string callsign, std::string country);
};

#endif