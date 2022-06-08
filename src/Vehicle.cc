#include <SFML/Graphics.hpp>
#include "VehicleType.hpp"
#include "Vehicle.h"

Vehicle::Vehicle() {}
Vehicle::Vehicle(float x, float y, int speed, const VehicleType& type, const sf::Color& color)
    : x_(x), initial_x_(x), initial_y_(y),  y_(y), active_(true), respawned_(false),
      speed_(speed <= MAX_SPEED_ ? speed : MAX_SPEED_), type_(type), color_(color) {}

Vehicle::~Vehicle() {}

float Vehicle::getXCoordinate() const { return x_; }
float Vehicle::getYCoordinate() const { return y_; }
int Vehicle::getSpeed() const { return speed_; }
sf::Color Vehicle::getColor() const { return color_; }
VehicleType Vehicle::getVehicleType() const { return type_; }
bool Vehicle::isActive() const { return active_; }
bool Vehicle::wasRespawned() const { return respawned_; }

void Vehicle::setSpeed(int speed) { speed_ = speed <= MAX_SPEED_ ? speed : MAX_SPEED_; }
void Vehicle::setVehicleType(const VehicleType& type) { type_ = type;}
void Vehicle::setColor(const sf::Color& color) { color_ = color; }
void Vehicle::setRespawn() { respawned_ = true; }

void Vehicle::update(const std::vector<Road>& roads){}
