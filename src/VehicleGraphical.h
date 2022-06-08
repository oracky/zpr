#ifndef VehicleGraphical_H
#define VehicleGraphical_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Vehicle.h"
#include "Road.h"


class VehicleGraphical : public Vehicle
{
public:
    VehicleGraphical();
    VehicleGraphical(int x, int y, int speed, const VehicleType& type, const sf::Color& color, float size);
    void update(const std::vector<Road>& roads) override;
    VehicleGraphical spawnClone() const;
    sf::RectangleShape getShape() const;
private:
    static constexpr float SPEED_TRANSLATION_ = 15.f;
    float size_;
    sf::RectangleShape shape_;
    Road current_road_;
    Road recent_road_;
    Move prefered_move_;

    int generateRandomMove(const int & min, const int & max) const;
    void setPreferedMove();
    void markRecentRoad();
    void move(Road& road, int boost = 0);
    void move(Road& road, Road& current_road, int boost);
    bool isOnTheRoad(const sf::FloatRect& bounding_box_shape, const sf::FloatRect& bounding_box_road);
    std::vector<Road> findRoadIntersections(const std::vector<Road>& roads);
};


#endif