#include "world.hpp"
#include <iostream>
#include <string>
#include <sstream>

static std::string_view banner =
R"(__________                    .__          __                 __                        .__       .___)""\n"
R"(\______   \ ___________  _____|__| _______/  |_  ____   _____/  |_  __  _  _____________|  |    __| _/)""\n"
R"( |     ___// __ \_  __ \/  ___/  |/  ___/\   __\/ __ \ /    \   __\ \ \/ \/ /  _ \_  __ \  |   / __ | )""\n"
R"( |    |   \  ___/|  | \/\___ \|  |\___ \  |  | \  ___/|   |  \  |    \     (  <_> )  | \/  |__/ /_/ | )""\n"
R"( |____|    \___  >__|  /____  >__/____  > |__|  \___  >___|  /__|     \/\_/ \____/|__|  |____/\____ | )""\n"
R"(               \/           \/        \/            \/     \/                                      \/ )""\n";

static std::string_view delimeter =
R"(======================================================================================================)""\n";
std::string history =
R"(    Hello, Commander!                                                                                 )""\n"
R"(    Humanity faces horrible times. Overpopulation is a major porblem today, so The Supreme Council S  )""\n"
R"(has decided to deploy the project with a code name "Persistent world" and appoint you as the head of  )""\n"
R"(this mission.                                                                                         )""\n"
R"(    Your task is to explore the galaxy and found all planets available for colonization. You will be  )""\n"
R"(provided with the best space explorers on our planet.                                                 )""\n";

static std::string_view answerYN =  R"(Do you accept this mission? [Yes/No] )";

//class SaveSlotConfig
//{
//    std::size_t __games_won = 0;

//private:
//};


//TO DO: The goal and the progress
void playInviniteGame(hse::world_base& world)
{
    hse::planet* current = world.home();
    while(!world.isVictory())
    {
        if(world.isHome(*current))
        {
            std::cout << "\n"
                      << "Home sweet home! What could be better!\n"
                      << "\n";
        }
        std::cout << *current << "\n";
        std::cout << "  [q] Quit" << "\n";

        auto checkTravelAnswer = [&current](std::string& answer, std::size_t& index)
                                  {
                                      std::istringstream line(answer);
                                      bool success = true && (line >> index);
                                      success &= index > 0;
                                      success &= (--index) < current->portals_count();
                                      return success;
                                  };

        std::size_t travel_planet_index;
        std::string travel_answer;

AgainTravel:
        std::cout << "Where should we travel? [1";
        if (current->portals_count()>1)
            std::cout << '-' << current->portals_count();
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
        current = world.Travel(current, travel_planet_index);
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

int main()
{


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
        hse::SimpleWorld world{};
//        hse::InfiniteWorld world{};
        playInviniteGame(world);

        std::cout << delimeter << delimeter << delimeter;
        std::cout << "Congratulation comander!!!\n";
        std::cout << "You have successfully complited the mission!\n";
        std::cout << "Nevertheless The Supreme Council have another one.\n";
        goto YesNoAgain;
    }else if(answ == ANSWER::UNDEF)
    {
        goto YesNoAgain;
    }
    std::cout << delimeter << "Fair enough! Goodbye, Commander.\n";

    return 0;
}
