#ifndef Road_H
#define Road_H

#include <SFML/Graphics.hpp>
#include <utility>
#include <functional>
#include "Move.h"


enum class RoadDirection
{
    HORIZONTAL,
    VERTICAL,
    DIAGONAL
};


class Road
{
public:
    Road();
    Road(int x, int y, float length, float width, const Move& preferedMove, int rotation_degrees=0);
    sf::RectangleShape getShape() const; 
    Move getPreferedMove() const;
    bool isActive() const;
    float getWidth() const;
    RoadDirection getDirection() const;
    void setPreferedMove(const Move& new_move);
    Move getOppositePreferedMove() const;
    int alignXToCenter(int x) const;
    int alignYToCenter(int y) const;
    friend bool operator!=(const Road& road1, const Road& road2);

private:
    bool active_;
    int x_;
    int y_;
    int rotation_degrees_;
    float length_;
    float width_;
    Move prefered_move_;
    RoadDirection direction_;
    sf::RectangleShape shape_;

    void setDirection();
};

#endif