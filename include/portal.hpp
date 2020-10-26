#ifndef PORTAL_HPP
#define PORTAL_HPP
#include "planet.hpp"

namespace hse
{
    struct portal
    {
        planet* from;
        planet* to;
    };
}

#endif // PORTAL_HPP
