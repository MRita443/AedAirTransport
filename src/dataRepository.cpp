//
// Created by rita on 04-01-2023.
//

#include "dataRepository.h"

using namespace std;

const airlineTable &DataRepository::getAirlines() const {
    return airlines;
}

void DataRepository::setAirlines(const airlineTable &airlines) {
    DataRepository::airlines = airlines;
}

const airportTable &DataRepository::getAirports() const {
    return airports;
}

void DataRepository::setAirports(const airportTable &airports) {
    DataRepository::airports = airports;
}

const cityToAirportsMap &DataRepository::getCityToAirports() const {
    return cityToAirports;
}

void DataRepository::setCityToAirports(const cityToAirportsMap &cityToAirports) {
    DataRepository::cityToAirports = cityToAirports;
}

std::optional<Airport> DataRepository::findAirport(const string &code) {
    //TODO: Check if valid
    auto it = airports.find(Airport(code));
    std::optional<Airport> result = *it;
    //if(it != airports.end()) return *it;
    return result;
}
