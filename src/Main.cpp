#define DEBUG
#include <sqlite3.h>
#include <math.h> 
#include <memory>
#include <iostream>
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
        auto rc = RoadConfig(i * margin_x + initial_x, i * margin_y + initial_y, length, width, move, rotate);
        configs.push_back(rc);
    }
}

// void setConfigForVehicles()


int main(int argc, char *argv[])
{

    std::string file = "../zpr.db";

    // auto rc1 = RoadConfig(0, 125, 800.f, 20.f, Move(MoveType::RIGHT, MoveType::NONE));
    // auto rc2 = RoadConfig(135, 0, 800.f, 20.f, Move(MoveType::NONE, MoveType::DOWN), 90);
    // auto rc3 = RoadConfig(235, 0, 800.f, 20.f, Move(MoveType::NONE, MoveType::UP), 90);
    // auto rc3 = RoadConfig(335, 0, 800.f, 20.f, Move(MoveType::NONE, MoveType::UP), 90);
    // auto rc3 = RoadConfig(435, 0, 800.f, 20.f, Move(MoveType::NONE, MoveType::UP), 90);
    // auto rc3 = RoadConfig535, 0, 800.f, 20.f, Move(MoveType::NONE, MoveType::UP), 90);

    //set

    // auto vc1 = VehicleConfig(5, 35, 1, VehicleType::CAR, sf::Color::Red, 10.f);
    auto vc1 = VehicleConfig(5, 100, 3, VehicleType::CAR, sf::Color::Red, 10.f);
    auto vc2 = VehicleConfig(5, 100, 10, VehicleType::TRUCK, sf::Color::Blue, 10.f);

    auto vc3 = VehicleConfig(5, 300, 6, VehicleType::CAR, sf::Color::Red, 10.f);
    auto vc4 = VehicleConfig(5, 500, 10, VehicleType::TRUCK, sf::Color::Blue, 10.f);

    auto cc1 = CameraConfig(260, 30, 90, sf::Color(0,255,0,200), 30);

    std::vector<RoadConfig> rcv;
    setConfigsForRoads(rcv, 8, RoadDirection::HORIZONTAL, 0, 0);
    setConfigsForRoads(rcv, 2, RoadDirection::VERTICAL, 200, 0, 90, 360.0f, 20.0f, 100);
    setConfigsForRoads(rcv, 1, RoadDirection::VERTICAL, 400, 0, 90, 800.0f, 20.0f, 100);
    setConfigsForRoads(rcv, 2, RoadDirection::VERTICAL, 500, 0, 90, 360.0f, 20.0f, 100);
    setConfigsForRoads(rcv, 2, RoadDirection::VERTICAL, 200, 460, 90, 320.0f, 20.0f, 100);
    setConfigsForRoads(rcv, 2, RoadDirection::VERTICAL, 500, 460, 90, 320.0f, 20.0f, 100);
    setConfigsForRoads(rcv, 1, RoadDirection::VERTICAL, 50, 280, 90, 320.0f, 20.0f, 100);

    std::vector<VehicleConfig> vcv;
    std::vector<CameraConfig> ccv;

    // rcv.push_back(rc1);
    // rcv.push_back(rc2);
    // rcv.push_back(rc3);
    vcv.push_back(vc1);
    vcv.push_back(vc2);
    vcv.push_back(vc3);
    vcv.push_back(vc4);
    ccv.push_back(cc1);

    int refresh_rate = 1000;

    auto config = Config(file,refresh_rate,rcv,vcv,ccv);
    auto sim = Simulation(config);
    sim.run();
    return 0;
}