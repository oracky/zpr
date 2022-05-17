#define BOOST_TEST_MODULE SimulationTest
#include <boost/test/unit_test.hpp>

#include "Simulation.h"


BOOST_AUTO_TEST_CASE(PassTest)
{
    BOOST_CHECK_EQUAL(3, simulate(2));
}
