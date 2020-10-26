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

    //returns random planet
    extern planet generatePlanet();
}
#endif // WORLD_HPP
