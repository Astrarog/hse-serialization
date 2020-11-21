#include "planet.hpp"
#include "world.hpp"

#include <string>
#include <ios>
#include <sstream>
#include <fstream>
#include <queue>

#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>

#include <nop/serializer.h>
#include <nop/utility/die.h>
#include <nop/utility/stream_reader.h>
#include <nop/utility/stream_writer.h>


// Sends fatal errors to std::cerr.
auto Die() { return nop::Die(std::cerr); }

hse::world generateConnected(std::size_t size)
{
    hse::world world;
    std::queue<std::pair<std::size_t, std::size_t>> q;
    for(std::size_t i=0; i<world.home().portalsCount(); ++i)
    {
        q.push({world.homeIdx(), i});
    }
    bool enough = false;
    while(world.WorldSize()<size)
    {
        std::pair<std::size_t, std::size_t> fr = q.front();
        std::size_t idx_in_galaxy=fr.first, next_planet_idx= fr.second;
        idx_in_galaxy = world.Travel(idx_in_galaxy, next_planet_idx);
        hse::planet& current = world.planetByIdx(idx_in_galaxy);

        q.pop();

        if(!enough)
        {
            for (std::size_t i=1; i<current.portalsCount() ;++i)
            {
                q.push({idx_in_galaxy, i});
            }
            if(q.size()==0)
            {
                world.addEmptyPortal(idx_in_galaxy);
                std::size_t i = current.portalsCount()-1;
                q.push({idx_in_galaxy, i});
            }
            enough = ((size - world.WorldSize()) < q.size());
        }

    }
    return world;
}



TEST_CASE("Serialization test of raw world", "[serialization][raw]") {
    BENCHMARK_ADVANCED("Raw wolrd with 2 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world(2);

        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".raw";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Raw wolrd with 4 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world(4);

        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".raw";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Raw wolrd with 8 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world(8);

        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".raw";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Raw wolrd with 16 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world(16);

        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".raw";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Raw wolrd with 32 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world(32);

        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".raw";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Raw wolrd with 64 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world(64);

        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".raw";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Raw wolrd with 128 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world(128);

        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".raw";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Raw wolrd with 256 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world(256);

        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".raw";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Raw wolrd with 512 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world(512);

        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".raw";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Raw wolrd with 1024 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world(1024);

        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".raw";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Raw wolrd with 2048 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world(2048);

        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".raw";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Raw wolrd with 4096 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world(4096);

        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".raw";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Raw wolrd with 8192 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world(8192);

        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".raw";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Raw wolrd with 16384 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world(16384);

        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".raw";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Raw wolrd with 32768 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world(32768);

        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".raw";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Raw wolrd with 65536 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world(65536);

        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".raw";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Raw wolrd with 131072 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world(131072);

        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".raw";
        std::ofstream file(ss.str());
        file << data;
    };

}

TEST_CASE("Serialization test of connected world", "[serialization][connected]") {
    BENCHMARK_ADVANCED("Connected wolrd with 2 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world = generateConnected(2);
        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".con";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Connected wolrd with 4 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world = generateConnected(4);
        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".con";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Connected wolrd with 8 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world = generateConnected(8);
        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".con";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Connected wolrd with 16 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world = generateConnected(16);
        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".con";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Connected wolrd with 32 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world = generateConnected(32);
        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".con";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Connected wolrd with 64 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world = generateConnected(64);
        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".con";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Connected wolrd with 128 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world = generateConnected(128);
        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".con";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Connected wolrd with 256 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world = generateConnected(256);
        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".con";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Connected wolrd with 512 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world = generateConnected(512);
        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".con";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Connected wolrd with 1024 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world = generateConnected(1024);
        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".con";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Connected wolrd with 2048 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world = generateConnected(2048);
        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".con";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Connected wolrd with 4096 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world = generateConnected(4096);
        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".con";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Connected wolrd with 8192 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world = generateConnected(8192);
        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".con";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Connected wolrd with 16384 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world = generateConnected(16384);
        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".con";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Connected wolrd with 32768 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world = generateConnected(32768);
        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".con";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Connected wolrd with 65536 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world = generateConnected(65536);
        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".con";
        std::ofstream file(ss.str());
        file << data;
    };

    BENCHMARK_ADVANCED("Connected wolrd with 131072 planets")(Catch::Benchmark::Chronometer meter) {
        hse::world world = generateConnected(131072);
        using Writer = nop::StreamWriter<std::stringstream>;
        nop::Serializer<Writer> serializer;

        meter.measure([&]
        {
            serializer.Write(world) || Die();
        });

        std::string data = serializer.writer().stream().str();

        std::stringstream ss;
        ss << world.WorldSize() << ".con";
        std::ofstream file(ss.str());
        file << data;
    };
}

TEST_CASE("Deserialization test of raw world", "[deserialization][raw]") {

    BENCHMARK_ADVANCED("Raw wolrd with 2 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 2;
        std::stringstream ss;
        ss << world_size << ".raw";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 4 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 4;
        std::stringstream ss;
        ss << world_size << ".raw";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 8 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 8;
        std::stringstream ss;
        ss << world_size << ".raw";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 16 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 16;
        std::stringstream ss;
        ss << world_size << ".raw";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 32 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 32;
        std::stringstream ss;
        ss << world_size << ".raw";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 64 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 64;
        std::stringstream ss;
        ss << world_size << ".raw";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 128 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 128;
        std::stringstream ss;
        ss << world_size << ".raw";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 256 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 256;
        std::stringstream ss;
        ss << world_size << ".raw";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 512 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 512;
        std::stringstream ss;
        ss << world_size << ".raw";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 1024 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 1024;
        std::stringstream ss;
        ss << world_size << ".raw";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 2048 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 2048;
        std::stringstream ss;
        ss << world_size << ".raw";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 4096 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 4096;
        std::stringstream ss;
        ss << world_size << ".raw";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 8192 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 8192;
        std::stringstream ss;
        ss << world_size << ".raw";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 16384 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 16384;
        std::stringstream ss;
        ss << world_size << ".raw";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 32768 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 32768;
        std::stringstream ss;
        ss << world_size << ".raw";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 65536 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 65536;
        std::stringstream ss;
        ss << world_size << ".raw";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 131072 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 131072;
        std::stringstream ss;
        ss << world_size << ".raw";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

}

TEST_CASE("Deserialization test of connected world", "[deserialization][connected]") {

    BENCHMARK_ADVANCED("Raw wolrd with 2 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 2;
        std::stringstream ss;
        ss << world_size << ".con";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 4 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 4;
        std::stringstream ss;
        ss << world_size << ".con";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 8 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 8;
        std::stringstream ss;
        ss << world_size << ".con";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 16 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 16;
        std::stringstream ss;
        ss << world_size << ".con";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 32 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 32;
        std::stringstream ss;
        ss << world_size << ".con";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 64 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 64;
        std::stringstream ss;
        ss << world_size << ".con";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 128 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 128;
        std::stringstream ss;
        ss << world_size << ".con";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 256 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 256;
        std::stringstream ss;
        ss << world_size << ".con";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 512 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 512;
        std::stringstream ss;
        ss << world_size << ".con";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 1024 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 1024;
        std::stringstream ss;
        ss << world_size << ".con";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 2048 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 2048;
        std::stringstream ss;
        ss << world_size << ".con";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 4096 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 4096;
        std::stringstream ss;
        ss << world_size << ".con";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 8192 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 8192;
        std::stringstream ss;
        ss << world_size << ".con";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 16384 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 16384;
        std::stringstream ss;
        ss << world_size << ".con";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 32768 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 32768;
        std::stringstream ss;
        ss << world_size << ".con";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 65536 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 65536;
        std::stringstream ss;
        ss << world_size << ".con";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

    BENCHMARK_ADVANCED("Raw wolrd with 131072 planets")(Catch::Benchmark::Chronometer meter) {
        std::size_t world_size = 131072;
        std::stringstream ss;
        ss << world_size << ".con";
        std::string saveFileName = ss.str();

        std::string data_raw;
        std::fstream file(saveFileName, std::ios::binary | std::ios::in | std::ios::app);
        std::string line;
        while ( getline (file,line) )
        {
          data_raw += line+'\n';
        }

        std::stringstream data_stream(data_raw);
        using Reader = nop::StreamReader<std::stringstream>;
        nop::Deserializer<Reader> deserializer(std::move(data_stream));

        hse::world world;

        meter.measure([&]
        {
            deserializer.Read(&world) || Die();
            deserializer.reader().stream().seekg(0);
        });
    };

}



