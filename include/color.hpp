#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstdint>
#include <iostream>

namespace hse
{

    struct color
    {
        using uint8_t=std::uint8_t;
        using uint32_t=std::uint32_t;
        uint8_t r=0;
        uint8_t g=0;
        uint8_t b=0;
        color(){}
        color(uint32_t c);
        color(uint8_t r, uint8_t g, uint8_t b): r(r), g(g), b(b) {}
        //auto operator<=>(const color&) const = default;
    };

    std::ostream& operator<<(std::ostream& out, const color& rgb);
    std::istream& operator>>(std::istream& out, color& rgb);

    // will be refactored when <=> is possible
    bool operator<(const color& firts, const color& second);
    bool operator==(const color& firts, const color& second);
    bool operator!=(const color& firts, const color& second);
    bool operator<=(const color& firts, const color& second);
    bool operator>(const color& firts, const color& second);
    bool operator>=(const color& firts, const color& second);

    // returns random color
    color generateColor();



}
#endif // COLOR_HPP
