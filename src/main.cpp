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
R"(======================================================================================================)""\n"
R"(||                                                                                                  ||)""\n"
R"(||    Hello, Commander!                                                                             ||)""\n"
R"(||    Humanity faces horrible times. Overpopulation is a major porblem today, so The Supreme Council||)""\n"
R"(||has decided to deploy the project with a code name "Persistent world" and appoint you as the head ||)""\n"
R"(||of this mission.                                                                                  ||)""\n"
R"(||    Your task is to explore the galaxy and found all planets available for colonization. You will ||)""\n"
R"(||be provided with the best space explorers on our planet.                                          ||)""\n"
R"(||                                                                                                  ||)""\n"
R"(======================================================================================================)""\n";

constexpr const char* thankYou =
R"(======================================================================================================)""\n"
R"(||                                                                                                  ||)""\n"
R"(||                           Thank you, Commander! Humanity is in your hands.                       ||)""\n"
R"(||                                                                                                  ||)""\n"
R"(======================================================================================================)""\n";


constexpr const char * infitityAnons =        
R"(======================================================================================================)""\n"
R"(||                                                                                                  ||)""\n"
R"(||         According to The Supreme Council's report, you have shown excellent services.            ||)""\n"
R"(||         In order to show the respect to you job, you are now available to investigae             ||)""\n"
R"(||         the mystery sectors with all of their seeming infinity. Can you find the end?            ||)""\n"
R"(||                                                                                                  ||)""\n"
R"(======================================================================================================)""\n";

constexpr const char * congrats =
R"(======================================================================================================)""\n"
R"(||    _________                                     __        .__          __  .__                  ||)""\n"
R"(||    \_   ___ \  ____   ____    ________________ _/  |_ __ __|  | _____ _/  |_|__| ____   ____     ||)""\n"
R"(||    /    \  \/ /  _ \ /    \  / ___\_  __ \__  \\   __\  |  \  | \__  \\   __\  |/  _ \ /    \    ||)""\n"
R"(||    \     \___(  <_> )   |  \/ /_/  >  | \// __ \|  | |  |  /  |__/ __ \|  | |  (  <_> )   |  \   ||)""\n"
R"(||     \______  /\____/|___|  /\___  /|__|  (____  /__| |____/|____(____  /__| |__|\____/|___|  /   ||)""\n"
R"(||            \/            \//_____/            \/                     \/                    \/    ||)""\n"
R"(||                                                                .___           ._.                ||)""\n"
R"(||                  ____  ____   _____   _____ _____    ____    __| _/___________| |                ||)""\n"
R"(||                _/ ___\/  _ \ /     \ /     \\__  \  /    \  / __ |/  _ \_  __ \ |                ||)""\n"
R"(||                \  \__(  <_> )  Y Y  \  Y Y  \/ __ \|   |  \/ /_/ (  <_> )  | \/\|                ||)""\n"
R"(||                 \___  >____/|__|_|  /__|_|  (____  /___|  /\____ |\____/|__|   __                ||)""\n"
R"(||                     \/            \/      \/     \/     \/      \/             \/                ||)""\n"
R"(||                                                                                                  ||)""\n"
R"(======================================================================================================)""\n"
R"(||                                                                                                  ||)""\n"
R"(||                            You have successfully complited the mission!                          ||)""\n"
R"(||                       Nevertheless The Supreme Council have another one for you.                 ||)""\n"
R"(||                                                                                                  ||)""\n"
R"(======================================================================================================)""\n";



constexpr const char* saveFileNameWorld =  "world-save.prof";

constexpr const char* saveFileNameProgress = "progress-save.prof";


namespace fs = std::filesystem;


class progress
{
public:
    bool achievedRespect() { return !(games_won_ < 1); }
    bool firstAchieve(){bool answ = first_achieved_; first_achieved_ =false; return answ; }
    void addWin() {++games_won_;}
private:
    std::size_t games_won_ = 0;
    bool first_achieved_ = true;
    NOP_STRUCTURE(progress, games_won_, first_achieved_);
};


progress global_progress{};

// Sends fatal errors to std::cerr.
auto Die() { return nop::Die(std::cerr); }

void deleteWorldSaveFile()
{
    if(fs::exists(saveFileNameWorld))
    {
        bool success = fs::remove(saveFileNameWorld);
        assert(success);
    }
}

void saveProgress()
{
    using Writer = nop::StreamWriter<std::stringstream>;
    nop::Serializer<Writer> serializer;

    serializer.Write(global_progress) || Die();

    std::string data = serializer.writer().stream().str();
    std::ofstream file(saveFileNameProgress);
    file << data;
}

void saveGame(hse::world world)
{
    using Writer = nop::StreamWriter<std::stringstream>;
    nop::Serializer<Writer> serializer;

    serializer.Write(world) || Die();

    std::string data = serializer.writer().stream().str();
    std::ofstream file(saveFileNameWorld);
    file << data;
}

void loadProgress()
{
    std::string data_raw;
    std::ifstream file(saveFileNameProgress, std::ios::binary | std::ios::in | std::ios::app);
    std::string line;
    while ( getline (file,line) )
    {
      data_raw += line+'\n';
    }

    std::stringstream data_stream(data_raw);
    using Reader = nop::StreamReader<std::stringstream>;
    nop::Deserializer<Reader> deserializer(std::move(data_stream));

    deserializer.Read(&global_progress) || Die();
}

hse::world loadGame()
{
    std::string data_raw;
    std::ifstream file(saveFileNameWorld, std::ios::binary | std::ios::in | std::ios::app);
    std::string line;
    while ( getline (file,line) )
    {
      data_raw += line+'\n';
    }

    std::stringstream data_stream(data_raw);
    using Reader = nop::StreamReader<std::stringstream>;
    nop::Deserializer<Reader> deserializer(std::move(data_stream));

    hse::world data;
    deserializer.Read(&data) || Die();

    return data;
}

[[noreturn]]
void exitCommandor()
{
    saveProgress();
    std::cout << "Fair enough! Goodbye, Commander.\n";
    std::exit(0);
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
             "\nWould you like to save you progress?", "Save?");
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

    std::cout << congrats;

    deleteWorldSaveFile();

}

} // namespace

int main()
{
    std::cout << banner
              << history ;

    hse::input_choises_handler main_game_input(
    {{"yes", "Accept the mission"},
     {"no" , "Decline the mission"},
     {"q" , "Quit"}},
                "", "Do you accept the mission?");

    std::string_view answer;
    while((answer = main_game_input.perform())=="yes")
    {
        if(fs::exists(saveFileNameProgress))
        {
            loadProgress();
        }
        std::cout << thankYou;

        hse::world world{};

        std::string load="no";
        if(fs::exists(saveFileNameWorld))
        {

            hse::input_choises_handler load_input(
            {{"yes", "Load the mission"},
             {"no" , "Delete the progress"},
             {"q" , "Quit"}},
                        "\nWe have found you previous mission.\n", "Would you like to load?");
            load = load_input.perform();
            if(load == "yes")
            {
                world = loadGame();
            }
            else if (load == "no")
            {
                deleteWorldSaveFile();
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
                            "", "Choose game mode.");
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


