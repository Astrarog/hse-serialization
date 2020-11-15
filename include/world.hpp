#ifndef WORLD_HPP
#define WORLD_HPP

#include "planet.hpp"

#include <string>
#include <list>
#include <iostream>
#include <nop/structure.h>

namespace hse
{

    class world_base
    {
    protected:
        // galaxy_.begin() is an initial planet
        // and beacause of this it is already visited
        std::vector<planet> galaxy_;
        std::size_t count_visited_ = 1;
    public:
        virtual std::string getPlanetPrefix(hse::planet&);

        std::vector<std::pair<std::string, std::string>> getPlanetChoises(hse::planet& _planet) const;

        world_base(){}
        virtual ~world_base() = default;

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

        auto& planetByIdx(std::size_t idx) & { return galaxy_[idx]; }
        const auto& planetByIdx(std::size_t idx) const & { return galaxy_[idx]; }

        // Travels to the next planet
        virtual std::int32_t Travel(std::int32_t planet_idx, std::size_t to_idx) {return galaxy_[planet_idx].Travel(to_idx); }

        // Returns true if victory condition granted
        virtual bool isVictory() const {return true; }

        NOP_STRUCTURE(world_base, galaxy_, count_visited_);
    };


    // world with finit number of planets
    // it is guarantee that there will be no unbidnded portals
    class SimpleWorld: public world_base
    {

    public:

        // Generate world generation with 10..20 planets
        SimpleWorld();

        // Generate world with at least size planets and no more than size+7 planets
        SimpleWorld(std::size_t);

        virtual ~SimpleWorld() = default;

        //Travels to the next planet and marks it as visited if needed
        virtual std::int32_t Travel(std::int32_t, std::size_t) override;
        virtual bool isVictory() const override { return this->CountVisited()==this->WorldSize(); }

        virtual std::string getPlanetPrefix(hse::planet &_planet);

        NOP_STRUCTURE(SimpleWorld);
    };


    // infinitly growing tree-like world
    class InfiniteWorld: public world_base
    {

    public:
        InfiniteWorld();
        virtual ~InfiniteWorld()=default;

        // Travels to the next planet
        virtual std::int32_t Travel(std::int32_t, std::size_t) override;
        virtual bool isVictory() const override { return false; }

        NOP_STRUCTURE(InfiniteWorld);
    };

}
#endif // WORLD_HPP
