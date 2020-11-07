#include "world.hpp"
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



//TO DO: The goal and the progress
void playGame(hse::world_base& world)
{
    std::size_t current_idx = world.homeIdx();
    while(!world.isVictory())
    {
        hse::planet& current = world.planetByIdx(current_idx);
        if(world.isHome(current))
        {
            std::cout << "\n"
                      << "Home sweet home! What could be better!\n"
                      << "\n";
        }
        std::cout << world.getPlanetInfo(current) << "\n";
        std::cout << "  [q] Quit" << "\n";

        auto checkTravelAnswer = [&current](std::string& answer, std::size_t& index)
                                  {
                                      std::istringstream line(answer);
                                      bool success = true && (line >> index);
                                      success &= index > 0;
                                      success &= (--index) < current.portals_count();
                                      return success;
                                  };

        std::size_t travel_planet_index;
        std::string travel_answer;

AgainTravel:
        std::cout << "Where should we travel? [1";
        if (current.portals_count()>1)
            std::cout << '-' << current.portals_count();
        std::cout << ", q] ";
        std::getline(std::cin, travel_answer);
        if (!travel_answer.empty() && std::toupper(travel_answer[0]) == 'Q')
        {
            std::exit(0);
        }
        if(!checkTravelAnswer(travel_answer, travel_planet_index))
        {
            goto AgainTravel;
        }
        current_idx = world.Travel(current_idx, travel_planet_index);
        std::cout << delimeter;
    }

}


enum class ANSWER
{
    YES, NO, UNDEF
};

ANSWER checkYNAnswer(std::string& answer)
{
    for(auto& letter: answer)
    {
        letter = std::toupper(letter);
    }
    if (answer == "YES")
        return ANSWER::YES;
    else if(answer == "NO")
        return ANSWER::NO;
    else
        return ANSWER::UNDEF;
}

}


int main()
{

    progress progress;

    std::cout << banner
              << delimeter
              << history << '\n';
    std::string answer;

YesNoAgain:
    std::cout << answerYN;
    std::getline(std::cin, answer);
    auto answ = checkYNAnswer(answer);
    if(answ == ANSWER::YES)
    {
        std::cout << "\n"
                  << "Thank you, Commander! Humanity is in your hands.\n"
                  << delimeter;

//        playGame();
        if(progress.achievedRespect())
        {
            gameModeChoice:
            if(progress.firstAchieve())
            {
                std::cout << infitityAnons;
            }
            std::cout << "\nWhat would you choose?\n\n";
            std::cout << "  [n] Normal mode\n";
            std::cout << "  [i] Infinite mode\n\n";
            std::cout << "  [h] Help\n";
            std::cout << "  [q] Quit\n\n[n,i,h,q] ";

            std::string game_mode_answer;
            std::getline(std::cin, game_mode_answer);
            if(game_mode_answer.empty())
            {
                goto gameModeChoice;
            }
            if (std::toupper(game_mode_answer[0]) == 'Q')
            {
                std::exit(0);
            }
            if (std::toupper(game_mode_answer[0]) == 'I')
            {
                hse::InfiniteWorld world{};
                playGame(world);
            }else{
                if (std::toupper(game_mode_answer[0]) == 'H')
                {
                    std::cout << infitityAnons;
                    goto gameModeChoice;
                }
                if (std::toupper(game_mode_answer[0]) == 'N')
                {
                    std::cout << "The offer is still valid\n";
                    hse::SimpleWorld world{};
                    playGame(world);
                }
            }

        }else
        {
            hse::SimpleWorld world{};
            playGame(world);
        }

        progress.addWin();
        std::cout << delimeter;
        std::cout << "Congratulation comander!!!\n";
        std::cout << "You have successfully complited the mission!\n";
        std::cout << "Nevertheless The Supreme Council have another one.\n";
        std::cout << delimeter;

        goto YesNoAgain;
    }else if(answ == ANSWER::UNDEF)
    {
        goto YesNoAgain;
    }
    std::cout << delimeter << "Fair enough! Goodbye, Commander.\n";

    return 0;
}
