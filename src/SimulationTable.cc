#include "MeasurementTable.h"
#include "CameraTable.h"
#include "Simulation.h"

/**
 * SimulationTable::SimulationTable() is a constructor for the SimulationTable class.
 */
SimulationTable::SimulationTable(){}

/**
 * The destructor for the SimulationTable class.
 */
SimulationTable::~SimulationTable(){}

/**
 * This is a constructor for the class `SimulationTable`. It takes a reference to a `std::string` as an
 * argument and assigns it to the member variable `name_`
 * 
 * @param name The name of the table.
 */
SimulationTable::SimulationTable(std::string& name) : name_(name) {}

/**
 * It creates a string that contains an SQL query that will insert a new row into the Simulations table
 * 
 * @return A string
 */
std::string SimulationTable::prepareInsertQuery() const 
{
    std::string query = "INSERT INTO Simulations (name) VALUES ('";
    query += name_;
    query += "');";

    return query;
}

/**
 * This function updates the id of the simulation table.
 * 
 * @param new_id The new ID of the simulation.
 */
void SimulationTable::updateID(int new_id) { id_ = new_id; }

/**
 * It returns the id_ of the SimulationTable object.
 * 
 * @return The id_ variable is being returned.
 */
unsigned int SimulationTable::getID() const { return id_; }

/**
 * It returns the name of simulation
 * 
 * @return The name of the simulation table.
 */
std::string& SimulationTable::getName() { return name_; }

/**
 * This function sets the name of the simulation table.
 * 
 * @param name The name of the simulation table.
 */
void SimulationTable::setName(std::string& name) { name_ = name; }