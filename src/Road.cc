#include <SFML/Graphics.hpp>
#include <utility>
#include <functional>
#include "Move.h"
#include "Road.h"
#include <iostream>


Road::Road() : active_(false) {}
Road::Road(int x, int y, float length, float width, const Move& preferedMove, int rotation_degrees)
    : x_(x), y_(y), length_(length), width_(width), prefered_move_(preferedMove), rotation_degrees_(rotation_degrees % 360), active_(true)
{
    direction_ = ( abs(rotation_degrees_) == 90 || abs(rotation_degrees_) == 270 ) ? RoadDirection::VERTICAL : RoadDirection::HORIZONTAL;
    shape_ = sf::RectangleShape(sf::Vector2f(length_, width_));
    shape_.setPosition(x_, y_);
    // std::cout << "Width before: " <<  << "|" << shape_.getPosition().y << std::endl;
    shape_.rotate(rotation_degrees_);
    std::cout << "Width after: " << shape_.getPosition().x << "|" << shape_.getPosition().y <<  std::endl;
    // shape_.setPosition(shape_.getPosition());
}

void Road::setPreferedMove(const Move& new_move) { prefered_move_ = new_move; }

Move Road::getOppositePreferedMove() const 
{
    return Move(static_cast<MoveType>(-prefered_move_.getHorizontal()), static_cast<MoveType>(-prefered_move_.getVertical()));
}

sf::RectangleShape Road::getShape() const { return shape_; }
Move Road::getPreferedMove() const { return prefered_move_; }
bool Road::isActive() const { return active_; }
float Road::getWidth() const { return width_; }
RoadDirection Road::getDirection() const { return direction_; }


//TODO - naprawic to
int Road::alignXToCenter(int x) const
{
    if (prefered_move_.getVerticalMoveType() != MoveType::NONE)
        return x - (x_ + width_ / 4) + width_;
    return 0;
}

int Road::alignYToCenter(int y) const
{
    if (prefered_move_.getHorizontalMoveType() != MoveType::NONE)
        return y - (y_ + width_ / 4);
    return 0;
}

void Road::setDirection()
{
    if (abs(rotation_degrees_) == 90 || abs(rotation_degrees_) == 270)
        direction_ = RoadDirection::VERTICAL;
    else if (abs(rotation_degrees_) == 0 || abs(rotation_degrees_) == 180)
        direction_ = RoadDirection::HORIZONTAL;
    else
        direction_ = RoadDirection::DIAGONAL;
}

bool operator!=(const Road& road1, const Road& road2) { return road1.x_ != road2.x_ || road1.y_ != road2.y_; }