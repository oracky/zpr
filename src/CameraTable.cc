#include "CameraTable.h"
#include "MeasurementTable.h"
#include "Simulation.h"

CameraTable::CameraTable(){}

CameraTable::CameraTable(int x, int y, double visibility, double precision) 
    : x_(x), y_(y), visibility_(visibility), precision_(precision) {}

CameraTable::~CameraTable(){}


std::string CameraTable::prepareInsertQuery() const 
{
    std::string query = "INSERT INTO Cameras (x_coordinate, y_coordinate, visibility_degree, precision) VALUES ('";
    query += std::to_string(x_);
    query += "', '";
    query += std::to_string(y_);
    query += "', '";
    query += std::to_string(visibility_);
    query += "', '";
    query += std::to_string(precision_);
    query += "')";

    return query;
}

void CameraTable::updateID(int new_id) { id_ = new_id; }

unsigned int CameraTable::getID() const { return id_; }
int CameraTable::getXCoordinate() const { return x_; }
int CameraTable::getYCoordinate() const { return y_; }
double CameraTable::getVisibility() const { return visibility_; }
double CameraTable::getPrecision() const { return precision_; }


void CameraTable::setXCoordinate(int x) { x_ = x;}
void CameraTable::setYCoordinate(int y) { y_ = y;}
void CameraTable::setVisibility(double visibility) { visibility_ = visibility; }
void CameraTable::setPrecision(double precision) 
{ 
    precision_ = isPrecisionValid(precision) ? precision : 0;
}
bool CameraTable::isPrecisionValid(double precision) { return precision - 1 <= 0;}

