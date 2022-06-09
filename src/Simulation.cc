#include "Simulation.h"
#include "Config.h"
#include "Road.h"
#include "Camera.h"
#include "SQLConnector.h"
#include "SimulationTable.h"
// #include "ParallelJob.h"
#include <thread>
#include <unistd.h>
#include <iostream>
#include <chrono>

Simulation::Simulation(const Config& config) : config_(config)
{
    std::string name = "Simulation";
    simulation_info_ = SimulationTable(name);
    db_ = std::make_unique<SQLConnector>(config_.getDatabaseFilePath());
    db_->insertData(simulation_info_);
}

void Simulation::run() 
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    setRoadSystemForSimulation();
    setVehiclesForSimulation();
    setCamerasForSimulation();


    can_monitor_ = true;
    std::thread t1(&Simulation::measureLoop, this);
    std::thread t2(&Simulation::savingLoop, this);

     while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                can_monitor_ = false;
            }
                
        }

        window.clear(sf::Color::Black);
        updateMap();
        drawObjects(&window);
        window.display();
    }

    t1.join();
    t2.join();
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

void Simulation::setCamerasForSimulation()
{
    for (const auto& cameras_config : config_.getCamerasConfig())
    {
        auto camera = Camera(cameras_config.getXCoordinate(), cameras_config.getYCoordinate(), cameras_config.getRotation(),
                        cameras_config.getColor(), cameras_config.getSize(), simulation_info_);
        cameras_.push_back(camera);
        CameraTable info = camera.getCameraInfo();
        db_->insertData(info);
    }
}

void Simulation::updateMap()
{
    for (auto& vehicle : vehicles_)
    {
        if(vehicle.isActive())
            vehicle.update(roads_);
        else
            vehicle = vehicle.spawnClone();
    }
}

void Simulation::makeMeasurements()
{
    for (auto& camera: cameras_)
    {
        for (auto& vehicle : vehicles_)
        {
            auto measurement = camera.makeMeasurement(vehicle);
            if (measurement.getCertainty() != -1)
            {
                std::lock_guard<std::mutex> lock(measurement_mutex_);
                measurements_.push(measurement);
            }
            
        }
        
    }
}


void Simulation::saveMeasurements()
{
    while(!measurements_.empty())
    {
        std::lock_guard<std::mutex> lock(measurement_mutex_);
        auto measurement = measurements_.front();
        measurements_.pop();
        db_->insertData(measurement);
    }
}

void Simulation::drawObjects(sf::RenderWindow* window)
{
    for (const auto& road : roads_)
    {
        window->draw(road.getShape());
    }

    for (const auto& camera : cameras_)
    {
        window->draw(camera.getShape());
    }

    for (const auto& vehicle : vehicles_)
    {
        if(vehicle.isActive())
            window->draw(vehicle.getShape());
    }

}

void Simulation::measureLoop()
{
    while (can_monitor_)
    {
        makeMeasurements();
        std::this_thread::sleep_for(std::chrono::milliseconds(config_.getRefreshRate()));
    }
    
}

void Simulation::savingLoop()
{
    while (can_monitor_)
    {
        saveMeasurements();
        std::this_thread::sleep_for(std::chrono::milliseconds(config_.getRefreshRate()));
    }
    
}
