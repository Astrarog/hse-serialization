#include "world.hpp"
#include "random.hpp"

#include <random>
#include <cstdint>
#include <vector>
#include <functional>
#include <sstream>
#include <algorithm>


namespace hse
{
//TO DO OUTPUT
    std::string world_base::getPlanetInfo(hse::planet& _planet) const
    {
        std::ostringstream out;
        out << _planet.getPlanetImage();
        if(_planet.showNewPlanet())
        {
            out << "Comader! We have found a new planet!\n";
        }
        out << "NAME : " <<_planet.name()  << "\n";
        out << "COLOR: " <<_planet.color() << "\n"
                                             << "\n";
        out << "Possible next hops:\n\n";
        std::size_t index=1;
        for (std::int32_t next_idx: _planet.portals())
        {
            out << "  ["<< index++ << "] ";
            if(next_idx == -1 || !__galaxy[next_idx].isVisited())
            {
                out << "(UNKNOWN)\n";
            }else
            {
                out << __galaxy[next_idx].name() << "\n";
            }
        }
        return out.str();
    }

    std::string SimpleWorld::getPlanetInfo(hse::planet &_planet) const
    {
        std::ostringstream out;
        out << world_base::getPlanetInfo(_planet);
        out << "\n  [Our intelligence reports that we have found " << CountVisited() << " out of " << WorldSize() << "]\n";
        return out.str();
    }


    std::int32_t random_element_idx(const std::vector<planet>& data)
    {
        assert(data.size()>0);
        std::uniform_int_distribution<std::int32_t> pick_elem(0, data.size() - 1);
        return pick_elem(randomGenerator);
    }

    std::int32_t random_element_idx(const std::vector<std::int32_t>& data)
    {
        assert(data.size()>0);
        std::uniform_int_distribution<std::int32_t> pick_elem(0, data.size() - 1);
        return data[pick_elem(randomGenerator)];
    }

    std::vector<std::int32_t> filter(const std::vector<planet>& data, const std::vector<std::int32_t>& idxs, std::function<bool(const planet &)> predicate)
    {
        std::vector<std::int32_t> output;
        for (std::size_t i=0; i<data.size(); ++i)
        {
            if (predicate(data[i])&& std::find(idxs.begin(), idxs.end(), i) != idxs.end())
                output.push_back(i);
        }
        return output;
    }
    std::vector<std::int32_t> filter(const std::vector<planet>& data, std::function<bool(const planet &)> predicate)
    {
        std::vector<std::int32_t> output;
        for (std::size_t i=0; i<data.size(); ++i)
        {
            if (predicate(data[i]))
                output.push_back(i);
        }
        return output;
    }

    void connect_planets(std::vector<planet>& data, std::int32_t planet_idx, std::vector<std::int32_t>& pool)
    {
        planet& _planet = data[planet_idx];
        if(!(pool.size()>1 && _planet.hasEmptyPortal()))
            return;
        auto hasEmptyPortal = [](const planet& e){ return e.hasEmptyPortal(); };
        auto notSelf = [&_planet](const planet& e){ return _planet!=e; };

        while((pool = filter(data, pool, hasEmptyPortal)).size()>1 &&
              _planet.hasEmptyPortal())
        {
            std::int32_t other_planet_idx = random_element_idx(filter(data, pool, notSelf));
            planet& other_planet = data[other_planet_idx];
            bindWithPortal(_planet, planet_idx,
                           other_planet, other_planet_idx);
        }
        for(std::int32_t connected_planet_idx :_planet.portals())
        {
            connect_planets(data, connected_planet_idx, pool);
        }
    }

    // generates world with 10..20 planets
    SimpleWorld::SimpleWorld()
    {
        // generate planets without connections
        std::size_t planets_count = std::uniform_int_distribution<std::size_t>(10, 20)(randomGenerator);

        for(std::size_t i = 0; i<planets_count; ++i)
        {
            __galaxy.push_back(generatePlanet());
        }
        // connecting planets
        std::vector<std::int32_t> connectivity_parts;


        //initialize pool with every planet, because no planets connected yet
        std::vector<std::int32_t> pool = filter(__galaxy, [](const planet&){return true;});
        do
        {
            connectivity_parts.push_back(random_element_idx(pool));

            //pool changes with the connect_planets call
            connect_planets(__galaxy, connectivity_parts.back(),  pool);
        }while(pool.size()>1);


        //There is one planet left with unbinded portals
        if(pool.size()==1)
        {
            std::int32_t last_planet_idx = pool.back();
            while(__galaxy[last_planet_idx].hasEmptyPortal())
            {
                //generate planet with only portal to last_planet
                __galaxy.push_back(generateHelperPlanet());

                bindWithPortal(__galaxy[last_planet_idx], last_planet_idx,
                            __galaxy.back(), __galaxy.size()-1);
            }
        }

        // At this parts there should be no empty portals left
        auto hasEmptyPortal = [](const planet& e){ return e.hasEmptyPortal(); };
        assert(filter(__galaxy, pool, hasEmptyPortal).size()==0);

        // Make graph fully connected if needed
        while (connectivity_parts.size()>1)
        {
            std::int32_t first_idx = connectivity_parts.back();
            planet& first = __galaxy[first_idx];
            connectivity_parts.pop_back();

            std::int32_t second_idx = connectivity_parts.back();
            planet& second = __galaxy[second_idx];

            first.addEmptyPortal();
            second.addEmptyPortal();

            bindWithPortal(first, first_idx,
                           second, second_idx);
        }
        // World is generated at this point
        __galaxy.front().markVisited();
        __galaxy.front().showNewPlanet();
    }

    std::int32_t SimpleWorld::Travel(std::int32_t current_idx, std::size_t to_idx)
    {
        std::int32_t next_idx = __galaxy[current_idx].Travel(to_idx);
        planet& next = __galaxy[next_idx];
        if(!(next.isVisited()))
        {
            ++__count_visited;
            next.markVisited();
        }
        return next_idx;
    }



    InfiniteWorld::InfiniteWorld()
    {
        __galaxy.push_back(generatePlanet());
        __galaxy.front().markVisited();
        __galaxy.front().showNewPlanet();
    }

    std::int32_t InfiniteWorld::Travel(std::int32_t current_idx, std::size_t to_idx)
    {
        std::int32_t next_idx = __galaxy[current_idx].Travel(to_idx);
        if(next_idx == -1)
        {
            __galaxy.push_back(generatePlanet());

            planet& current = __galaxy[current_idx];
            planet& new_planet = __galaxy.back();
            next_idx = __galaxy.size()-1;
            bindWithPortal(current, current_idx,
                        new_planet, next_idx );
            new_planet.markVisited();
        }
        return next_idx;
    }
}
