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


void parseInputArgs(int argc, char** arv)
{

}

int main(int argc, char** argv)
{

    std::string file = "../zpr.db";
    std::string p1 = "../roads.cfg";
    std::string p2 = "../vehicles.cfg";
    std::string p3 = "../cameras.cfg";
    int refresh_rate = 500;

    // switch (argc)
    // {
    // case 1:
    //     std::cout << "Didn't provide any configuration information. Continuing with default settings" << std::endl;
    //     break;
    // case 2:
    //     std::cout << "Provided " << argv[1] << " as a path to database. Refresh rate and other configuration information is set to default." << std::endl;
    // case 3:
    //     std::cout << "Provided " << argv[1] << " as a path to database." << std::endl
    //               << "Provided " << argv[2] << " as a refresh rate for measurements and database saving. Other configuration information is set to default." << std::endl;
    // case 4:
    //     std::cout << "Provided " << argv[1] << " as a path to database." << std::endl
    //               << "Provided " << argv[2] << " as a refresh rate for measurements and database saving." << std::endl
    //               << "Provided " << argv[3] << " as a path to roads config. Other configuration information is set to default." << std::endl;
    // case 5:
    //     std::cout << "Provided " << argv[1] << " as a path to database." << std::endl
    //               << "Provided " << argv[2] << " as a refresh rate for measurements and database saving." << std::endl
    //               << "Provided " << argv[3] << " as a path to roads config. " << std::endl
    //               << "Provided " << argv[4] << " as a path to vehciles config. Other configuration information is set to default." << std::endl;
    // case 6:
    //     std::cout << "Provided " << argv[1] << " as a path to database." << std::endl
    //               << "Provided " << argv[2] << " as a refresh rate for measurements and database saving." << std::endl
    //               << "Provided " << argv[3] << " as a path to roads config."  << std::endl
    //               << "Provided " << argv[4] << " as a path to vehciles config." << std::endl
    //               << "Provided " << argv[5] << " as a path to cameras config." << std::endl;
    // default:
    //     std::cout << "Wrong usage. Try: ./Main [db_path] [refresh_rate] [roads_cfg_file] [vehicles_cfg_file] [cameras_cfg_file]." << std::endl;
    //     exit();
    // }
    
    
    // auto config = Config(file,refresh_rate, p1, p2, p3);
    auto config = Config(argc, argv);
    auto sim = Simulation(config);
    sim.run();
    return 0;
}