#include "world.hpp"
#include "random.hpp"
#include "input_handler.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <ios>
#include <filesystem>
#include <cassert>
#include <random>

#include <nop/serializer.h>
#include <nop/utility/die.h>
#include <nop/utility/stream_reader.h>
#include <nop/utility/stream_writer.h>

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

constexpr const char* answerYN =  R"(Do you accept this mission?)";

constexpr const char* saveFileName =  "save.prof";

namespace fs = std::filesystem;


class progress
{
public:
    bool achievedRespect() { return !(__games_won < 0); }
    bool firstAchieve(){bool answ = __first_achieved; __first_achieved =false; return answ; }
    void addWin() {++__games_won;}
private:
    std::size_t __games_won = 0;
    bool __first_achieved = true;
    NOP_STRUCTURE(progress, __games_won, __first_achieved);
};


progress global_progress{};


[[noreturn]]
void exitCommandor()
{
    std::cout << "Fair enough! Goodbye, Commander.\n";
    std::exit(0);
}

// Sends fatal errors to std::cerr.
auto Die() { return nop::Die(std::cerr); }

void deleteSaveFile()
{
    if(fs::exists(saveFileName))
    {
//        fs::create_directories(saveFileName);
        bool success = fs::remove(saveFileName);
        assert(success);
    }
}

void saveGame(hse::world world)
{
    using Writer = nop::StreamWriter<std::stringstream>;
    nop::Serializer<Writer> serializer;

    serializer.Write(global_progress) || Die();
    serializer.Write(world) || Die();

    std::string data = serializer.writer().stream().str();
    std::ofstream file(saveFileName);
    file << data;
}

hse::world loadGame()
{
    std::string data_raw;
    std::ifstream file(saveFileName, std::ios::binary | std::ios::out | std::ios::app);
    std::string line;
    while ( getline (file,line) )
    {
      data_raw += line+'\n';
    }

    std::stringstream data_stream(data_raw);
    using Reader = nop::StreamReader<std::stringstream>;
    nop::Deserializer<Reader> deserializer(std::move(data_stream));

    deserializer.Read(&global_progress) || Die();

    hse::world data;
    deserializer.Read(&data) || Die();

    return data;
}

void playGame(hse::world& world)
{
    std::size_t current_idx = world.homeIdx();
    while(!(world.isVictory()))
    {
        hse::planet& current = world.planetByIdx(current_idx);

        hse::input_choises_handler travel_input
                (world.getPlanetChoises(current), delimeter+world.getPlanetPrefix(current), "Where should we travel?");

        std::string answer = std::string(travel_input.perform());
        std::size_t next_idx;
        if (answer=="q")
        {
            hse::input_choises_handler save_input(
            {{"yes", "Save the progress"},
             {"no" , "Discard the progress"}},
             "Would you like to save you progress?", "Save?");
            std::string_view answer = save_input.perform();
            if(answer == "yes")
            {
                saveGame(world);
            }
            exitCommandor();
        }
        else
        {
            std::istringstream in(answer);
            in >> next_idx;
            --next_idx;
        }

        current_idx = world.Travel(current_idx, next_idx);
    }

    std::cout << '\n' << delimeter;
    std::cout << "\nCongratulation comander!!!\n";
    std::cout << "\nYou have successfully complited the mission!\n";
    std::cout << "\nNevertheless The Supreme Council have another one.\n\n";

    deleteSaveFile();

}

} // namespace

int main()
{
    std::cout << banner
              << delimeter
              << history << '\n';

    hse::input_choises_handler main_game_input(
    {{"yes", "Accept the mission"},
     {"no" , "Decline the mission"},
     {"q" , "Quit"}},
                delimeter, answerYN);

    std::string_view answer;
    while((answer = main_game_input.perform())=="yes")
    {
        std::cout << "\n"
                  << "Thank you, Commander! Humanity is in your hands.\n"
                  << delimeter;


        hse::world world{};

        std::string load="no";
        if(fs::exists(saveFileName))
        {

            hse::input_choises_handler load_input(
            {{"yes", "Load the mission"},
             {"no" , "Delete the progress"},
             {"q" , "Quit"}},
                        "We have found you previous mission.", "Would you like to load?");
            load = load_input.perform();
            if(load == "yes")
            {
                world = loadGame();
            }
            else if (load == "no")
            {
                deleteSaveFile();
            }
            else
            {
                exitCommandor();
            }
        }
        if(load=="no")
        {
            std::string mode = "n";
            if(global_progress.achievedRespect())
            {
                if(global_progress.firstAchieve())
                {
                    std::cout << infitityAnons;
                }
                hse::input_choises_handler mode_input(
                {{"n", "Normal mode"},
                 {"i" , "Infinite mode"},
                 {"h" , "Help"},
                 {"q" , "Quit"}},
                            "", "");
                mode = mode_input.perform();

            }
            if(mode == "h")
            {
                std::cout << infitityAnons;
            }
            else if(mode == "q")
            {
                exitCommandor();
            }else if(mode == "n")
            {
                std::size_t world_size = std::uniform_int_distribution<std::size_t>(10, 20)(hse::randomGenerator);
                world.generatePlanets(world_size);
                world.connectCurrnet();
                world.makeFinit();
            }
        }
        playGame(world);
        global_progress.addWin();
    }

    exitCommandor();
}


