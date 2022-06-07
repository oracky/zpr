#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>
#include "MeasurementTable.h"
#include "CameraTable.h"
#include "Simulation.h"
#include "VehicleType.hpp"

MeasurementTable::MeasurementTable()
{
    auto time = std::time(nullptr);
    auto local_time = *std::localtime(&time);

    std::ostringstream timestamp;
    timestamp << std::put_time(&local_time, "%d-%m-%Y %H:%M:%S");
    timestamp_ = timestamp.str();
}

MeasurementTable::MeasurementTable(int x, int y, double certainty, VehicleType vehicle_type, CameraTable& camera, SimulationTable& simulation)
    : x_(x), y_(y), certainty_(certainty), vehicle_type_(vehicle_type), camera_(camera), simulation_(simulation)
{
    auto time = std::time(nullptr);
    auto local_time = *std::localtime(&time);

    std::ostringstream timestamp;
    timestamp << std::put_time(&local_time, "%d-%m-%Y %H:%M:%S");
    timestamp_ = timestamp.str();
}

MeasurementTable::~MeasurementTable(){}

std::string MeasurementTable::prepareInsertQuery() const 
{
    auto time = std::time(nullptr);
    auto local_time = *std::localtime(&time);

    std::ostringstream timestamp;
    timestamp << std::put_time(&local_time, "%d-%m-%Y %H:%M:%S");

    std::string query = "INSERT INTO Measurements (vehicle_type, x_coordinate, y_coordinate, certainty, timestamp, camera_id, simulation_id) VALUES ('";
    query += std::to_string(static_cast<int>(vehicle_type_));
    query += "', '";
    query += std::to_string(x_);
    query += "', '";
    query += std::to_string(y_);
    query += "', '";
    query += std::to_string(certainty_);
    query += "', '";
    query += timestamp_;
    query += "', '";
    query += std::to_string(camera_.getID());
    query += "', '";
    query += std::to_string(simulation_.getID());
    query += "');";

    return query;
}

void MeasurementTable::updateID(int new_id) { id_ = new_id; }

unsigned int MeasurementTable::getID() const { return id_; }
int MeasurementTable::getXCoordinate() const { return x_; }
int MeasurementTable::getYCoordinate() const { return y_; }
double MeasurementTable::getCertainty() const { return certainty_; }
VehicleType MeasurementTable::getVehicleType() const { return vehicle_type_; }
CameraTable MeasurementTable::getCamera() const { return camera_; }
SimulationTable MeasurementTable::getSimulation() const { return simulation_; }

void MeasurementTable::setXCoordinate(int x) { x_ = x;}
void MeasurementTable::setYCoordinate(int y) { y_ = y;}
void MeasurementTable::setCertainty(double certainty) { certainty_ = certainty; }
void MeasurementTable::setVehicleType(VehicleType vehicle_type) { vehicle_type_ = vehicle_type; }
void MeasurementTable::setCamera(CameraTable& camera)
{ 
    camera_ = CameraTable(camera.getXCoordinate(), camera.getYCoordinate(), camera.getVisibility(), camera.getPrecision()); 
}
void MeasurementTable::setSimulation(SimulationTable& simulation)
{
    simulation_ = SimulationTable(simulation.getName());
}
