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

    // auto job1 = ParallelMeasurement();
    // job1.startThread();
    // job1.parallel();
    // auto job2 = ParallelSave();
    // job2.startThread();
    // job2.parallel();
    std::thread t1(&Simulation::measureLoop, this);
    std::thread t2(&Simulation::savingLoop, this);

     while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        updateMap();
        drawObjects(&window);

        window.display();
        // usleep(10*1000);
        
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
        vehicle.update(roads_);
    }
}

void Simulation::makeMeasurements()
{
    for (auto& camera: cameras_)
    {
        for (auto& vehicle : vehicles_)
        {
            auto measurement = camera.makeMeasurement(vehicle);
            measurement_mutex_.lock();
            measurements_.push(measurement);
            measurement_mutex_.unlock();
        }
        
    }
}

void Simulation::saveMeasurements()
{
    while(!measurements_.empty())
    {
        measurement_mutex_.lock();
        auto measurement = measurements_.front();
        measurements_.pop();
        measurement_mutex_.unlock();
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
        window->draw(vehicle.getShape());
    }

}

void Simulation::measureLoop()
{
    while (true)
    {
        makeMeasurements();

    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void Simulation::savingLoop()
{
    while (true)
    {
        saveMeasurements();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}