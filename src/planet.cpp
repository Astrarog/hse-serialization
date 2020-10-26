#include "planet.hpp"

#include <tuple>


namespace hse
{

    std::pair<bool, planet::pool_t::iterator> planet::getEmptyPortalPostion()
    {
        planet::pool_t::iterator position;
        bool success = hasEmptyPortal();

        if(success)
        {
            position = __portals.end() - __empty_portals_count;
        }

        return std::make_pair(success, position);
    }

    bool bindWithPortal(planet& first, planet& second)
    {
        bool success = (first!=second);
        auto [success_first, position_first] = first.getEmptyPortalPostion();
        auto [success_second, position_second] = second.getEmptyPortalPostion();
        success &= success_first && success_second;
        if(success)
        {
            --first.__empty_portals_count;
            --second.__empty_portals_count;
            *position_first  = &second;
            *position_second = &first;
        }
        return success;
    }

}
