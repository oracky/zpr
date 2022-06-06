#ifndef Vehicle_H
#define Vehicle_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "VehicleType.hpp"
#include "Road.h"

class Vehicle
{
public:
    Vehicle();
    virtual ~Vehicle();
    Vehicle(int x, int y, int speed, const VehicleType& type, const sf::Color& color);
    virtual void update(const std::vector<Road>& roads);
    int getXCoordinate() const;
    int getYCoordinate() const;
    int getSpeed() const;
    void setSpeed(int speed);
    VehicleType getVehicleType() const;
    void setVehicleType(const VehicleType& type);
    sf::Color getColor() const;
    void setColor(const sf::Color& color);

protected:
    const int MAX_SPEED_ = 5;
    int x_;
    int y_;
    int speed_;
    VehicleType type_;
    sf::Color color_;
};



#endif