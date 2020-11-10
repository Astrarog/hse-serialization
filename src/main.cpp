#include "world.hpp"
#include "input_handler.hpp"

#include <iostream>
#include <string>
#include <sstream>

namespace  {

constexpr const char* banner =
R"(__________                    .__          __                 __                        .__       .___)""\n"
R"(\______   \ ___________  _____|__| _______/  |_  ____   _____/  |_  __  _  _____________|  |    __| _/)""\n"
R"( |     ___// __ \_  __ \/  ___/  |/  ___/\   __\/ __ \ /    \   __\ \ \/ \/ /  _ \_  __ \  |   / __ | )""\n"
R"( |    |   \  ___/|  | \/\___ \|  |\___ \  |  | \  ___/|   |  \  |    \     (  <_> )  | \/  |__/ /_/ | )""\n"
R"( |____|    \___  >__|  /____  >__/____  > |__|  \___  >___|  /__|     \/\_/ \____/|__|  |____/\____ | )""\n"
R"(               \/           \/        \/            \/     \/                                      \/ )""\n";

constexpr const char* delimeter =
R"(======================================================================================================)""\n";
constexpr const char* history =
R"(    Hello, Commander!                                                                                 )""\n"
R"(    Humanity faces horrible times. Overpopulation is a major porblem today, so The Supreme Council Z  )""\n"
R"(has decided to deploy the project with a code name "Persistent world" and appoint you as the head of  )""\n"
R"(this mission.                                                                                         )""\n"
R"(    Your task is to explore the galaxy and found all planets available for colonization. You will be  )""\n"
R"(provided with the best space explorers on our planet.                                                 )""\n";

constexpr const char * infitityAnons =
        "According to The Supreme Council's report, you have shown excellent services.\n"
        "In order to show the respect to you job, you are now available to investigae \n"
        "the sector XZY-931 with all of its infinite planets. \n";

constexpr const char* answerYN =  R"(Do you accept this mission? [Yes/No] )";

class progress
{
public:
    bool achievedRespect() { return !(__games_won < 0); }
    bool firstAchieve(){bool answ = __first_achieved; __first_achieved =false; return answ; }
    void addWin() {++__games_won;}
private:
    std::size_t __games_won = 0;
    bool __first_achieved = true;
};

[[noreturn]]
void exit_commandor()
{
    std::cout << "Fair enough! Goodbye, Commander.\n";
    std::exit(0);
}


//TO DO: The goal and the progress
void playGame(hse::world_base& world)
{
    std::size_t current_idx = world.homeIdx();
    while(!world.isVictory())
    {
        hse::planet& current = world.planetByIdx(current_idx);

        hse::input_choises_handler travel_input
                (world.getPlanetChoises(current), world.getPlanetPrefix(current), "Where should we travel?");

        std::string answer = std::string(travel_input.perfom());
        std::size_t next_idx;
        if (answer=="q")
        {
            exit_commandor();
        }
        else
        {
            std::istringstream in(answer);
            in >> next_idx;
            --next_idx;
        }

        current_idx = world.Travel(current_idx, next_idx);
        std::cout << delimeter;
    }

    std::cout << '\n' << delimeter;
    std::cout << "\nCongratulation comander!!!\n";
    std::cout << "\nYou have successfully complited the mission!\n";
    std::cout << "\nNevertheless The Supreme Council have another one.\n\n";
}

}

int main()
{
    progress progress;

    std::cout << banner
              << delimeter
              << history << '\n';

    hse::input_choises_handler main_game_input(
    {{"yes", "Accept the mission"},
     {"no" , "Decline the mission"},
     {"q" , "Quit"}},
                delimeter, answerYN);

    std::string answer;
    while((answer = main_game_input.perfom())=="yes")
    {
        std::cout << "\n"
                  << "Thank you, Commander! Humanity is in your hands.\n"
                  << delimeter;

        std::string mode = "n";
        if(progress.achievedRespect())
        {
            if(progress.firstAchieve())
            {
                std::cout << infitityAnons;
            }
            hse::input_choises_handler mode_input(
            {{"n", "Normal mode"},
             {"i" , "Infinite mode"},
             {"h" , "Help"},
             {"q" , "Quit"}},
                        "", "");
            mode = mode_input.perfom();

        }
        if(mode == "n")
        {
            hse::SimpleWorld world{};
            playGame(world);
            progress.addWin();
        }
        else if (mode == "i")
        {
            hse::InfiniteWorld world{};
            playGame(world);
            progress.addWin();
        } else if(mode == "h")
        {
            std::cout << infitityAnons;
        }
        else if(mode == "q")
        {
            exit_commandor();
        }
    }

    exit_commandor();
}


