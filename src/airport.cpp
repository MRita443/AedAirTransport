#include "airport.h"

Airport::Airport(std::string const &code, std::string const &name, std::string const &city, std::string const &country,
                 float const &latitude,
                 float const &longitude) {
    this->code = code;
    this->name = name;
    this->city = city;
    this->country = country;
    location.setLatitude(latitude);
    location.setLongitude(longitude);
}
