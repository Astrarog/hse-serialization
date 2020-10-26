#include "color.hpp"

#include <sstream>
#include <iostream>
#include <cstdint>
#include <cctype>
#include <iomanip>
#include <stdexcept>
#include <tuple>

namespace hse
{

    color::color(uint32_t c):
        r(c / 256 / 256),
        g((c / 256) % 256),
        b(c % 256)
    {}

    //    bool static checkHex(std::uint8_t x)
    //    {
    //       return (x>='0' && x<='9')||(x>='A' && x<='F');
    //    }

    //    std::uint8_t static parseHex(std::uint8_t f, std::uint8_t s){
    //        f = f>='0'&&f<='9'?f-'0':(f-'A')+10;
    //        s = s>='0'&&s<='9'?s-'0':(s-'A')+10;
    //        return f*16 + s;
    //    }
    std::istream& operator>>(std::istream& input, color& rgb)
    {
        std::string format;
        input >> format;
        std::istringstream in(format);
        bool parse_is_good = true;
        std::uint8_t stratring_char=0;
        parse_is_good = parse_is_good && (in >> stratring_char);
        parse_is_good = parse_is_good && (stratring_char == '#');

        auto checkHex = [](std::uint8_t x)
        {
           return (x>='0' && x<='9')||(x>='A' && x<='F');
        };

        auto parseHex = [](std::uint8_t f, std::uint8_t s)
        {
            f = f>='0'&&f<='9'?f-'0':(f-'A')+10;
            s = s>='0'&&s<='9'?s-'0':(s-'A')+10;
            return f*16 + s;
        };

        auto parseHelper = [&](std::uint8_t& channel)
        {
            std::uint8_t f=0, s=0;
            parse_is_good = parse_is_good && (in >> f);
            f = std::uint8_t(std::toupper(f));
            parse_is_good = parse_is_good && (checkHex(f));

            parse_is_good = parse_is_good && (in >> s);
            s = std::uint8_t(std::toupper(s));
            parse_is_good = parse_is_good && (checkHex(s));

            channel = parseHex(f, s);
        };

        color to_rgb;
        parseHelper(to_rgb.r);
        parseHelper(to_rgb.g);
        parseHelper(to_rgb.b);

        in.peek();
        parse_is_good = parse_is_good && in.eof();

        if (!parse_is_good){
            throw std::logic_error("Wrong color format: "+format);
        }
        rgb = to_rgb;
        return input;
    }
    std::ostream& operator<<(std::ostream& out, const color& rgb)
    {
        out << '#'  << std::hex << std::uppercase << std::right << std::setw(2) << std::setfill('0');
        out << int(rgb.r);
        out << std::setw(2) << std::setfill('0') << int(rgb.g);
        out << std::setw(2) << std::setfill('0') << int(rgb.b);
        out << std::dec;
        return out;
    }

    bool operator<(const color& firts, const color& second)
    {
        return 256*256*firts.r + 256*firts.g + firts.b < 256*256*second.r + 256*second.g + second.b;
    }
    bool operator==(const color& firts, const color& second)
    {
        return firts.r==second.r && firts.g==second.g && firts.b==second.b;
    }
    bool operator!=(const color& firts, const color& second)  { return !(firts == second);}
    bool operator<=(const color& firts, const color& second) { return firts<second || firts==second;}
    bool operator>(const color& firts, const color& second) { return !(firts<=second);}
    bool operator>=(const color& firts, const color& second) { return firts>second || firts==second;}
}
