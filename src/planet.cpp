#include "planet.hpp"

#include <tuple>
#include <algorithm>


namespace hse
{

    std::pair<bool, planet::pool_t::iterator> planet::getEmptyPortal()
    {
        bool success = __unexplored_portals_count;
        planet::pool_t::iterator position;
        if(success)
        {
            position = __portals.end() - __unexplored_portals_count;
        }

        return std::make_pair(success, position);
    }

    bool bindWithPortal(planet& first, planet& second)
    {
        if(first==second)
            return false;

        auto [success_first, position_first] = first.getEmptyPortal();
        if(!success_first)
            return false;

        auto [success_second, position_second] = second.getEmptyPortal();
        if(!success_second)
            return false;

        --first.__unexplored_portals_count;
        --second.__unexplored_portals_count;
        *position_first  = &second;
        *position_second = &first;

        return true;
    }
}
