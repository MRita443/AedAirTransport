//
// Created by rita on 04-01-2023.
//

#include "dataRepository.h"

using namespace std;

DataRepository::DataRepository() = default;

const airlineTable &DataRepository::getAirlines() const {
    return airlines;
}

void DataRepository::setAirlines(const airlineTable &airlines) {
    DataRepository::airlines = airlines;
}

/**
 * Adds a new entry to the unordered_set of Airlines, creating the corresponding Airline object
 * Time Complexity: O(n) (worst case) | O(1) (average case)
 *
 * @param code - Code of the new Airline
 * @param name - Name of the new Airline
 * @param callsign - Callsign of the new Airline
 * @param country - Country of the new Airline
 * @return Created Airline object
 */
Airline DataRepository::addAirlineEntry(string code, string name, string callsign, string country) {
    Airline newAirline = Airline(code, name, callsign, country);
    airlines.insert(newAirline);
    return newAirline;
}

const airportTable &DataRepository::getAirports() const {
    return airports;
}

void DataRepository::setAirports(const airportTable &airports) {
    DataRepository::airports = airports;
}

/**
 * Adds a new entry to the unordered_set of Airports, creating the corresponding Airport object
 * Time Complexity: O(n) (worst case) | O(1) (average case)
 *
 * @param code - Code of the new Airport
 * @param name - Name of the new Airport
 * @param city - City of the new Airport
 * @param country - Country of the new Airport
 * @param latitude - Latitude of the new Airport
 * @param longitude - Longitude of the new Airport
 * @return Created Airport object
 */
Airport DataRepository::addAirportEntry(string code, string name, string city, string country, float latitude,
                                        float longitude) {
    Airport newAirport = Airport(code, name, city, country, latitude, longitude);
    airports.insert(newAirport);
    return newAirport;
}

/**
 * Adds a new Airport value to an entry in the unordered_map of (city, country) pairs
 * Time Complexity: O(n) (worst case) | O(1) (average case)
 *
 * @param city - City of the new Airport
 * @param country - Country of the new Airport
 * @param airport - Airport to add
 */
void DataRepository::addAirportToCityEntry(const string& city, const string& country, const Airport& airport) {
    list<Airport> currList = cityToAirports[{city, country}];
    currList.push_back(airport);
    cityToAirports.insert_or_assign({city, country}, currList);
}

const cityToAirportsMap &DataRepository::getCityToAirports() const {
    return cityToAirports;
}

void DataRepository::setCityToAirports(const cityToAirportsMap &cityToAirports) {
    DataRepository::cityToAirports = cityToAirports;
}

std::optional<Airport> DataRepository::findAirport(const string &code) {
    std::optional<Airport> result;
    auto it = airports.find(Airport(code));
    if (it != airports.end()) result = *it;
    return result;
}

std::optional<Airline> DataRepository::findAirline(const string &code) {
    std::optional<Airline> result;
    auto it = airlines.find(Airline(code));
    if (it != airlines.end()) result = *it;
    return result;
}

list<Airport> DataRepository::findAirportsInCity(const std::string &city, const std::string &country) {
    return cityToAirports.at({city, country});
}

bool DataRepository::checkValidCityCountry(const std::string &city, const std::string &country){
    return cityToAirports.find({city, country}) != cityToAirports.end();
}


