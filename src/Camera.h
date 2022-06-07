#ifndef Camera_H
#define Camera_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "MeasurementTable.h"
#include "CameraTable.h"
#include "SimulationTable.h"
#include "VehicleGraphical.h"


class Camera
{
public:
    Camera();
    Camera(int x, int y, int roatation, const sf::Color& color, float size, const SimulationTable& sim_info);
    int getXCoordinate() const;
    int getYCoordinate() const;
    int getRotation() const;
    float getSize() const;
    sf::Color getColor() const;
    sf::CircleShape getShape() const;
    CameraTable getCameraInfo();
    MeasurementTable makeMeasurement(const VehicleGraphical& vehicle);
    void setXCoordinate(int x);
    void setYCoordinate(int y);
    void setRotation(int rotation);
    void setSize(float size);
    void setColor(const sf::Color& color);
private:
    int x_;
    int y_;
    int rotation_;
    float size_;
    sf::Color color_;
    sf::CircleShape shape_;
    CameraTable camera_info_;
    SimulationTable simulation_info_;

    bool isInTheCameraScope(const sf::FloatRect& bounding_box_shape, const sf::FloatRect& bounding_box_road);
};


#endif