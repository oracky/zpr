#define BOOST_TEST_MODULE VehicleTest test
#include <boost/test/unit_test.hpp>
#include <SFML/Graphics.hpp>

#include "VehicleGraphical.h"
#include "VehicleType.hpp"


BOOST_AUTO_TEST_CASE(VehicleTest)
{
    auto veh = VehicleGraphical(1,1,1,VehicleType::CAR,sf::Color::Red,1.0f);

    BOOST_CHECK_EQUAL(1, veh.getXCoordinate());
    BOOST_CHECK_EQUAL(1, veh.getYCoordinate());
    BOOST_CHECK_EQUAL(1, veh.getSpeed());
    BOOST_CHECK_EQUAL(sf::Color::Red.a, veh.getColor().a);
    BOOST_CHECK_EQUAL(static_cast<int>(VehicleType::CAR), static_cast<int>(veh.getVehicleType()));
    BOOST_CHECK_EQUAL(true, veh.isActive());

    veh.setSpeed(8);
    BOOST_CHECK_EQUAL(8, veh.getSpeed());

    veh.setSpeed(99);
    BOOST_CHECK_EQUAL(10, veh.getSpeed());

    veh.setVehicleType(VehicleType::TRUCK);
    BOOST_CHECK_EQUAL(static_cast<int>(VehicleType::TRUCK), static_cast<int>(veh.getVehicleType()));

    veh.setColor(sf::Color::Black);
    BOOST_CHECK_EQUAL(sf::Color::Black.a, veh.getColor().a);
}
