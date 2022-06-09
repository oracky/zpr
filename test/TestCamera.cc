#define BOOST_TEST_MODULE CameraTest test
#include <boost/test/unit_test.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

#include "SimulationTable.h"
#include "Camera.h"


bool is_close(double a, double b, double epsilon = 1e-5) { 
    return std::fabs(a - b) < epsilon; 
}

BOOST_AUTO_TEST_CASE(CameraTest)
{
    auto st = SimulationTable();
    auto c = Camera(1,1,0,sf::Color::Red,1.0f,st);

    BOOST_CHECK_EQUAL(1, c.getXCoordinate());
    BOOST_CHECK_EQUAL(1, c.getYCoordinate());
    BOOST_CHECK_EQUAL(true, is_close(1.0f, c.getSize()));
    BOOST_CHECK_EQUAL(sf::Color::Red.a, c.getColor().a);
    BOOST_CHECK_EQUAL(0, c.getRotation());

    c.setXCoordinate(5);
    BOOST_CHECK_EQUAL(5, c.getXCoordinate());

    c.setYCoordinate(6);
    BOOST_CHECK_EQUAL(6, c.getYCoordinate());

    c.setRotation(90);
    BOOST_CHECK_EQUAL(90, c.getRotation());

    c.setSize(50.0f);
    BOOST_CHECK_EQUAL(true, is_close(50.0f, c.getSize()));

    c.setColor(sf::Color::Blue);
    BOOST_CHECK_EQUAL(sf::Color::Blue.a, c.getColor().a);
}
