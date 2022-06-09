#include <SFML/Graphics.hpp>
#include "VehicleType.hpp"
#include "Vehicle.h"


/**
 * A constructor for the Vehicle class.
 */
Vehicle::Vehicle() {}

/**
 * This function initializes the vehicle's position, speed, type, and color
 * 
 * @param x The x coordinate of the vehicle.
 * @param y The y coordinate of the vehicle.
 * @param speed The speed of the vehicle.
 * @param type The type of vehicle.
 * @param color The color of the vehicle.
 */
Vehicle::Vehicle(float x, float y, int speed, const VehicleType& type, const sf::Color& color)
    : x_(x), initial_x_(x), initial_y_(y),  y_(y), active_(true), respawned_(false),
      speed_(speed <= MAX_SPEED_ ? speed : MAX_SPEED_), type_(type), color_(color) {}

/**
 * The Vehicle destructor.
 */
Vehicle::~Vehicle() {}

/**
 * This function returns the x coordinate of the vehicle.
 * 
 * @return The x coordinate of the vehicle.
 */
float Vehicle::getXCoordinate() const { return x_; }

/**
 * This function returns the y coordinate of the vehicle.
 * 
 * @return The y coordinate of the vehicle.
 */
float Vehicle::getYCoordinate() const { return y_; }

/**
 * This function returns the speed of the vehicle.
 * 
 * @return The speed of the vehicle.
 */
int Vehicle::getSpeed() const { return speed_; }

/**
 * This function returns the color of the vehicle.
 * 
 * @return The color of the vehicle.
 */
sf::Color Vehicle::getColor() const { return color_; }

/**
 * Returns the type of vehicle.
 * 
 * @return The type of vehicle.
 */
VehicleType Vehicle::getVehicleType() const { return type_; }

/**
 * This function checks if vehicle is active
 * 
 * @return true if vehicle is active (is on the map), false if not
 */
bool Vehicle::isActive() const { return active_; }

/**
 * It returns the value of the private variable respawned_.
 * 
 * @return A boolean value.
 */
bool Vehicle::wasRespawned() const { return respawned_; }

/**
 * It sets the speed of the vehicle to the speed passed in, unless the speed is greater than the max
 * speed, in which case it sets the speed to the max speed.
 * 
 * @param speed The speed of the vehicle.
 */
void Vehicle::setSpeed(int speed) { speed_ = speed <= MAX_SPEED_ ? speed : MAX_SPEED_; }

/**
 * This function sets the type of the vehicle to the type passed in as a parameter
 * 
 * @param type The type of vehicle.
 */
void Vehicle::setVehicleType(const VehicleType& type) { type_ = type;}

/**
 * Sets the color of the vehicle.
 * 
 * @param color The color of the vehicle.
 */
void Vehicle::setColor(const sf::Color& color) { color_ = color; }

/**
 * This function sets the respawned_ data member to true.
 */
void Vehicle::setRespawn() { respawned_ = true; }

/**
 * The `update` function is called every time while simulation update loop calls it and updates the vehicle's position and speed.
 * 
 * @param roads A vector of Road objects.
 */
void Vehicle::update(const std::vector<Road>& roads){}
