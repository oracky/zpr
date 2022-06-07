#ifndef Config_H
#define Config_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Move.h"
#include "VehicleType.hpp"

class RoadConfig
{
public:
    RoadConfig(int x, int y, float length, float width, const Move& preferedMove, int rotation_degrees=0);
    int getXCoordinate() const;
    int getYCoordinate() const;
    int getRotation() const;
    float getLength() const;
    float getWidth() const;
    Move getPreferedMove() const;
    void setXCoordinate(int x);
    void setYCoordinate(int y);
    void setRotation(int degrees);
    void setLength(float length);
    void setWidth(float width);
    void setPreferedMove(const Move& prefered_move);
private:
    int x_;
    int y_;
    int rotation_degrees_;
    float length_;
    float width_;
    Move prefered_move_;
};

class VehicleConfig
{
public:
    VehicleConfig(int x, int y, int speed, const VehicleType& type, const sf::Color& color, float size);
    int getXCoordinate() const;
    int getYCoordinate() const;
    int getSpeed() const;
    float getSize() const;
    VehicleType getVehicleType() const;
    sf::Color getColor() const;
    void setXCoordinate(int x);
    void setYCoordinate(int y);
    void setSize(float size);
    void setSpeed(int speed);
    void setVehicleType(const VehicleType& type);
    void setColor(const sf::Color& color);
private:
    int x_;
    int y_;
    int speed_;
    float size_;
    VehicleType type_;
    sf::Color color_;
};

class Config
{
public:
    Config(int pedestrian_number, int car_number, int truck_number, int road_number,
     const std::vector<RoadConfig>& roads_config, const std::vector<VehicleConfig>& vehicle_config);
    int getPedestrianNumber() const;
    int getCarNumber() const;
    int getTruckNumber() const;
    int getRoadNumber() const;
    std::vector<RoadConfig> getRoadsConfig() const;
    std::vector<VehicleConfig> getVehiclesConfig() const;
    void setPedestrianNumber(int number);
    void setCarNumber(int number);
    void setTruckNumber(int number);
    void setRoadNumber(int number);
    void setRoadsConfig(const std::vector<RoadConfig>& roads_config);
    void setVehiclesConfig(const std::vector<VehicleConfig>& vehciles_config);

private:
    int pedestrian_number_;
    int car_number_;
    int truck_number_;
    int road_number_;
    std::vector<RoadConfig> roads_config_;
    std::vector<VehicleConfig> vehicles_config_;
};




#endif