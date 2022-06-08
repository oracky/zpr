#include <random>
#include <vector>
#include <iostream>
#include <thread>
#include <unistd.h>
#include "Vehicle.h"
#include "VehicleGraphical.h"
#include "Move.h"


VehicleGraphical::VehicleGraphical() {}
VehicleGraphical::VehicleGraphical(int x, int y, int speed, const VehicleType& type, const sf::Color& color, float size)
    : Vehicle(x, y, speed, type, color), size_(size)
{
    shape_ = sf::RectangleShape(sf::Vector2f(size_, size_));
    shape_.setPosition(x_, y_);
    shape_.setFillColor(color_);
}

VehicleGraphical VehicleGraphical::spawnClone() const
{
    return VehicleGraphical(initial_x_, initial_y_, speed_, type_, color_, size_);
}

// void VehicleGraphical::update(const std::vector<Road>& roads)
// {
//     bool can_move = false;
//     auto bounding_box_shape = shape_.getGlobalBounds();

//     if (isOnTheRoad(bounding_box_shape, current_road_.getShape().getGlobalBounds()))
//     {
//         move(current_road_);
//         return;
//     }

//     for (auto road : roads)
//     {
//         auto bounding_box_road = road.getShape().getGlobalBounds();

//         if (road != current_road_ && isOnTheRoad(bounding_box_shape, bounding_box_road))
//         {
//             move(road);
//             can_move = true;
//             break;
//         }
//     }

//     if (!can_move)
//     {
//         current_road_.setPreferedMove(current_road_.getOppositePreferedMove());
//         move(current_road_);
//     }
// }
void VehicleGraphical::update(const std::vector<Road>& roads)
{
    auto bounding_box_shape = shape_.getGlobalBounds();
    std::vector<Road> available_roads;

    for (auto road : roads)
    {
        auto bounding_box_road = road.getShape().getGlobalBounds();

        if (road != last_road_ && isOnTheRoad(bounding_box_shape, bounding_box_road))
        {
            available_roads.push_back(road);
        }

        // If the car has 2 available roads (which it intersects), we assume it is enough to make a choice
        // if it should turn and where exactly (to boost efficency if there are a lot of roads)
        if (available_roads.size() == 2)
            break;
    }

    if (!available_roads.empty())
    {
        Road chosen_road;
        if (available_roads.size() > 1)
        {
            int road_index_choosen = generateRandomMove(0, 100);

            if (road_index_choosen < 70)
            {
                chosen_road = current_road_;
            }

            else
            {
                road_index_choosen = generateRandomMove(0, available_roads.size()-1);
                std::cout << road_index_choosen << std::endl;
                
                chosen_road = available_roads[road_index_choosen];
                if (chosen_road != current_road_)
                {
                    last_road_ = current_road_;
                }
                    
                else
                {
                    for (auto& road : available_roads)
                    {
                        if ( road != current_road_)
                        {
                            last_road_ = road;
                            break;
                        }
                    }
                } 
            }
        }

        else
        {
            chosen_road = available_roads[0];
        }

        move(chosen_road);
        return;
    }

    else
    {
        active_ = false;
    }

    move(current_road_);

}

sf::RectangleShape VehicleGraphical::getShape() const { return shape_; }

bool VehicleGraphical::isOnTheRoad(const sf::FloatRect& bounding_box_shape, const sf::FloatRect& bounding_box_road)
{
    return bounding_box_shape.intersects(bounding_box_road);
}

void VehicleGraphical::move(Road& road, int boost)
{
    auto prefered_move = road.getPreferedMove();

    int x_align = 0;
    int y_align = 0;

    if (road.getDirection() == RoadDirection::HORIZONTAL)
    {
        y_align = road.alignYToCenter(y_);
        y_ -= y_align;
    }
    else if(road.getDirection() == RoadDirection::VERTICAL)
    {
        x_align = road.alignXToCenter(x_);
        x_ -= x_align;
    }
        
    else
    {
        x_align = road.alignXToCenter(x_);
        x_ += x_align;
        y_align = road.alignYToCenter(y_);
        y_ -= y_align;
    }
        

    x_ += prefered_move.getHorizontal() * speed_ / SPEED_TRANSLATION_;
    y_ += prefered_move.getVertical() * speed_  / SPEED_TRANSLATION_;
    shape_.setPosition(x_, y_);

    current_road_ = road;
}



int VehicleGraphical::generateRandomMove(const int & min, const int & max) const
{
    static thread_local std::mt19937 generator;
    std::uniform_int_distribution<int> distribution(min,max);
    return distribution(generator);
}