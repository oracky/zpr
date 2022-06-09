#include "Simulation.h"
#include "Config.h"



int main(int argc, char** argv)
{
    auto config = Config(argc, argv);
    auto sim = Simulation(config);
    sim.run();
    return 0;
}