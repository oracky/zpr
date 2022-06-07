#include "MeasurementTable.h"
#include "CameraTable.h"
#include "Simulation.h"

SimulationTable::SimulationTable(){}
SimulationTable::~SimulationTable(){}

SimulationTable::SimulationTable(std::string& name) : name_(name) {}

std::string SimulationTable::prepareInsertQuery() const 
{
    std::string query = "INSERT INTO Simulations (name) VALUES ('";
    query += name_;
    query += "');";

    return query;
}

void SimulationTable::updateID(int new_id) { id_ = new_id; }

unsigned int SimulationTable::getID() const { return id_; }
std::string& SimulationTable::getName() { return name_; }

void SimulationTable::setName(std::string& name) { name_ = name; }