#define BOOST_TEST_MODULE RoadTest test
#include <boost/test/unit_test.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

#include "Move.h"
#include "Road.h"

bool is_close(double a, double b, double epsilon = 1e-5) { 
    return std::fabs(a - b) < epsilon; 
}

BOOST_AUTO_TEST_CASE(RoadTest)
{
    auto prefered_move = Move(MoveType::RIGHT, MoveType::NONE);
    auto prefered_move_2 = Move(MoveType::NONE, MoveType::UP);
    auto road = Road(1,1,1.0f,2.0f,prefered_move);

    BOOST_CHECK_EQUAL(true, is_close(2.0f, road.getWidth()));
    BOOST_CHECK_EQUAL(static_cast<int>(RoadDirection::HORIZONTAL), static_cast<int>(road.getDirection()));
    BOOST_CHECK_EQUAL(road.getPreferedMove().getHorizontal(), -road.getOppositePreferedMove().getHorizontal());

    road.setPreferedMove(prefered_move_2);
    BOOST_CHECK_EQUAL(road.getPreferedMove().getVertical(), -road.getOppositePreferedMove().getVertical());
}