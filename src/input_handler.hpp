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
    input_choises_handler(const std::vector<std::pair<std::string, std::string>>& ch,
                          const std::string& pr,
                          const std::string& ii);

    // Will print prefix, possible options with their descriptions
    // and input invitation. After that there will be an interration
    // with user input until one of the possible option does not occur.
    std::string_view perfom() const;
};


}
#endif // INPUT_HANDLER_HPP
