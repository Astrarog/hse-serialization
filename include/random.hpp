#ifndef RANDOM_HPP
#define RANDOM_HPP

#include "color.hpp"
#include "planet.hpp"

#include <random>
#include <string>

namespace hse
{
    //prng
    extern std::mt19937 randomGenerator;

    // returns random string with lenght from 5 to 10 symbols
    extern std::string generateString();

    // returns random color
    extern color generateColor();

    //returns random valid planet type
    extern planet::TYPE generatePlanetType();

    //returns random planet with 1..7 empty portals and provided parent
    extern planet generatePlanet();

    //returns random planet with only parent portal
    extern planet generateHelperPlanet(planet& parent);
}
#endif // WORLD_HPP
