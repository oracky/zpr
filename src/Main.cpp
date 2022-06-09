#define DEBUG
#include <sqlite3.h>
#include <math.h> 
#include <memory>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include "SQLConnector.h"
#include "SimulationTable.h"
#include "CameraTable.h"
#include "MeasurementTable.h"
#include "VehicleType.hpp"
#include "Simulation.h"
#include "Road.h"

void setConfigsForRoads(std::vector<RoadConfig>& configs, int roads_number, RoadDirection direction, int initial_x, int initial_y,  int rotation=0, float length=800.0f, float width=20.f, int margin=100)
{
    auto move = direction == RoadDirection::HORIZONTAL ? Move(MoveType::RIGHT, MoveType::NONE) : Move(MoveType::NONE, MoveType::DOWN);
    auto margin_x = direction == RoadDirection::HORIZONTAL ? 0 : margin;
    auto margin_y = direction == RoadDirection::HORIZONTAL ? margin : 0;
    auto rotate = direction == RoadDirection::HORIZONTAL ? 0 : rotation;

    for (int i=1; i<=roads_number; ++i)
    {
        std::cout << i * margin_x + initial_x << " | " << i * margin_y + initial_y<< std::endl;
        auto road_config = RoadConfig(i * margin_x + initial_x, i * margin_y + initial_y, length, width, move, rotate);
        configs.push_back(road_config);
    }
}

void setConfigsForVehicles(std::vector<VehicleConfig>& v_configs, std::vector<RoadConfig>& roads, int car_number, int truck_number, int pedestrian_number)
{
    while(car_number > 0 && truck_number > 0 && pedestrian_number > 0)
    {
        for (auto& road : roads)
        {
            if ( car_number > 0)
            {
                auto vehicle_config = VehicleConfig(road.getXCoordinate(), road.getYCoordinate(), 7, VehicleType::CAR, sf::Color::Blue, 10.f);
                v_configs.push_back(vehicle_config);
                --car_number;
            }
            if ( truck_number > 0)
            {
                auto vehicle_config = VehicleConfig(road.getXCoordinate(), road.getYCoordinate(), 5, VehicleType::TRUCK, sf::Color::Black, 10.f);
                v_configs.push_back(vehicle_config);
                --truck_number;
            }
            if ( pedestrian_number > 0)
            {
                auto vehicle_config = VehicleConfig(road.getXCoordinate(), road.getYCoordinate(), 2, VehicleType::PEDESTRIAN, sf::Color::Red, 10.f);
                v_configs.push_back(vehicle_config);
                --pedestrian_number;
            }
        }

    }
    
}

// void setConfigsForCameras(std::vector<CameraConfig>& configs, int number, int initial_x, int initial_y, int margin=100, int rotation=0, float size=30.f)
// {
//     for (int i=1; i<=number; ++i)
//     {
//         // std::cout << i * margin_x + initial_x << " | " << i * margin_y + initial_y<< std::endl;
//         auto cc = CameraConfig(i * margin + initial_x, initial_y, rotation, sf::Color(0,255,0,200), size);
//         configs.push_back(cc);
//     }
// }

// TODO - wczytanie configu, windows

std::vector<std::string> getNextLineAndSplitIntoTokens(std::istream& str)
{
    std::vector<std::string>   result;
    std::string                line;
    std::getline(str,line);

    std::stringstream          lineStream(line);
    std::string                cell;

    while(std::getline(lineStream,cell, ','))
    {
        result.push_back(cell);
    }
    // This checks for a trailing comma with no data after it.
    if (!lineStream && cell.empty())
    {
        // If there was a trailing comma then add an empty element.
        result.push_back("");
    }
    return result;
}

int main(int argc, char *argv[])
{

    std::string file = "../zpr.db";


    // auto vc1 = VehicleConfig(5, 100, 3, VehicleType::CAR, sf::Color::Red, 10.f);
    // auto vc2 = VehicleConfig(5, 100, 10, VehicleType::TRUCK, sf::Color::Blue, 10.f);

    // auto vc3 = VehicleConfig(5, 300, 6, VehicleType::CAR, sf::Color::Red, 10.f);
    // auto vc4 = VehicleConfig(5, 500, 10, VehicleType::TRUCK, sf::Color::Blue, 10.f);

    // auto cc1 = CameraConfig(630, 430, 90, sf::Color(0,255,0,200), 30);
    // auto cc2 = CameraConfig(330, 230, 90, sf::Color(0,255,0,200), 30);
    // auto cc3 = CameraConfig(330, 440, 270, sf::Color(0,255,0,200), 60);
    // auto cc4 = CameraConfig(630, 90, 0, sf::Color(0,255,0,200), 15);
    // auto cc5 = CameraConfig(270, 65, 45, sf::Color(0,255,0,200), 45);
    // auto cc6 = CameraConfig(150, 235, 45, sf::Color(0,255,0,200), 45);
    // auto cc7 = CameraConfig(310, 450, 45, sf::Color(0,255,0,200), 30);
    // auto cc8 = CameraConfig(530, 530, 90, sf::Color(0,255,0,200), 30);
    // auto cc9 = CameraConfig(530, 230, 120, sf::Color(0,255,0,200), 30);
    // // auto cc2 = CameraConfig()


    // std::vector<RoadConfig> rcv;
    // setConfigsForRoads(rcv, 8, RoadDirection::HORIZONTAL, 0, 0);
    // setConfigsForRoads(rcv, 2, RoadDirection::VERTICAL, 200, 0, 90, 360.0f, 20.0f, 100);
    // setConfigsForRoads(rcv, 1, RoadDirection::VERTICAL, 400, 0, 90, 800.0f, 20.0f, 100);
    // setConfigsForRoads(rcv, 2, RoadDirection::VERTICAL, 500, 0, 90, 360.0f, 20.0f, 100);
    // setConfigsForRoads(rcv, 2, RoadDirection::VERTICAL, 200, 460, 90, 320.0f, 20.0f, 100);
    // setConfigsForRoads(rcv, 2, RoadDirection::VERTICAL, 500, 460, 90, 320.0f, 20.0f, 100);
    // setConfigsForRoads(rcv, 1, RoadDirection::VERTICAL, 50, 280, 90, 320.0f, 20.0f, 100);

    // std::vector<VehicleConfig> vcv;
    // setConfigsForVehicles(vcv, rcv, 2, 2, 5);
    // std::vector<CameraConfig> ccv;

    // ccv.push_back(cc1);
    // ccv.push_back(cc2);
    // ccv.push_back(cc3);
    // ccv.push_back(cc4);
    // ccv.push_back(cc5);
    // ccv.push_back(cc6);
    // ccv.push_back(cc7);
    // ccv.push_back(cc8);
    // ccv.push_back(cc9);

    int refresh_rate = 500;
    std::string p = "../roads.cfg";
    auto config = Config(file,refresh_rate);
    auto r = RoadConfig();
    config.readConfig(p, r);
    config.getRoadsConfig();
    // auto sim = Simulation(config);
    // sim.run();
    return 0;
}