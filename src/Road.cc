#include <SFML/Graphics.hpp>
#include <utility>
#include <functional>
#include "Move.h"
#include "Road.h"


/**
 * The constructor for the Road class. It sets the active_ variable to false.
 */
Road::Road() : active_(false) {}

/**
 * The function takes in the x and y coordinates of the road, the length and width of the road, the
 * prefered move of the road, and the rotation of the road. It then sets the direction of the road, the
 * shape of the road, and the position of the road
 * 
 * @param x x coordinate of the road
 * @param y y coordinate of the road
 * @param length The length of the road
 * @param width the width of the road
 * @param preferedMove The direction the road wants the car to move in.
 * @param rotation_degrees The angle of rotation of the road.
 */

Road::Road(int x, int y, float length, float width, const Move& preferedMove, int rotation_degrees)
    : x_(x), y_(y), length_(length), width_(width), prefered_move_(preferedMove), rotation_degrees_(rotation_degrees % 360), active_(true)
{
    direction_ = ( abs(rotation_degrees_) == 90 || abs(rotation_degrees_) == 270 ) ? RoadDirection::VERTICAL : RoadDirection::HORIZONTAL;
    shape_ = sf::RectangleShape(sf::Vector2f(length_, width_));
    shape_.setPosition(x_, y_);
    shape_.rotate(rotation_degrees_);
}

/** 
 * This function takes in a `Move` object and sets the `prefered_move_` variable to the `new_move`
 * variable
 * 
 * @param new_move The new move to set as the prefered move.
 */
void Road::setPreferedMove(const Move& new_move) { prefered_move_ = new_move; }

/**
 * It returns the opposite of the prefered move
 * 
 * @return The opposite of the prefered move.
 */
Move Road::getOppositePreferedMove() const 
{
    return Move(static_cast<MoveType>(-prefered_move_.getHorizontal()), static_cast<MoveType>(-prefered_move_.getVertical()));
}

/**
 * The function `getShape` returns the shape of the road.
 * 
 * @return The shape of the road.
 */
sf::RectangleShape Road::getShape() const { return shape_; }

/**
 * The function `getPreferedMove` returns the prefered move of the road
 * 
 * @return The prefered move of the road.
 */
Move Road::getPreferedMove() const { return prefered_move_; }

/**
 * The function `isActive` checks if the road is active
 * 
 * @return The value of the active_ variable.
 */
bool Road::isActive() const { return active_; }

/**
 * Get the width of the road.
 * 
 * @return The width of the road.
 */
float Road::getWidth() const { return width_; }

/**
 * Returns the direction of the road.
 * 
 * @return The direction of the road.
 */
RoadDirection Road::getDirection() const { return direction_; }

/**
 * It returns the difference between the given x coordinate and the center of the road, if the road is
 * vertical
 * 
 * @param x the x coordinate of the car
 * 
 * @return The difference between the x coordinate of the road and the x coordinate of the car.
 */
int Road::alignXToCenter(int x) const
{
    if (prefered_move_.getVerticalMoveType() != MoveType::NONE)
        return x - (x_ + width_ / 4) + width_;
    return 0;
}

/**
 * It returns the difference between the y coordinate of the car and the y coordinate of the road, if
 * the car is moving horizontally
 * 
 * @param y the y coordinate of the car
 * 
 * @return The difference between the y coordinate of the road and the y coordinate of the car.
 */
int Road::alignYToCenter(int y) const
{
    if (prefered_move_.getHorizontalMoveType() != MoveType::NONE)
        return y - (y_ + width_ / 4);
    return 0;
}

/**
 * It sets the direction of the road based on the rotation of the road
 */
void Road::setDirection()
{
    if (abs(rotation_degrees_) == 90 || abs(rotation_degrees_) == 270)
        direction_ = RoadDirection::VERTICAL;
    else if (abs(rotation_degrees_) == 0 || abs(rotation_degrees_) == 180)
        direction_ = RoadDirection::HORIZONTAL;
    else
        direction_ = RoadDirection::DIAGONAL;
}

/**
 * If the x and y coordinates of road1 are not equal to the x and y coordinates of road2, return true,
 * otherwise return false.
 * 
 * @param road1 The first road to compare.
 * @param road2 The road to compare to.
 * 
 * @return A boolean value.
 */
bool operator!=(const Road& road1, const Road& road2) { return road1.x_ != road2.x_ || road1.y_ != road2.y_; }