#include <SFML/Graphics.hpp>
#include "Camera.h"
#include "MeasurementTable.h"
#include "VehicleGraphical.h"

Camera::Camera(int x, int y, int rotation, const sf::Color& color, float size)
    : x_(x), y_(y), rotation_(rotation), color_(color), size_(size) 
{
    shape_ = sf::CircleShape(size_, 3);
    shape_.setPosition(x_, y_);
    shape_.setFillColor(color_);
    shape_.rotate(rotation_);
}

int Camera::getXCoordinate() const { return x_; }
int Camera::getYCoordinate() const { return y_; }
int Camera::getRotation() const { return rotation_; }
float Camera::getSize() const { return size_; }
sf::Color Camera::getColor() const { return color_; }
sf::CircleShape Camera::getShape() const { return shape_; }

MeasurementTable Camera::makeMeasurement(const std::vector<VehicleGraphical>& vehicles) const
{
    //TODO
}


void Camera::setXCoordinate(int x) { x_ = x; }
void Camera::setYCoordinate(int y) { y_ = y; }
void Camera::setRotation(int rotation) { rotation_ = rotation; }
void Camera::setSize(float size) { size_ = size; }
void Camera::setColor(const sf::Color& color) { color_ = color; }