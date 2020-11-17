#ifndef WORLD_HPP
#define WORLD_HPP

#include "planet.hpp"

#include <string>
#include <list>
#include <iostream>
#include <nop/structure.h>

namespace hse
{

    class world
    {
    protected:
        // galaxy_.begin() is an initial planet
        // and beacause of this it is already visited
        std::vector<planet> galaxy_;
        std::size_t count_visited_ = 1;
        std::size_t count_unbinded_portals_ = 0;

    public:
        std::string getPlanetPrefix(hse::planet&);

        std::vector<std::pair<std::string, std::string>> getPlanetChoises(hse::planet& _planet) const;

        world();
        world(std::size_t);

        // adds the provided number of planets to currnet world
        void generatePlanets(std::size_t);

        // Simple getters
        const auto& galaxy() const & { return galaxy_; }
        auto& galaxy() & { return galaxy_; }
        auto&& galaxy() && { return std::move(galaxy_); }

        planet& home() { return galaxy_.front(); }
        std::int32_t homeIdx() const { return 0; }

        // returns true is the planet was already visited
        bool isHome(const planet& _planet) const { return galaxy_.front()==_planet; }

        // returns the number of planets that was already visited
        std::size_t CountVisited() const { return count_visited_; }

        // returns the number of planets in world currently
        std::size_t WorldSize() const { return galaxy_.size(); }

        // returns the number of planets in world and the number of portals
        std::size_t WorldCapacity() const { return galaxy_.size() + count_unbinded_portals_ ;}

        auto& planetByIdx(std::size_t idx) & { return galaxy_[idx]; }
        const auto& planetByIdx(std::size_t idx) const & { return galaxy_[idx]; }

        // Randomly connetcs currnet unbinded portals
        // The unbinded portals may left ater this operation
        void connectCurrnet();

        // If there is nonbinded portals in galaxy then
        // will be created oneway planets and bindede with
        // those portal respectively
        void makeFinit();

        //add empty portal to the planet provided by index in galaxy
        void addEmptyPortal(std::int32_t planet_idx);

        // Travels to the next planet
        std::int32_t Travel(std::int32_t planet_idx, std::size_t to_idx);

        // Returns true if victory condition granted
        bool isVictory() const { return this->CountVisited()==this->WorldSize() && count_unbinded_portals_==0; }

        NOP_STRUCTURE(world, galaxy_, count_visited_, count_unbinded_portals_);
    };

}
#endif // WORLD_HPP
