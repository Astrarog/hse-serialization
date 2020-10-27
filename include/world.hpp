#ifndef WORLD_HPP
#define WORLD_HPP

#include "planet.hpp"

#include <set>

namespace hse
{

    // world with finit number of planets
    class SimpleWorld
    {
        // __galaxy.begin() is an initial planet
        std::vector<planet> __galaxy;
        std::size_t __count_visited = 0;

    public:
        // World generation
        SimpleWorld();

        // Simple getters
        const auto& galaxy() const & { return __galaxy; }
        auto& galaxy() & { return __galaxy; }
        auto&& galaxy() && { return std::move(__galaxy); }

        planet* home() { return &(__galaxy.front()); }

        // returns true is the planet was already visited
        bool isHome(const planet& _planet) const { return __galaxy.front()==_planet; }

        // returns the number of planets in world
        std::size_t WorldSize() const { return __galaxy.size(); }

        // returns the number of planets that was already visited
        std::size_t CountVisited() const { return __count_visited; }

        // Marks planet as visited
        void markVisited(planet& _planet)
        {
            if(!(_planet.isVisited()))
            {
                ++__count_visited;
                _planet.markVisited();
            }
        }

    };

    // infinitly growing world
    class InviniteWorld
    {

    };

    //returns random planet
    planet generatePlanet();
}
#endif // WORLD_HPP
