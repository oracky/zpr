#include <SFML/Graphics.hpp>
#include "Camera.h"
#include "MeasurementTable.h"
#include "VehicleGraphical.h"
#include "CameraTable.h"
#include "SimulationTable.h"

/**
 * It initializes the camera's position, rotation, color, and size, and then creates a shape to
 * represent the camera
 * 
 * @param x The x position of the camera
 * @param y The y coordinate of the camera
 * @param rotation The rotation of the camera in degrees.
 * @param color The color of the camera.
 * @param size The size of the camera.
 * @param sim_info The simulation table that contains all the information about the simulation.
 */
Camera::Camera(int x, int y, int rotation, const sf::Color& color, float size, const SimulationTable& sim_info)
    : x_(x), y_(y), rotation_(rotation), color_(color), size_(size), simulation_info_(sim_info)
{
    shape_ = sf::CircleShape(size_, 3);
    shape_.setPosition(x_, y_);
    shape_.setFillColor(color_);
    shape_.rotate(rotation_);

    camera_info_ = CameraTable(x_, y_);
}

/**
 * This function returns the x coordinate of the camera.
 * 
 * @return The x coordinate of the camera.
 */
int Camera::getXCoordinate() const { return x_; }
/**
 * This function returns the y coordinate of the camera.
 * 
 * @return The y coordinate of the camera.
 */
int Camera::getYCoordinate() const { return y_; }
/**
 * This function returns the rotation of the camera.
 * 
 * @return The rotation of the camera.
 */
int Camera::getRotation() const { return rotation_; }
/**
 * This function returns the rotation of the camera.
 * 
 * @return The size of the camera.
 */
float Camera::getSize() const { return size_; }
/**
 * 
 * This function returns the color of the camera.
 * 
 * @return The color of the camera.
 */
sf::Color Camera::getColor() const { return color_; }
/**
 * 
 * This function returns the shape of the camera.
 * 
 * @return The shape of the camera.
 */
sf::CircleShape Camera::getShape() const { return shape_; }
/**
 * This function returns the camera info of the camera.
 * 
 * @return The camera_info_ variable is being returned.
 */
CameraTable Camera::getCameraInfo(){ return camera_info_; }

/**
 * If the vehicle is in the camera scope, then return a measurement table with the vehicle's
 * coordinates, otherwise return a measurement table with invalid coordinates and negative certainty.
 * 
 * @param vehicle The vehicle that is being measured.
 * 
 * @return A MeasurementTable object.
 */
MeasurementTable Camera::makeMeasurement(const VehicleGraphical& vehicle)
{
    auto bounding_box_shape = shape_.getGlobalBounds();
    auto bounding_box_vehicle = vehicle.getShape().getGlobalBounds();
    if (isInTheCameraScope(bounding_box_shape, bounding_box_vehicle))
    {
        return MeasurementTable(vehicle.getXCoordinate(), vehicle.getYCoordinate(),
                                1, vehicle.getVehicleType(), camera_info_, simulation_info_);
    }
    
    return MeasurementTable(-1, -1, -1, VehicleType::NONE, camera_info_, simulation_info_);
}


/**
 * Set the camera's x coordinate to the value of the parameter x.
 * 
 * @param x The x coordinate of the camera.
 */
void Camera::setXCoordinate(int x) { x_ = x; }
/**
 * This function sets the y coordinate of the camera.
 * 
 * @param y The y coordinate of the camera.
 */
void Camera::setYCoordinate(int y) { y_ = y; }
/**
 * Sets the rotation of the camera.
 * 
 * @param rotation The rotation of the camera in degrees.
 */
void Camera::setRotation(int rotation) { rotation_ = rotation; }
/**
 * Sets the size of the camera.
 * 
 * @param size The size of the camera.
 */
void Camera::setSize(float size) { size_ = size; }
/**
 * Sets the color of the camera.
 * 
 * @param color The color of the camera.
 */
void Camera::setColor(const sf::Color& color) { color_ = color; }


/**
 * It returns true if the bounding box of the shape intersects with the bounding box of the vehicle.
 * Basically it checks if the camera can see the vehicle.
 * 
 * @param bounding_box_shape The bounding box of the shape that we want to check if it's in the camera
 * scope.
 * @param bounding_box_vehicle The bounding box of the vehicle.
 * 
 * @return a boolean value.
 */
bool Camera::isInTheCameraScope(const sf::FloatRect& bounding_box_shape, const sf::FloatRect& bounding_box_vehicle)
{
    return bounding_box_shape.intersects(bounding_box_vehicle);
}