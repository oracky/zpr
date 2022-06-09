#include "CameraTable.h"
#include "MeasurementTable.h"
#include "Simulation.h"


/**
 * An empty constructor for the CameraTable class.
 */
CameraTable::CameraTable(){}

/**
 * `CameraTable` is a constructor that takes in four parameters and assigns them to the class variables
 * `x_`, `y_`, `visibility_`, and `precision_`.
 * 
 * @param x x coordinate of the camera
 * @param y y coordinate of the camera
 * @param visibility The distance from the camera that the robot can see
 * @param precision the precision of the camera. This is the probability that the camera will detect a
 * car.
 */
CameraTable::CameraTable(int x, int y, double visibility, double precision) 
    : x_(x), y_(y), visibility_(visibility), precision_(precision) {}

/**
 * The destructor for the CameraTable class.
 */
CameraTable::~CameraTable(){}

/**
 * It creates a string that contains the SQL query to insert a new row into the database
 * 
 * @return A string containing the query to insert a new camera into the database.
 */
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

/**
 * This function updates the id of the camera.
 * 
 * @param new_id The new ID of the camera.
 */
void CameraTable::updateID(int new_id) { id_ = new_id; }

/**
 * It returns the id_ of the CameraTable object.
 * 
 * @return The id_ variable is being returned.
 */
unsigned int CameraTable::getID() const { return id_; }

/**
 * This function returns the x coordinate of the camera.
 * 
 * @return The x coordinate of the camera.
 */
int CameraTable::getXCoordinate() const { return x_; }

/**
 * This function returns the y coordinate of the camera.
 * 
 * @return The y coordinate of the camera.
 */
int CameraTable::getYCoordinate() const { return y_; }

/**
 * It returns the visibility_ variable.
 * 
 * @return The visibility of the camera.
 */
double CameraTable::getVisibility() const { return visibility_; }

/**
 * 
 * 
 * @return The precision of the camera.
 */
double CameraTable::getPrecision() const { return precision_; }

/**
 * This function sets the x coordinate of the camera.
 * 
 * @param x The x coordinate of the camera.
 */
void CameraTable::setXCoordinate(int x) { x_ = x;}

/**
 * This function sets the y coordinate of the camera.
 * 
 * @param y The y coordinate of the camera.
 */
void CameraTable::setYCoordinate(int y) { y_ = y;}

/**
 * This function sets the visibility of the camera.
 * 
 * @param visibility The visibility of the camera.
 */
void CameraTable::setVisibility(double visibility) { visibility_ = visibility; }

/**
 * This function sets the precision of the camera table to the given value if it is valid, otherwise
 * it sets the precision to 0.
 * 
 * @param precision The precision of the camera table.
 */
void CameraTable::setPrecision(double precision) 
{ 
    precision_ = isPrecisionValid(precision) ? precision : 0;
}

/**
 * It checks if the precision is valid.
 * 
 * @param precision The precision of the camera.
 * 
 * @return true if valid otherwise false.
 */
bool CameraTable::isPrecisionValid(double precision) { return precision - 1 <= 0;}

