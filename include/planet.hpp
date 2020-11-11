#ifndef PLANET_HPP
#define PLANET_HPP
#include "color.hpp"

#include <string>
#include <string_view>
#include <vector>
#include <tuple>
#include <map>
#include <cassert>

#include <nop/structure.h>

namespace hse
{

    class planet;

    // Binds unoccupied portals if possible on both sides
    // and returns the success of operaion
    bool bindWithPortal(planet& first, std::int32_t firts_idx, planet& second, std::int32_t second_idx);

    class planet
    {
    public:

        // helper enum for different planet drawings
        enum class TYPE
        {
            EARTH=0, ASTEROID, MOON, SATURN, MYSTERY,
            DEATH // indicates the number of elements in TYPE
        };

    private:

        using pool_t = std::vector<std::int32_t>;

        std::string __name;
        color __color;

        // Marker that shows if planet was visited or not
        bool __is_visited = false;

        // Output helper field
        bool __show_new_planet = true;

        // count nullptrs in __portals container
        std::size_t __empty_portals_count;

        // portals represented as indexes in the world_base object
        // -1 means that portal exist but
        // it is not yet conneted to other planet
        // it is guarantied that there is no portal to self
        // example of container state: [planet_idx1, planet_idx2, -1, -1, -1]
        pool_t __portals;

        TYPE __type;

        NOP_STRUCTURE(planet, __name, __color, __is_visited, __show_new_planet, __empty_portals_count, __portals, __type);
    public:

        // helper function for ascii graphisc
        std::string_view getPlanetImage() const;

        // "Jumps in portal"
        // return the next planet index taken by the index in __portals
        std::int32_t Travel(std::size_t index)
        {
            assert(index < this->portals_count());
            return __portals[index];
        }

        //simple getters below
        std::string name() const { return __name; }
        color Color() const { return __color; }
        std::size_t empty_portals_count() const { return __empty_portals_count;}
        std::size_t portals_count() const { return __portals.size();}

        const auto& portals() const & { return __portals; }
        auto& portals() & { return __portals; }
        auto&& portals() && { return std::move(__portals); }

        //add empty portal to the end of the container __portals
        void addEmptyPortal() { __portals.push_back(-1); }

        // construct planet without any portals binded
        // count==0 is an error;
        planet(const std::string& name, const class color& _color, std::size_t count, TYPE type)
            : __name(name), __color(_color), __empty_portals_count(count), __portals(count, -1), __type(type){}

        // needed for nop
        planet(){}

        // Returns the position of unbinded portals if last exist
        // Otherwise returns the __portals.end()
        pool_t::iterator getEmptyPortalPostion();

        // returns true is the planet was already visited
        bool isVisited() const { return __is_visited; }

        // Marks current planet as visited
        void markVisited() { __is_visited = true;}

        // helper output function
        bool showNewPlanet() { bool answer = __show_new_planet; __show_new_planet = false; return answer;}

        // return is there is empty potal in __portlas
        bool hasEmptyPortal() const { return __empty_portals_count;}

        // sets portal idx to value and reduces the amount of empty portals
        // DOES NOT CHECK THE AVAILABILITY TO DO IT
        void makePortal(std::int32_t);

        bool operator==(const planet& other) const { return std::tuple(__name, __color) == std::tuple(other.__name, other.__color); }
        bool operator!=(const planet& other) const { return std::tuple(__name, __color) != std::tuple(other.__name, other.__color); }
        bool operator< (const planet& other) const { return std::tuple(__name, __color) <  std::tuple(other.__name, other.__color); }

        // return random planet
    };

    extern planet generatePlanet();
    extern planet generateHelperPlanet();

    std::ostream& operator<<(std::ostream& out, hse::planet& _planet);

}

#endif // PLANET_HPP
