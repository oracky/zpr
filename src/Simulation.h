#ifndef Simulation_H
#define Simulation_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Road.h"
#include "VehicleGraphical.h"
#include "Config.h"


class Simulation
{
public:
    Simulation(const Config& config);
    void run();
private:
    Config config_;
    sf::RenderWindow window_;
    std::vector<Road> roads_;
    std::vector<VehicleGraphical> vehicles_;

    void setRoadSystemForSimulation();
    void setVehiclesForSimulation();
    void setCamerasForSimulation();
    void updateMap();
    void drawObjects(sf::RenderWindow* window);
};

#endif