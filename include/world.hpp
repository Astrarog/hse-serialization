#ifndef WORLD_HPP
#define WORLD_HPP

#include "planet.hpp"

#include <string>
#include <list>
#include <iostream>

namespace hse
{

    class world_base
    {
    protected:
        // __galaxy.begin() is an initial planet
        // and beacause of this it is already visited
        std::vector<planet> __galaxy;
        std::size_t __count_visited = 1;
    public:
        virtual std::string getPlanetInfo(hse::planet&) const;

        world_base(){}

        // Simple getters
        const auto& galaxy() const & { return __galaxy; }
        auto& galaxy() & { return __galaxy; }
        auto&& galaxy() && { return std::move(__galaxy); }

        planet& home() { return __galaxy.front(); }
        std::int32_t homeIdx() const { return 0; }

        // returns true is the planet was already visited
        bool isHome(const planet& _planet) const { return __galaxy.front()==_planet; }

        // returns the number of planets that was already visited
        std::size_t CountVisited() const { return __count_visited; }

        // returns the number of planets in world currently
        std::size_t WorldSize() const { return __galaxy.size(); }

        planet& planetByIdx(std::size_t idx) {return __galaxy[idx]; }

        // Travels to the next planet
        virtual std::int32_t Travel(std::int32_t planet_idx, std::size_t idx) = 0;

        // Returns true if victory condition granted
        virtual bool isVictory() = 0;

    };


    // world with finit number of planets
    // it is guarantee that there will be no unbidnded portals
    class SimpleWorld: public world_base
    {

    public:

        // World generation
        SimpleWorld();

        //Travels to the next planet and marks it as visited if needed
        virtual std::int32_t Travel(std::int32_t, std::size_t) override;
        virtual bool isVictory() override { return this->CountVisited()==this->WorldSize(); }

        virtual std::string getPlanetInfo(hse::planet &_planet) const;
    };


    // infinitly growing tree-like world
    class InfiniteWorld: public world_base
    {

    public:
        InfiniteWorld();

        // Travels to the next planet
        virtual std::int32_t Travel(std::int32_t, std::size_t) override;
        virtual bool isVictory() override { return false; }
    };

}
#endif // WORLD_HPP
