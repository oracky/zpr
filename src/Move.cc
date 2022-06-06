#include "Move.h"

Move::Move(){}
Move::Move(MoveType vertical, MoveType horizontal) : vertical_(vertical), horizontal_(horizontal) {}
float Move::getVertical() const { return static_cast<float>(vertical_); }
float Move::getHorizontal() const { return static_cast<float>(horizontal_); }