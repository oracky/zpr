#ifndef VehicleGraphical_H
#define VehicleGraphical_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Vehicle.h"
#include "Road.h"


class VehicleGraphical : public Vehicle
{
public:
    VehicleGraphical();
    VehicleGraphical(int x, int y, int speed, const VehicleType& type, const sf::Color& color, float size);
    void update(const std::vector<Road>& roads) override;
    sf::RectangleShape getShape() const;
private:
    static constexpr float SPEED_TRANSLATION_ = 10.f;
    sf::RectangleShape shape_;
    Road last_road_;

    void move(const Road& road);
    bool isOnTheRoad(const sf::FloatRect& bounding_box_shape, const sf::FloatRect& bounding_box_road);
};


#endif