#include "position.h"

using namespace std;

Position::Position(const float &latitude, const float &longitude) {
    this->latitude = latitude;
    this->longitude = longitude;
}

float Position::getLatitude() const {
    return latitude;
}

void Position::setLatitude(float latitude) {
    Position::latitude = latitude;
}

float Position::getLongitude() const {
    return longitude;
}

void Position::setLongitude(float longitude) {
    Position::longitude = longitude;
}
