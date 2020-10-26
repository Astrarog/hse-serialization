#include "world.hpp"
#include "random.hpp"

#include <random>
#include <cstdint>

namespace hse
{

    // generates world with 10..20 planets
    SimpleWorld::SimpleWorld(): world_base(generatePlanet())
    {

        std::size_t planets_count = std::uniform_int_distribution<>(10, 20)(randomGenerator);

        /* world generation */
    }
}
