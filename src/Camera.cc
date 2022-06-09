#include <SFML/Graphics.hpp>
#include "Camera.h"
#include "MeasurementTable.h"
#include "VehicleGraphical.h"
#include "CameraTable.h"
#include "SimulationTable.h"

Camera::Camera(int x, int y, int rotation, const sf::Color& color, float size, const SimulationTable& sim_info)
    : x_(x), y_(y), rotation_(rotation), color_(color), size_(size), simulation_info_(sim_info)
{
    shape_ = sf::CircleShape(size_, 3);
    shape_.setPosition(x_, y_);
    shape_.setFillColor(color_);
    shape_.rotate(rotation_);

    camera_info_ = CameraTable(x_, y_);
}

int Camera::getXCoordinate() const { return x_; }
int Camera::getYCoordinate() const { return y_; }
int Camera::getRotation() const { return rotation_; }
float Camera::getSize() const { return size_; }
sf::Color Camera::getColor() const { return color_; }
sf::CircleShape Camera::getShape() const { return shape_; }
CameraTable Camera::getCameraInfo(){ return camera_info_; }

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


void Camera::setXCoordinate(int x) { x_ = x; }
void Camera::setYCoordinate(int y) { y_ = y; }
void Camera::setRotation(int rotation) { rotation_ = rotation; }
void Camera::setSize(float size) { size_ = size; }
void Camera::setColor(const sf::Color& color) { color_ = color; }

bool Camera::isInTheCameraScope(const sf::FloatRect& bounding_box_shape, const sf::FloatRect& bounding_box_road)
{
    return bounding_box_shape.intersects(bounding_box_road);
}