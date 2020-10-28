#ifndef PLANET_HPP
#define PLANET_HPP
#include "color.hpp"

#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <cassert>

namespace hse
{

    class planet;

    // Binds unoccupied portals if possible on both sides
    // and returns the success of operaion
    bool bindWithPortal(planet& firts, planet& second);

    class planet
    {
    public:

        // helper enum for different planet drawings
        enum class TYPE
        {
            EARTH=0, MOON, SATURN, MYSTERY,
            DEATH // indicates the number of elements in TYPE
        };

    private:

        using pool_t = std::vector<planet*>;      //use boost::pool ?

        std::string __name;
        color __color;

        // Marker that shows if planet was visited or not
        bool __is_visited = false;

        // Output helper field
        bool __show_new_planet = true;

        // count nullptrs in __portals container
        std::size_t __empty_portals_count;

        // portals represented as pointers
        // nullptr means that portal exist but
        // it is not yet conneted to other planet
        // it is guarantied that there is no portal to self
        // example of container state: [*planet1, *planet2, nullptr, nullptr, nullptr]
        pool_t __portals;

        TYPE __type;
    public:

        // helper function for ascii graphisc
        std::string_view getPlanetImage() const;

        // "Jumps in portal"
        // return the next planet taken by the index in __portals
        planet* Travel(std::size_t index)
        {
            assert(index<this->portals_count());
            return __portals[index];
        }

        //simple getters below
        std::string name() const { return __name; }
        color color() const { return __color; }
        std::size_t empty_portals_count() const { return __empty_portals_count;}
        std::size_t portals_count() const { return __portals.size();}

        const auto& portals() const & { return __portals; }
        auto& portals() & { return __portals; }
        auto&& portals() && { return std::move(__portals); }

        //add empty portal to the end of the container __portals
        void addEmptyPortal() { __portals.push_back(nullptr); }

        // construct planet without any portals binded
        // count==0 is an error;
        planet(const std::string& name, const class color& _color, std::size_t count, TYPE type)
            : __name(name), __color(_color), __empty_portals_count(count), __portals(count, nullptr), __type(type){}

        // Find the position of unbinded portals
        // Returns the success and the position
        // if the result was unseccessfull then
        // position is undefiend
        std::pair<bool, pool_t::iterator> getEmptyPortalPostion();

        // returns true is the planet was already visited
        bool isVisited() const { return __is_visited; }

        // Marks current planet as visited
        void markVisited() { __is_visited = true;}

        // helper output function
        bool showNewPlanet() { bool answer = __show_new_planet; __show_new_planet = false; return answer;}

        // return is there is empty potal in __portlas
        bool hasEmptyPortal() const { return __empty_portals_count;}

        // Binds unoccupied portals if possible on both sides
        // and returns the success of operaion
        friend bool bindWithPortal(planet& firts, planet& second);

        // Analog of the function above
        bool bindWithPortal(planet& second) { return hse::bindWithPortal(*this, second); }
        bool bindWithPortal(planet& second, std::size_t idx);


        bool operator==(const planet& other) const { return this == &other; }
        bool operator!=(const planet& other) const { return this != &other; }
        bool operator< (const planet& other) const { return std::tuple(__empty_portals_count, this)
                                                          < std::tuple(__empty_portals_count, &other); }

        // return random planet
    };

    extern planet generatePlanet();
    extern planet generateHelperPlanet();

    std::ostream& operator<<(std::ostream& out, hse::planet& _planet);

}

#endif // PLANET_HPP
