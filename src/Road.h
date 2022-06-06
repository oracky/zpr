#ifndef Road_H
#define Road_H

#include <SFML/Graphics.hpp>
#include "Move.h"

class Road
{
public:
    Road();
    Road(int x, int y, float length, float width, const Move& preferedMove);
    sf::RectangleShape getShape() const; 
    Move getPreferedMove() const;
    void setPreferedMove(const Move& new_move);
    Move getOppositePreferedMove() const;
    friend bool operator!=(const Road& road1, const Road& road2);
private:
    int x_;
    int y_;
    float length_;
    float width_;
    Move preferedMove_;
    sf::RectangleShape shape_;
};

#endif