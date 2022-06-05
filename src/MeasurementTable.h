#ifndef MeasurementTable_H
#define MeasurementTable_H

#include "SQLTable.h"
#include "VehicleType.hpp"
#include "CameraTable.h"
#include "SimulationTable.h"


class MeasurementTable : public SQLTable
{
public:
    MeasurementTable();
    MeasurementTable(int x, int y, double certainty, VehicleType vehicle_type, CameraTable& camera, SimulationTable& simulation);
    ~MeasurementTable() = default;
    std::string prepareInsertQuery() const;
    void updateID(int new_id) override; 
    unsigned int getID() const;
    int getXCoordinate() const;
    void setXCoordinate(int x);
    int getYCoordinate() const;
    void setYCoordinate(int y);
    double getCertainty() const;
    void setCertainty(double certainty);
    VehicleType getVehicleType() const;
    void setVehicleType(VehicleType vehicle_type);
    CameraTable getCamera() const;
    void setCamera(CameraTable& camera);
    SimulationTable getSimulation() const;
    void setSimulation(SimulationTable& simulation);

private:
    unsigned int id_;
    int x_;
    int y_;
    double certainty_;
    VehicleType vehicle_type_;
    CameraTable camera_;
    SimulationTable simulation_;
};

#endif