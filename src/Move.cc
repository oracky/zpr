#include "Move.h"


/**
 * An empty constructor for the Move class.
 */
Move::Move(){}

/**
 * This function is a constructor for the Move class. It takes two parameters, both of which are of
 * type MoveType. It sets the vertical_ and horizontal_ member variables to the values of the
 * parameters
 * 
 * @param horizontal The horizontal direction of the move.
 * @param vertical The vertical direction of the move.
 */
Move::Move(MoveType horizontal, MoveType vertical) : vertical_(vertical), horizontal_(horizontal) {}

/**
 * It returns the vertical value of the move.
 * 
 * @return The vertical_ value of the move.
 */
float Move::getVertical() const { return static_cast<float>(vertical_); }

/**
 * This function returns the horizontal value of the Move object.
 * 
 * @return The horizontal value of the move.
 */
float Move::getHorizontal() const { return static_cast<float>(horizontal_); }

/**
 * Returns the horizontal move type.
 * 
 * @return The horizontal move type.
 */
MoveType Move::getHorizontalMoveType() const { return horizontal_; }

/**
 * Returns the vertical move type.
 * 
 * @return The vertical move type.
 */
MoveType Move::getVerticalMoveType() const { return vertical_; }

/**
 * This function takes in a `MoveType` and sets the `horizontal_` member variable to that value
 * 
 * @param type The type of move to set.
 */
void Move::setHorizontal(MoveType type) { horizontal_ = type;}

/**
 * This function takes in a `MoveType` and sets the `vertical_` member variable to that value
 * 
 * @param type The type of move to set.
 */
void Move::setVertical(MoveType type) { vertical_ = type;}