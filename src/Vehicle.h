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
    Vehicle(float x, float y, int speed, const VehicleType& type, const sf::Color& color);
    virtual void update(const std::vector<Road>& roads);
    float getXCoordinate() const;
    float getYCoordinate() const;
    int getSpeed() const;
    bool isActive() const;
    bool wasRespawned() const;
    void setSpeed(int speed);
    VehicleType getVehicleType() const;
    void setVehicleType(const VehicleType& type);
    sf::Color getColor() const;
    void setColor(const sf::Color& color);
    void setRespawn();
    

protected:
    static const int MAX_SPEED_ = 10;
    float x_;
    float y_;
    float initial_x_;
    float initial_y_;
    int speed_;
    bool active_;
    bool respawned_;
    VehicleType type_;
    sf::Color color_;
};



#endif