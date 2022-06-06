#include "Vehicle.h"
#include "VehicleGraphical.h"
#include "Move.h"
#include <iostream>

VehicleGraphical::VehicleGraphical() {}
VehicleGraphical::VehicleGraphical(int x, int y, int speed, const VehicleType& type, const sf::Color& color, float size)
    : Vehicle(x, y, speed, type, color)
{
    shape_ = sf::RectangleShape(sf::Vector2f(size, size));
    shape_.setPosition(x_, y_);
    shape_.setFillColor(color_);
}

void VehicleGraphical::update(const std::vector<Road>& roads)
{
    bool can_move = false;
    auto bounding_box_shape = shape_.getGlobalBounds();

    if (isOnTheRoad(bounding_box_shape, last_road_.getShape().getGlobalBounds()))
    {
        move(last_road_);
        return;
    }

    for (auto road : roads)
    {
        auto bounding_box_road = road.getShape().getGlobalBounds();

        if (road != last_road_ && isOnTheRoad(bounding_box_shape, bounding_box_road))
        {
            move(road);
            can_move = true;
            break;
        }
    }

    if (!can_move)
    {
        last_road_.setPreferedMove(last_road_.getOppositePreferedMove());
        move(last_road_);
    }
}

sf::RectangleShape VehicleGraphical::getShape() const { return shape_; }

bool VehicleGraphical::isOnTheRoad(const sf::FloatRect& bounding_box_shape, const sf::FloatRect& bounding_box_road)
{
    return bounding_box_shape.intersects(bounding_box_road);
}

void VehicleGraphical::move(const Road& road)
{
    auto prefered_move = road.getPreferedMove();
    shape_.move(prefered_move.getVertical() * speed_, prefered_move.getHorizontal() * speed_);
    last_road_ = road;
}