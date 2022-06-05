#define DEBUG
#include <sqlite3.h>
#include <memory>
#include <iostream>
#include <stdio.h>
#include "SQLConnector.h"
#include "SimulationTable.h"
#include "CameraTable.h"
#include "MeasurementTable.h"
#include "VehicleType.hpp"

int main(int argc, char *argv[])
{
   std::string filepath = "../zpr.db";

   auto database = std::make_unique<SQLConnector>(filepath);
   std::string name = "TEST3";
   SimulationTable simulation_table(name);
   database->insertData(simulation_table);

   CameraTable camera_table(1, 3, 0.2, 0.3);
   database->insertData(camera_table);

   MeasurementTable measurement_table(5, 6, 1.2, VehicleType::Car, camera_table, simulation_table);
   database->insertData(measurement_table);
}