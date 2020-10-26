#ifndef WORLD_HPP
#define WORLD_HPP

#include "planet.hpp"

#include <set>

namespace hse
{
    class world_base
    {
    protected:
        planet initial_planet;
    public:
        world_base(const planet& init): initial_planet(init){}
    };


    // world with 10..20 planets
    class SimpleWorld: protected world_base
    {
        std::set<planet> __galaxy;

    public:
        SimpleWorld();

    };

    // infinitly growing world
    class InviniteWorld: public world_base
    {

    };

    //returns random planet
    planet generatePlanet();
}
#endif // WORLD_HPP
