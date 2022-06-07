#include <SFML/Graphics.hpp>
#include "Move.h"
#include "Road.h"


Road::Road(){};
Road::Road(int x, int y, float length, float width, const Move& preferedMove, int rotation_degrees)
    : x_(x), y_(y), length_(length), width_(width), prefered_move_(preferedMove), rotation_degrees_(rotation_degrees)
{
    shape_ = sf::RectangleShape(sf::Vector2f(length_, width_));
    shape_.setPosition(x_, y_);
    shape_.rotate(rotation_degrees_);
}

void Road::setPreferedMove(const Move& new_move) { prefered_move_ = new_move; }

Move Road::getOppositePreferedMove() const 
{
    return Move(static_cast<MoveType>(-prefered_move_.getHorizontal()), static_cast<MoveType>(-prefered_move_.getVertical()));
}

sf::RectangleShape Road::getShape() const { return shape_; }
Move Road::getPreferedMove() const { return prefered_move_; }
bool operator!=(const Road& road1, const Road& road2) { return road1.x_ != road2.x_ || road1.y_ != road2.y_; }