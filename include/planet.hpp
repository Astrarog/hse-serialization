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

        std::string name_;
        color color_;

        // Marker that shows if planet was visited or not
        bool is_visited_ = false;

        // Output helper field
        bool show_new_planet_ = true;

        // count nullptrs in portals_ container
        std::size_t empty_portals_count_;

        // portals represented as indexes in the world_base object
        // -1 means that portal exist but
        // it is not yet conneted to other planet
        // it is guarantied that there is no portal to self
        // example of container state: [planet_idx1, planet_idx2, -1, -1, -1]
        pool_t portals_;

        TYPE type_;

        NOP_STRUCTURE(planet, name_, color_, is_visited_, show_new_planet_, empty_portals_count_, portals_, type_);
    public:

        // helper function for ascii graphisc
        std::string_view getPlanetImage() const;

        // "Jumps in portal"
        // return the next planet index taken by the index in portals_
        std::int32_t Travel(std::size_t index)
        {
            assert(index < this->portals_count());
            return portals_[index];
        }

        //simple getters below
        std::string name() const { return name_; }
        color Color() const { return color_; }
        std::size_t empty_portals_count() const { return empty_portals_count_;}
        std::size_t portals_count() const { return portals_.size();}

        const auto& portals() const & { return portals_; }
        auto& portals() & { return portals_; }
        auto&& portals() && { return std::move(portals_); }

        //add empty portal to the end of the container portals_
        void addEmptyPortal() { portals_.push_back(-1); }

        // construct planet without any portals binded
        // count==0 is an error;
        planet(const std::string& name, const color& _color, std::size_t count, TYPE type)
            : name_(name), color_(_color), empty_portals_count_(count), portals_(count, -1), type_(type){}

        // needed for nop
        planet(){}

        // Returns the position of unbinded portals if last exist
        // Otherwise returns the portals_.end()
        pool_t::iterator getEmptyPortalPostion();

        // returns true is the planet was already visited
        bool isVisited() const { return is_visited_; }

        // Marks current planet as visited
        void markVisited() { is_visited_ = true;}

        // helper output function
        bool showNewPlanet() { bool answer = show_new_planet_; show_new_planet_ = false; return answer;}

        // return is there is empty potal in __portlas
        bool hasEmptyPortal() const { return empty_portals_count_;}

        // sets portal idx to value and reduces the amount of empty portals
        // DOES NOT CHECK THE AVAILABILITY TO DO IT
        void makePortal(std::int32_t);

        bool operator==(const planet& other) const { return std::tuple(name_, color_) == std::tuple(other.name_, other.color_); }
        bool operator!=(const planet& other) const { return std::tuple(name_, color_) != std::tuple(other.name_, other.color_); }
        bool operator< (const planet& other) const { return std::tuple(name_, color_) <  std::tuple(other.name_, other.color_); }

        // return random planet
    };

    extern planet generatePlanet();
    extern planet generateHelperPlanet();

    std::ostream& operator<<(std::ostream& out, hse::planet& _planet);

}

#endif // PLANET_HPP
