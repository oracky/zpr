#ifndef Move_H
#define Move_H

enum class MoveType
{
    None=0,
    UP=1,
    DOWN=-1,
    RIGHT=1,
    LEFT=-1
};

class Move
{
public:
    Move();
    Move(MoveType vertical, MoveType horizontal);
    float getVertical() const;
    float getHorizontal() const;
private:
    MoveType vertical_;
    MoveType horizontal_;
};

#endif