#include "Simulation.h"
#include "Config.h"
#include "Road.h"
#include <unistd.h>

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
    for(int i=0; i<config_.getRoadNumber(); ++i)
    {   
        auto road = Road(1*i, 2*i, 50.f*i, 20.f, Move(MoveType::RIGHT, MoveType::None));
        roads_.push_back(road);
    }

}

void Simulation::setVehiclesForSimulation()
{
    for(int i=0; i<config_.getCarNumber(); ++i)
    {   
        auto car = VehicleGraphical(1*i, 1*i, 1, VehicleType::Car, sf::Color::Red, 10.f);
        vehicles_.push_back(car);
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