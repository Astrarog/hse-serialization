#include "world.hpp"
#include "random.hpp"

#include <random>
#include <cstdint>
#include <vector>
#include <functional>

namespace hse
{

    planet* random_element(const std::vector<planet>& data)
    {
        assert(data.size()>0);
        std::uniform_int_distribution<std::size_t> pick_elem(0, data.size() - 1);
        return const_cast<planet*>(&(data[pick_elem(randomGenerator)]));
    }

    planet* random_element(const std::vector<planet*>& data)
    {
        std::uniform_int_distribution<std::size_t> pick_elem(0, data.size() - 1);
        return data[pick_elem(randomGenerator)];
    }

    std::vector<planet*> filter(const std::vector<planet*>& data, std::function<bool(const planet &)> predicate)
    {
        std::vector<planet*> output;
        for (auto& elem : data)
        {
            if (predicate(*elem))
                output.push_back(const_cast<planet*>(elem));
        }
        return output;
    }
    std::vector<planet*> filter(const std::vector<planet>& data, std::function<bool(const planet &)> predicate)
    {
        std::vector<planet*> output;
        for (auto& elem : data)
        {
            if (predicate(elem))
                output.push_back(const_cast<planet*>(&elem));
        }
        return output;
    }

    void connect_planets(planet& _planet, std::vector<planet*>& pool)
    {
        if(!(pool.size()>1 && _planet.hasEmptyPortal()))
            return;
        auto hasEmptyPortal = [](const planet& e){ return e.hasEmptyPortal(); };
        auto notSelf = [&_planet](const planet& e){ return _planet!=e; };

        while((pool = filter(pool, hasEmptyPortal)).size()>1 &&
              _planet.hasEmptyPortal())
        {
            auto* other_planet = random_element(filter(pool, notSelf));
            _planet.bindWithPortal(*other_planet);
        }
        for(planet* connected_planet :_planet.portals())
        {
            connect_planets(*connected_planet, pool);
        }
    }

    // generates world with 10..20 planets
    SimpleWorld::SimpleWorld()
    {
        // generate planets without connections
        std::size_t planets_count = std::uniform_int_distribution<std::size_t>(10, 20)(randomGenerator);

        //it is possible that we will need to generate up to 7 more planets
        __galaxy.reserve(planets_count+7);
        for(std::size_t i = 0; i<planets_count; ++i)
        {
            __galaxy.push_back(generatePlanet());
        }

        // connecting planets
        std::vector<planet*> connectivity_parts;

        auto hasEmptyPortal = [](const planet& e){ return e.hasEmptyPortal(); };

        //initialize pool with every planet, because no planets connected yet
        std::vector<planet*> pool = filter(__galaxy, [](const planet&){return true;});
        do
        {
            connectivity_parts.push_back(random_element(pool));

            //pool changes with the connect_planets call
            connect_planets(*(connectivity_parts.back()),  pool);
        }while(pool.size()>1);

        //There is one planet left with unbinded portals
        if(pool.size()==1)
        {
            auto* last_planet = pool.back();
            while(last_planet->hasEmptyPortal())
            {   
                //generate planet with only portal to last_planet
                __galaxy.push_back(generateHelperPlanet(last_planet));

                //[ERROR OCCURED]:
                //last_planet stores the reference to newlly generated planet
                //but after the contrution reference becomes dangling
            }
        }

        // At this parts there should be no empty portals left
        assert(filter(pool, hasEmptyPortal).size()==0);

        // Make graph fully connected if needed
        while (connectivity_parts.size()>1)
        {
            auto* first = connectivity_parts.back();
            connectivity_parts.pop_back();
            auto* second = connectivity_parts.back();
            first->addEmptyPortal();
            second->addEmptyPortal();
            first->bindWithPortal(*second);
        }

        // World is generated at this point

    }
}
