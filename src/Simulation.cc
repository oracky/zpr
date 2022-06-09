#include <thread>
#include <chrono>
#include "Simulation.h"
#include "Config.h"
#include "Road.h"
#include "Camera.h"
#include "SQLConnector.h"
#include "SimulationTable.h"


/**
 * The constructor for the Simulation class takes a Config object as an argument and uses it to
 * initialize the simulation_info_ member variable and the db_ member variable
 * 
 * @param config The configuration object that contains the parameters for the simulation.
 */
Simulation::Simulation(const Config& config) : config_(config)
{
    std::string name = "Simulation";
    simulation_info_ = SimulationTable(name);
    db_ = std::make_unique<SQLConnector>(config_.getDatabaseFilePath());
    db_->insertData(simulation_info_);
}

/**
 * The function `run()` is the main function of the simulation. It creates a window, sets up the
 * simulation, and then runs the simulation
 */
void Simulation::run() 
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);

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

/**
 * This function takes the road configuration from the config file and creates a road object for each
 * road
 */
void Simulation::setRoadSystemForSimulation()
{
    for (const auto& road_config : config_.getRoadsConfig())
    {
        auto road = Road(road_config.getXCoordinate(), road_config.getYCoordinate(), road_config.getLength(),
                        road_config.getWidth(), road_config.getPreferedMove(), road_config.getRotation());
        roads_.push_back(road);
    }

}

/**
 * It takes the vehicle configuration from the configuration file and creates a vehicle object for each
 * vehicle
 */
void Simulation::setVehiclesForSimulation()
{
    for (const auto& vehicle_config : config_.getVehiclesConfig())
    {
        auto vehicle = VehicleGraphical(vehicle_config.getXCoordinate(), vehicle_config.getYCoordinate(), vehicle_config.getSpeed(),
                        vehicle_config.getVehicleType(), vehicle_config.getColor(), vehicle_config.getSize());
        vehicles_.push_back(vehicle);
    }
}

/**
 * It creates a camera object for each camera in the configuration file and stores it in a vector. The information about the camera is stored in the database.
 */
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

/**
 * It updates the map on every iteration of main loop in Simulation::run function.
 * It checks if the vehicle is active (is on any road), if yes update vehicle status else spawn it in the initial location. 
 */
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

/**
 * It creates measurements for each camera and put them into measurements queue.
 */
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

/**
 * > This function takes the measurements from the queue and inserts them into the database
 */
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

/**
 * It draws all the objects in the simulation
 * 
 * @param window The window to draw the objects to.
 */
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

/**
 * The function `measureLoop()` is a loop that runs in a separate thread and makes measurements of the
 * vehicles at a rate specified by the config.
 */
void Simulation::measureLoop()
{
    while (can_monitor_)
    {
        makeMeasurements();
        std::this_thread::sleep_for(std::chrono::milliseconds(config_.getRefreshRate()));
    }
    
}

/**
 The function `savingLoop()` is a loop that runs in a separate thread and saves taken measurements.
 */
void Simulation::savingLoop()
{
    while (can_monitor_)
    {
        saveMeasurements();
        std::this_thread::sleep_for(std::chrono::milliseconds(config_.getRefreshRate()));
    } 
}
