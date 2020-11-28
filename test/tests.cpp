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

void measure_serialization(Catch::Benchmark::Chronometer& meter, std::size_t world_size, bool isConnected=false)
{
	hse::world world = isConnected ? generateConnected(world_size): hse::world{world_size};
	
	
    using Writer = nop::StreamWriter<std::stringstream>;
    nop::Serializer<Writer> serializer;

    meter.measure([&]
    {
        serializer.Write(world) || Die();
		serializer.writer().stream().seekp(0);
    });

    std::string data = serializer.writer().stream().str();

    std::stringstream ss;
    ss << world.WorldSize() << isConnected? ".con" :".raw";
    std::ofstream file(ss.str());
    file << data;
}

void measaure_deserialization(Catch::Benchmark::Chronometer& meter, std::size_t world_size, bool isConnected=false)
{
	std::stringstream ss;
	ss << world_size << isConnected?".con":".raw";
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
}

#define SERIALIZATION_RAW_TEST(size): \
    BENCHMARK_ADVANCED("Raw world with size planets")(Catch::Benchmark::Chronometer meter) { \
		measure_serialization(meter, size); \
    };

#define SERIALIZATION_CON_TEST(size): \
    BENCHMARK_ADVANCED("Connected world with size planets")(Catch::Benchmark::Chronometer meter) { \
		measure_serialization(meter, size, true); \
    };

#define DESERIALIZATION_RAW_TEST(size): \
    BENCHMARK_ADVANCED("Raw world with size planets")(Catch::Benchmark::Chronometer meter) { \
		measure_deserialization(meter, size); \
    };

#define DESERIALIZATION_CON_TEST(size): \
    BENCHMARK_ADVANCED("Connected world with size planets")(Catch::Benchmark::Chronometer meter) { \
		measure_deserialization(meter, size, true); \
    };

TEST_CASE("Serialization testof raw world", "[serialization][raw]") {
    SERIALIZATION_RAW_TEST(2);
    SERIALIZATION_RAW_TEST(4);
    SERIALIZATION_RAW_TEST(8);
    SERIALIZATION_RAW_TEST(16);
    SERIALIZATION_RAW_TEST(32);
    SERIALIZATION_RAW_TEST(64);
    SERIALIZATION_RAW_TEST(128);
    SERIALIZATION_RAW_TEST(256);
    SERIALIZATION_RAW_TEST(512);
    SERIALIZATION_RAW_TEST(1024);
    SERIALIZATION_RAW_TEST(2048);
    SERIALIZATION_RAW_TEST(4096);
	SERIALIZATION_RAW_TEST(8192);
	SERIALIZATION_RAW_TEST(16384);
	SERIALIZATION_RAW_TEST(32768);
	SERIALIZATION_RAW_TEST(65536);
	SERIALIZATION_RAW_TEST(131072);
}

TEST_CASE("Serialization test of connected world", "[serialization][connected]") {
    SERIALIZATION_CON_TEST(2);
    SERIALIZATION_CON_TEST(4);
    SERIALIZATION_CON_TEST(8);
    SERIALIZATION_CON_TEST(16);
    SERIALIZATION_CON_TEST(32);
    SERIALIZATION_CON_TEST(64);
    SERIALIZATION_CON_TEST(128);
    SERIALIZATION_CON_TEST(256);
    SERIALIZATION_CON_TEST(512);
    SERIALIZATION_CON_TEST(1024);
    SERIALIZATION_CON_TEST(2048);
    SERIALIZATION_CON_TEST(4096);
	SERIALIZATION_CON_TEST(8192);
	SERIALIZATION_CON_TEST(16384);
	SERIALIZATION_CON_TEST(32768);
	SERIALIZATION_CON_TEST(65536);
	SERIALIZATION_CON_TEST(131072);
}

TEST_CASE("Deserialization test of raw world", "[deserialization][raw]") {
	DESERIALIZATION_RAW_TEST(2);
    DESERIALIZATION_RAW_TEST(4);
    DESERIALIZATION_RAW_TEST(8);
    DESERIALIZATION_RAW_TEST(16);
    DESERIALIZATION_RAW_TEST(32);
    DESERIALIZATION_RAW_TEST(64);
    DESERIALIZATION_RAW_TEST(128);
    DESERIALIZATION_RAW_TEST(256);
    DESERIALIZATION_RAW_TEST(512);
    DESERIALIZATION_RAW_TEST(1024);
    DESERIALIZATION_RAW_TEST(2048);
    DESERIALIZATION_RAW_TEST(4096);
	DESERIALIZATION_RAW_TEST(8192);
	DESERIALIZATION_RAW_TEST(16384);
	DESERIALIZATION_RAW_TEST(32768);
	DESERIALIZATION_RAW_TEST(65536);
	DESERIALIZATION_RAW_TEST(131072);
}
TEST_CASE("Deserialization test of connected world", "[deserialization][connected]") {
	DESERIALIZATION_CON_TEST(2);
    DESERIALIZATION_CON_TEST(4);
    DESERIALIZATION_CON_TEST(8);
    DESERIALIZATION_CON_TEST(16);
    DESERIALIZATION_CON_TEST(32);
    DESERIALIZATION_CON_TEST(64);;
    DESERIALIZATION_CON_TEST(128);
    DESERIALIZATION_CON_TEST(256);
    DESERIALIZATION_CON_TEST(512);
    DESERIALIZATION_CON_TEST(1024);
    DESERIALIZATION_CON_TEST(2048);
    DESERIALIZATION_CON_TEST(4096);
	DESERIALIZATION_CON_TEST(8192);
	DESERIALIZATION_CON_TEST(16384);
	DESERIALIZATION_CON_TEST(32768);
	DESERIALIZATION_CON_TEST(65536);
	DESERIALIZATION_CON_TEST(131072);	
}



