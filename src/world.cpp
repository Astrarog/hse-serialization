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

    std::string world::getPlanetPrefix(hse::planet& _planet)
    {
        std::ostringstream out;
        out << _planet.getPlanetImage();
        if(isHome(_planet))
        {
            out << "\n"
                << "Home sweet home! What could be better!\n"
                << "\n";
        }
        else if(_planet.showNewPlanet())
        {
            out << "Comader! We have found a new planet!\n";
        }
        out << "NAME : " <<_planet.name()  << "\n";
        out << "COLOR: " <<_planet.Color() << "\n"
                                             << "\n";
        out << "\n  [Our intelligence reports that we have found " << CountVisited() << " out of " << WorldSize() << "]\n\n";
        out << "Possible next hops:\n";

        return out.str();
    }

    std::vector<std::pair<std::string, std::string>> world::getPlanetChoises(hse::planet& _planet) const
    {
        std::vector<std::pair<std::string, std::string>> choises;
        std::size_t index=1;
        for (std::int32_t next_idx: _planet.portals())
        {
            std::string opt, desc;

            std::ostringstream os; os << index++; opt=os.str();

            if(next_idx == -1 || !galaxy_[next_idx].isVisited())
            {
                desc = "(UNKNOWN)" ;
            }else
            {
                desc = galaxy_[next_idx].name();
            }

            choises.push_back({opt, desc});
        }
        choises.push_back({"q", "Quit"});
        return choises;
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

    void connectPlanets(std::vector<planet>& data, std::int32_t planet_idx, std::vector<std::int32_t>& pool, std::size_t& count_unbinded)
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
            count_unbinded -= 2; // cause portals on both sides;
        }
        for(std::int32_t connected_planet_idx :_planet.portals())
        {
            connectPlanets(data, connected_planet_idx, pool, count_unbinded);
        }
    }

    void world::connectCurrnet()
    {
        std::vector<std::int32_t> connectivity_parts;

        //initialize pool with every planet, because no planets connected yet
        std::vector<std::int32_t> pool = filter(galaxy_, [](const planet&){return true;});
        do
        {
            connectivity_parts.push_back(random_element_idx(pool));

            //pool changes with the connectPlanets call
            connectPlanets(galaxy_, connectivity_parts.back(),  pool, count_unbinded_portals_);
        }while(pool.size()>1);

        // Make graph fully connected
        while (connectivity_parts.size()>1)
        {
            std::int32_t first_idx = connectivity_parts.back();
            planet& first = galaxy_[first_idx];
            connectivity_parts.pop_back();

            std::int32_t second_idx = connectivity_parts.back();
            planet& second = galaxy_[second_idx];

            first.addEmptyPortal();
            second.addEmptyPortal();

            bindWithPortal(first, first_idx,
                           second, second_idx);
        }
    }

    void world::makeFinit()
    {
        auto hasEmptyPortal = [](const planet& e){ return e.hasEmptyPortal(); };
        std::vector<std::int32_t> pool = filter(galaxy_, hasEmptyPortal);

        std::int32_t last_planet_idx = pool.back();
        while(galaxy_[last_planet_idx].hasEmptyPortal())
        {
            //generate planet with only portal to last_planet
            galaxy_.push_back(generateHelperPlanet());

            bindWithPortal(galaxy_[last_planet_idx], last_planet_idx,
                        galaxy_.back(), galaxy_.size()-1);
            --count_unbinded_portals_;
        }


        // At this parts there should be no empty portals left
        assert(filter(galaxy_, pool, hasEmptyPortal).size()==0);
        assert(count_unbinded_portals_==0);
    }

    void world::generatePlanets(std::size_t size)
    {
        for(std::size_t i = 0; i<size; ++i)
        {
            galaxy_.push_back(generatePlanet());
            count_unbinded_portals_ += galaxy_.back().emptyPortalsCount();
        }
    }

    world::world(std::size_t size)
    {
        // generate planets without connections
        this->generatePlanets(size);
        // connecting planets

        galaxy_.front().markVisited();
        galaxy_.front().showNewPlanet();
    }

    world::world()
    {
        *this = world(1);
    }

    std::int32_t world::Travel(std::int32_t current_idx, std::size_t to_idx)
    {
        std::int32_t next_idx = galaxy_[current_idx].Travel(to_idx);
        if(next_idx == -1)
        {
            --count_unbinded_portals_;
            galaxy_.push_back(generatePlanet());

            planet& current = galaxy_[current_idx];
            planet& new_planet = galaxy_.back();
            next_idx = galaxy_.size()-1;
            bindWithPortal(current, current_idx,
                        new_planet, next_idx );

            count_unbinded_portals_+=new_planet.emptyPortalsCount();
        }
        planet& next = galaxy_[next_idx];
        if(!(next.isVisited()))
        {
            ++count_visited_;
            next.markVisited();
        }
        return next_idx;
    }
}
