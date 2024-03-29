#include "input_handler.hpp"
#include <cstdint>
#include <iostream>
#include <string>
#include <algorithm>
#include <string_view>

namespace hse {


std::string_view input_choises_handler::perform() const
{
    std::cout << prefix << '\n';

    for (const auto& [opt, description] : choises)
    {
        std::cout << "  [" << opt[0] << "] "<< description << '\n';
    }
    std::cout << '\n';
    while(true)
    {
        std::cout << input_invitation << ' ' << all_options << ' ';

        std::string answer="";
        std::getline(std::cin, answer);

        if(!(std::cin) || answer=="")
        {
            throw std::runtime_error("input error");
        }

        for (const auto& [opt, _] : choises)
        {
            if (opt.rfind(answer, 0) == 0)
                return opt;
        }

    }
}

}
