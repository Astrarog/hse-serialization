#include "world.hpp"
#include "random.hpp"

#include <random>
#include <cstdint>
#include <list>
#include <functional>

namespace hse
{

    planet* random_element(const std::list<planet>& data)
    {
        assert(data.size()>0);
        std::uniform_int_distribution<std::size_t> pick_elem(0, data.size() - 1);
        return const_cast<planet*>(&(*(next(data.begin(), pick_elem(randomGenerator)))));
    }

    planet* random_element(const std::list<planet*>& data)
    {
        std::uniform_int_distribution<std::size_t> pick_elem(0, data.size() - 1);
        return const_cast<planet*>(*(next(data.begin(), pick_elem(randomGenerator))));
    }

    std::list<planet*> filter(const std::list<planet*>& data, std::function<bool(const planet &)> predicate)
    {
        std::list<planet*> output;
        for (auto& elem : data)
        {
            if (predicate(*elem))
                output.push_back(const_cast<planet*>(elem));
        }
        return output;
    }
    std::list<planet*> filter(const std::list<planet>& data, std::function<bool(const planet &)> predicate)
    {
        std::list<planet*> output;
        for (auto& elem : data)
        {
            if (predicate(elem))
                output.push_back(const_cast<planet*>(&elem));
        }
        return output;
    }

    void connect_planets(planet& _planet, std::list<planet*>& pool)
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

        for(std::size_t i = 0; i<planets_count; ++i)
        {
            __galaxy.push_back(generatePlanet());
        }

        // connecting planets
        std::list<planet*> connectivity_parts;

        auto hasEmptyPortal = [](const planet& e){ return e.hasEmptyPortal(); };

        //initialize pool with every planet, because no planets connected yet
        std::list<planet*> pool = filter(__galaxy, [](const planet&){return true;});
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
                __galaxy.push_back(generateHelperPlanet());
                last_planet->bindWithPortal(__galaxy.back());
            }
        }

        // At this parts there should be no empty portals left
        assert(filter(pool, hasEmptyPortal).size()==0);

        // Make graph fully connected if needed
        while (connectivity_parts.size()>1)
        {
            planet* first = connectivity_parts.back();
            connectivity_parts.pop_back();
            planet* second = connectivity_parts.back();
            first->addEmptyPortal();
            second->addEmptyPortal();
            first->bindWithPortal(*second);
        }
        // World is generated at this point
        __galaxy.front().markVisited();
        __galaxy.front().showNewPlanet();
    }

    planet* SimpleWorld::Travel(planet* _planet, std::size_t idx)
    {
        planet* next = _planet->Travel(idx);
        if(!(next->isVisited()))
        {
            ++__count_visited;
            next->markVisited();
        }
        return next;
    }



    InfiniteWorld::InfiniteWorld()
    {
        __galaxy.push_back(generatePlanet());
        __galaxy.front().markVisited();
        __galaxy.front().showNewPlanet();
    }

    planet* InfiniteWorld::Travel(planet* _planet, std::size_t idx)
    {
        planet* next = _planet->Travel(idx);
        if(next == nullptr)
        {
            __galaxy.push_back(generatePlanet());
            planet& new_planet = __galaxy.back();
            _planet->bindWithPortal(new_planet, idx);
            next = &new_planet;
            next -> markVisited();
        }
        return next;
    }
}
