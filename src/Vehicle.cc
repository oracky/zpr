#include <SFML/Graphics.hpp>
#include "VehicleType.hpp"
#include "Vehicle.h"

Vehicle::Vehicle() {}
Vehicle::Vehicle(int x, int y, int speed, const VehicleType& type, const sf::Color& color)
    : x_(x), y_(y), speed_(speed <= MAX_SPEED_ ? speed : MAX_SPEED_), type_(type), color_(color) {}

Vehicle::~Vehicle() {}

int Vehicle::getXCoordinate() const { return x_; }
int Vehicle::getYCoordinate() const { return y_; }
int Vehicle::getSpeed() const { return speed_; }
sf::Color Vehicle::getColor() const { return color_; }
VehicleType Vehicle::getVehicleType() const { return type_; }

void Vehicle::setSpeed(int speed) { speed_ = speed <= MAX_SPEED_ ? speed : MAX_SPEED_; }
void Vehicle::setVehicleType(const VehicleType& type) { type_ = type;}
void Vehicle::setColor(const sf::Color& color) { color_ = color; }

void Vehicle::update(const std::vector<Road>& roads){}
