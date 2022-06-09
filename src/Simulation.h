#ifndef Simulation_H
#define Simulation_H

#include <vector>
#include <list>
#include <queue>
#include <mutex>
#include <SFML/Graphics.hpp>
#include "Road.h"
#include "VehicleGraphical.h"
#include "SimulationTable.h"
#include "Config.h"
#include "Camera.h"
#include "SQLConnector.h"


class Simulation
{
public:
    Simulation(const Config& config);
    void run();
private:
    bool can_monitor_;
    Config config_;
    SimulationTable simulation_info_;
    sf::RenderWindow window_;
    std::vector<Road> roads_;
    std::vector<VehicleGraphical> vehicles_;
    std::vector<Camera> cameras_;
    std::queue<MeasurementTable> measurements_;
    std::queue<VehicleGraphical> inactive_vehicles_;
    std::mutex measurement_mutex_;
    std::mutex vehicles_mutex_;
    std::unique_ptr<SQLConnector> db_;


    void setRoadSystemForSimulation();
    void setVehiclesForSimulation();
    void setCamerasForSimulation();
    void updateMap();
    void makeMeasurements();
    void saveMeasurements();
    void measureLoop();
    void savingLoop();
    void drawObjects(sf::RenderWindow* window);
};

#endif