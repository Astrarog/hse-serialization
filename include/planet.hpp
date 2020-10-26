#ifndef PLANET_HPP
#define PLANET_HPP

#include "color.hpp"

#include <string>
#include <vector>
#include <tuple>
#include <cassert>

namespace hse {

    class planet;

    // Binds unoccupied portals if possible on both sides
    // and returns the success of operaion
    bool bindWithPortal(planet& firts, planet& second);

    class planet
    {
    private:

        using pool_t = std::vector<const planet*>;      //use boost::pool ?

        std::string __name;
        color __color;

        // count nullptrs in __portals container
        std::size_t __unexplored_portals_count;

        // portals represented as pointers
        // nullptr means that portal exist but
        // it is not yet conneted to other planet
        // it is guarantied that there is no portal to self
        // example of container state: [planet1, planet2, nullptr, nullptr, nullptr]
        pool_t __portals;

    public:

        // construct planet without any portals binded
        planet(const std::string& name, const color& color, std::size_t count)
            : __name(name), __color(color), __unexplored_portals_count(count), __portals(count, nullptr)
        {}

        // counstruct planet with parent portal
        // there will be count+1 portals in total
        planet(const std::string& name, const color& color, std::size_t count, planet& parent)
        {
            assert(count+1 != 0);
            planet(name, color, count+1);
            *(__portals.begin()) = &parent;
        }

        // Find the position of unbinded portals
        // Returns the success and the position
        // if the result was unseccessfull then
        // position is undefiend
        std::pair<bool, pool_t::iterator> getEmptyPortal();


        // Binds unoccupied portals if possible on both sides
        // and returns the success of operaion
        friend bool bindWithPortal(planet& firts, planet& second);

        // Analog of the function above
        bool bindWithPortal(planet& second) { return hse::bindWithPortal(*this, second); }


        bool operator==(const planet& other) const { return this == &other; }

    };

}

#endif // PLANET_HPP
