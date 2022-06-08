#include "Move.h"


Move::Move(){}
Move::Move(MoveType horizontal, MoveType vertical) : vertical_(vertical), horizontal_(horizontal) {}
float Move::getVertical() const { return static_cast<float>(vertical_); }
float Move::getHorizontal() const { return static_cast<float>(horizontal_); }
MoveType Move::getHorizontalMoveType() const { return horizontal_; }
MoveType Move::getVerticalMoveType() const { return vertical_; }
void Move::setHorizontal(MoveType type) { horizontal_ = type;}
void Move::setVertical(MoveType type) { vertical_ = type;}