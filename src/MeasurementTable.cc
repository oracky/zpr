#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>
#include "MeasurementTable.h"
#include "CameraTable.h"
#include "Simulation.h"
#include "VehicleType.hpp"


/**
 * It's a constructor. It creates a timestamp for the measurement table
 */
MeasurementTable::MeasurementTable()
{
    auto time = std::time(nullptr);
    auto local_time = *std::localtime(&time);

    std::ostringstream timestamp;
    timestamp << std::put_time(&local_time, "%d-%m-%Y %H:%M:%S");
    timestamp_ = timestamp.str();
}

/**
 * It's a constructor. It creates a new measurement table with the given parameters
 * 
 * @param x The x coordinate of the measurement
 * @param y The y-coordinate of the measurement.
 * @param certainty The certainty of the measurement.
 * @param vehicle_type The type of vehicle that was detected.
 * @param camera The camera that took the measurement.
 * @param simulation The simulation table that this measurement belongs to.
 */
MeasurementTable::MeasurementTable(int x, int y, double certainty, VehicleType vehicle_type, CameraTable& camera, SimulationTable& simulation)
    : x_(x), y_(y), certainty_(certainty), vehicle_type_(vehicle_type), camera_(camera), simulation_(simulation)
{
    auto time = std::time(nullptr);
    auto local_time = *std::localtime(&time);

    std::ostringstream timestamp;
    timestamp << std::put_time(&local_time, "%d-%m-%Y %H:%M:%S");
    timestamp_ = timestamp.str();
}

/**
 * The destructor for the MeasurementTable class.
 */
MeasurementTable::~MeasurementTable(){}

/**
 * It creates a string that contains a SQL query that inserts a new row into the Measurements table
 * 
 * @return A string containing the query to insert a new measurement into the database.
 */
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

/**
 * This function updates the ID of the measurement table.
 * 
 * @param new_id The new ID to be assigned to the measurement.
 */
void MeasurementTable::updateID(int new_id) { id_ = new_id; }

/**
 * It returns the id_ of the MeasurementTable object.
 * 
 * @return The id_ variable is being returned.
 */
unsigned int MeasurementTable::getID() const { return id_; }

/**
 * It returns the x coordinate of the table.
 * 
 * @return The x coordinate of the measurement.
 */
int MeasurementTable::getXCoordinate() const { return x_; }

/**
 * It returns the y coordinate of the table.
 * 
 * @return The y coordinate of the measurement.
 */
int MeasurementTable::getYCoordinate() const { return y_; }

/**
 * It returns the certainty of the measurement.
 * 
 * @return The certainty of the measurement.
 */
double MeasurementTable::getCertainty() const { return certainty_; }

/**
 * It returns the vehicle type.
 * 
 * @return The vehicle type.
 */
VehicleType MeasurementTable::getVehicleType() const { return vehicle_type_; }

/**
 * It returns the camera_ variable.
 * 
 * @return The camera_ variable is being returned.
 */
CameraTable MeasurementTable::getCamera() const { return camera_; }

/**
 * It returns SimulationTable object.
 * 
 * @return A SimulationTable object.
 */
SimulationTable MeasurementTable::getSimulation() const { return simulation_; }

/**
 * It sets the x coordinate of the measurement.
 * 
 * @param x The x coordinate of the measurement.
 */
void MeasurementTable::setXCoordinate(int x) { x_ = x;}

/**
 * This function sets the y coordinate of the measurement.
 * 
 * @param y The y coordinate of the measurement.
 */
void MeasurementTable::setYCoordinate(int y) { y_ = y;}

/**
 * It sets the certainty of the measurement.
 * 
 * @param certainty The certainty of the measurement.
 */
void MeasurementTable::setCertainty(double certainty) { certainty_ = certainty; }

/**
 * This function sets the vehicle type.
 * 
 * @param vehicle_type The type of vehicle that the measurement is for.
 */
void MeasurementTable::setVehicleType(VehicleType vehicle_type) { vehicle_type_ = vehicle_type; }

/**
 * This function sets the camera_ variable to the camera variable passed in.
 * 
 * @param camera The camera table that the measurement table is associated with.
 */
void MeasurementTable::setCamera(CameraTable& camera)
{ 
    camera_ = CameraTable(camera.getXCoordinate(), camera.getYCoordinate(), camera.getVisibility(), camera.getPrecision()); 
}

/**
 * This function sets the simulation_ variable to the simulation passed in.
 * 
 * @param simulation The name of the simulation that this measurement is associated with.
 */
void MeasurementTable::setSimulation(SimulationTable& simulation)
{
    simulation_ = SimulationTable(simulation.getName());
}
