#include "color.hpp"
#include "planet.hpp"

#include <iostream>

int main()
{
    hse::color c(1);
    std::cout << c;
    hse::planet("aaa", c, 1);
//    hse::world world;
    return 0;
}
