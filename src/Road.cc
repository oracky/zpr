#include <SFML/Graphics.hpp>
#include "Move.h"
#include "Road.h"


Road::Road(){};
Road::Road(int x, int y, float length, float width, const Move& preferedMove)
    : x_(x), y_(y), length_(length), width_(width), preferedMove_(preferedMove)
{
    shape_ = sf::RectangleShape(sf::Vector2f(length_, width_));
    shape_.setPosition(x_, y_);
}

void Road::setPreferedMove(const Move& new_move) { preferedMove_ = new_move; }

Move Road::getOppositePreferedMove() const 
{
    return Move(static_cast<MoveType>(-preferedMove_.getVertical()), static_cast<MoveType>(-preferedMove_.getHorizontal()));
}

sf::RectangleShape Road::getShape() const { return shape_; }
Move Road::getPreferedMove() const { return preferedMove_; }
bool operator!=(const Road& road1, const Road& road2) { return road1.x_ != road2.x_ || road1.y_ != road2.y_; }