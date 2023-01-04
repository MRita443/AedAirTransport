//
// Created by rita on 04-01-2023.
//

#ifndef AIRTRANSPORT_DATAREPOSITORY_H
#define AIRTRANSPORT_DATAREPOSITORY_H

#include <list>
#include <optional>
#include "airport.h"
#include "airline.h"

typedef std::unordered_map<std::pair<std::string, std::string>, std::list<Airport>> cityToAirportsMap;

class DataRepository {
private:
    airlineTable airlines;
    airportTable airports;
    cityToAirportsMap cityToAirports;
public:
    DataRepository();

    const airlineTable &getAirlines() const;

    void setAirlines(const airlineTable &airlines);

    const airportTable &getAirports() const;

    void setAirports(const airportTable &airports);

    const cityToAirportsMap &getCityToAirports() const;

    void setCityToAirports(const cityToAirportsMap &cityToAirports);

    std::optional<Airport> findAirport(const std::string& code);

    Airline findAirline(const std::string& code);

    std::list<Airport> findAirportsInCity(const std::string& city, const std::string& country);

};


#endif //AIRTRANSPORT_DATAREPOSITORY_H
