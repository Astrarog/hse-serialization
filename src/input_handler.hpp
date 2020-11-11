#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP
#include <vector>
#include <string>
#include <cstdint>
#include <string_view>

namespace hse {


// Handler to check user input
class input_choises_handler
{
    // Possible choises for user
    std::vector<std::pair<std::string, std::string>> choises;

    // Prefix that will be outputed before choises
    std::string prefix;

    // String that will be outputed before user input every time
    std::string input_invitation;

    // All options as a formated string
    std::string all_options;
public:
    template<typename Str1, typename Str2>
    input_choises_handler(std::vector<std::pair<std::string, std::string>>&& ch, Str1&& pr, Str2&& ii):
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
    // Will print prefix, possible options with their descriptions
    // and input invitation. After that there will be an interration
    // with user input until one of the possible option does not occur.
    std::string_view perfom() const;
};


}
#endif // INPUT_HANDLER_HPP
