#ifndef Move_H
#define Move_H

enum class MoveType
{
    NONE=0,
    UP=-1,
    DOWN=1,
    RIGHT=1,
    LEFT=-1
};

class Move
{
public:
    Move();
    Move(MoveType horizontal, MoveType vertical);
    float getVertical() const;
    MoveType getVerticalMoveType() const;
    float getHorizontal() const;
    MoveType getHorizontalMoveType() const;
private:
    MoveType vertical_;
    MoveType horizontal_;
};

#endif