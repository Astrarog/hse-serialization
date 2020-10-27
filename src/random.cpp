#include "random.hpp"
#include "color.hpp"
#include "planet.hpp"

#include <random>
#include <string>
#include <cstdint>

namespace hse
{
    //prng
    std::mt19937 randomGenerator{std::random_device{}()};

    // returns random string with lenght from 5 to 10 symbols
    extern std::string generateString()
    {
        static std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        static std::string numbers = "0123456789";

        using udistr_t = std::uniform_int_distribution<std::string::size_type>;

        static udistr_t pick_letter(0, letters.size() - 1);
        static udistr_t pick_number(0, numbers.size() - 1);
        static udistr_t pick_lenght(4, 9);

        std::size_t length = pick_lenght(randomGenerator);
        std::string s;
        s.reserve(length);

        for(std::size_t i = 0; i<length/2; ++i)
        {
            s += letters[pick_letter(randomGenerator)];
        }
        s+='-';
        for(std::size_t i = length/2; i<length; ++i)
        {
            s += numbers[pick_number(randomGenerator)];
        }

        return s;
    }


    // returns random color
    extern color generateColor()
    {
       static std::uniform_int_distribution<std::uint8_t> pick_channel(0, 255);
       return color(pick_channel(randomGenerator),
                    pick_channel(randomGenerator),
                    pick_channel(randomGenerator));
    }

    //returns random valid planet type
    extern planet::TYPE generatePlanetType()
    {
        static std::uniform_int_distribution<std::size_t> pick_type(static_cast<std::size_t>(planet::TYPE::EARTH),
                                                                    static_cast<std::size_t>(planet::TYPE::DEATH));
        return static_cast<planet::TYPE>(pick_type(randomGenerator));
    }

    //returns random planet with 1..7 empty portals
    extern planet generatePlanet()
    {
        static std::uniform_int_distribution<std::size_t> pick_portals_count(1, 7);
        return planet(generateString(),
                      generateColor(),
                      pick_portals_count(randomGenerator),
                      generatePlanetType());
    }

    //returns random planet with only 1 portal
    extern planet generateHelperPlanet()
    {
        return planet(generateString(),
                      generateColor(),
                      1,
                      generatePlanetType());
    }

}
