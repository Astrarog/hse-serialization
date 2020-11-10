#include "input_handler.hpp"
#include <cstdint>
#include <iostream>
#include <string>
#include <algorithm>
#include <string_view>

namespace hse {

input_choises_handler::input_choises_handler(const std::vector<std::pair<std::string, std::string>>& ch,
                      const std::string& pr,
                      const std::string& ii):
        choises(ch), prefix(pr), input_invitation(ii)
{
    all_options = "[";
    bool first = true;
    for (const auto& [opt, _] : choises)
    {
        if(!first)
        {
            all_options+=", ";
        }
        all_options+=opt;
        first = false;
    }
    all_options += "]";
}


std::string_view input_choises_handler::perfom() const
{
    std::cout << prefix << '\n' << '\n';

    for (const auto& [opt, description] : choises)
    {
        std::cout << "  [" << opt[0] << "] "<< description << '\n';
    }
    std::cout << '\n';
    while(true)
    {
        std::cout << input_invitation << ' ' << all_options << ' ';

        std::string answer;
        std::getline(std::cin, answer);

        if(!(std::cin))
        {
            throw std::runtime_error("input error");
        }

        for (const auto& [opt, _] : choises)
        {
            auto pos = std::mismatch(answer.begin(), answer.end(), opt.begin());
            if(pos.first == answer.end())
                return opt;
        }

    }
}

}
