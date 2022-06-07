#include "Simulation.h"
#include "Config.h"
#include "Road.h"
#include <unistd.h>
#include <iostream>

Simulation::Simulation(const Config& config) : config_(config) {}

void Simulation::run() 
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    setRoadSystemForSimulation();
    setVehiclesForSimulation();
    setCamerasForSimulation();

     while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
    //     for (auto road : roads_)
    // {
    //     window.draw(road.getShape());
    // }
        // std::cout << &window << std::endl;
        updateMap();
        drawObjects(&window);

        window.display();
        usleep(10*1000);
    }

;}

void Simulation::setRoadSystemForSimulation()
{
    for (const auto& road_config : config_.getRoadsConfig())
    {
        auto road = Road(road_config.getXCoordinate(), road_config.getYCoordinate(), road_config.getLength(),
         road_config.getWidth(), road_config.getPreferedMove(), road_config.getRotation());
        roads_.push_back(road);
    }

}

void Simulation::setVehiclesForSimulation()
{
    for (const auto& vehicle_config : config_.getVehiclesConfig())
    {
        auto vehicle = VehicleGraphical(vehicle_config.getXCoordinate(), vehicle_config.getYCoordinate(), vehicle_config.getSpeed(),
         vehicle_config.getVehicleType(), vehicle_config.getColor(), vehicle_config.getSize());
        vehicles_.push_back(vehicle);
    }
}

void Simulation::setCamerasForSimulation() {}

void Simulation::updateMap()
{
    for (auto& vehicle : vehicles_)
    {
        vehicle.update(roads_);
    }
}

void Simulation::drawObjects(sf::RenderWindow* window)
{
    for (const auto& road : roads_)
    {
        window->draw(road.getShape());
    }

    for (const auto& vehicle : vehicles_)
    {
        window->draw(vehicle.getShape());
    }

}