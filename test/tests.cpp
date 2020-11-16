#include "world.hpp"

#include <string>

#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>

#include <nop/serializer.h>
#include <nop/utility/die.h>
#include <nop/utility/stream_reader.h>
#include <nop/utility/stream_writer.h>


// Sends fatal errors to std::cerr.
auto Die() { return nop::Die(std::cerr); }

//std::shared_ptr<hse::world_base> load_game()
//{
//    std::string data_raw;
//    std::ifstream file(saveFileName, std::ios::binary | std::ios::out | std::ios::app);
//    std::string line;
//    while ( getline (file,line) )
//    {
//      data_raw += line+'\n';
//    }

//    std::stringstream data_stream(data_raw);
//    using Reader = nop::StreamReader<std::stringstream>;
//    nop::Deserializer<Reader> deserializer(std::move(data_stream));

//    deserializer.Read(&global_progress) || Die();

//    auto* data = new hse::world_base;
//    deserializer.Read(data) || Die();

//    return std::shared_ptr<hse::world_base>(data);
//}

TEST_CASE("Serialization 5") {
BENCHMARK_ADVANCED("Serrialozation with wolrd of about 5 planet")(Catch::Benchmark::Chronometer meter) {
    hse::world world(5);

    using Writer = nop::StreamWriter<std::stringstream>;
    nop::Serializer<Writer> serializer;

    meter.measure([&]
    {
        serializer.Write(world) || Die();
    });

    std::string data = serializer.writer().stream().str();

    std::stringstream ss("serialize-");
    ss << world.WorldSize() << ".raw";
    std::ofstream file(ss.str());
    file << data;
};
}

TEST_CASE("Serialization 20") {
BENCHMARK_ADVANCED("Serrialozation with wolrd of about 20 planet")(Catch::Benchmark::Chronometer meter) {
    hse::world world(20);

    using Writer = nop::StreamWriter<std::stringstream>;
    nop::Serializer<Writer> serializer;

    meter.measure([&]
    {
        serializer.Write(world) || Die();
    });

    std::string data = serializer.writer().stream().str();

    std::stringstream ss("serialize-");
    ss << world.WorldSize() << ".raw";
    std::ofstream file(ss.str());
    file << data;
};
}

TEST_CASE("Serialization 50") {
BENCHMARK_ADVANCED("Serrialozation with wolrd of about 50 planet")(Catch::Benchmark::Chronometer meter) {
    hse::world world(50);

    using Writer = nop::StreamWriter<std::stringstream>;
    nop::Serializer<Writer> serializer;

    meter.measure([&]
    {
        serializer.Write(world) || Die();
    });

    std::string data = serializer.writer().stream().str();

    std::stringstream ss("serialize-");
    ss << world.WorldSize() << ".raw";
    std::ofstream file(ss.str());
    file << data;
};
}

TEST_CASE("Serialization 100") {
BENCHMARK_ADVANCED("Serrialozation with wolrd of about 100 planet")(Catch::Benchmark::Chronometer meter) {
    hse::world world(100);

    using Writer = nop::StreamWriter<std::stringstream>;
    nop::Serializer<Writer> serializer;

    meter.measure([&]
    {
        serializer.Write(world) || Die();
    });

    std::string data = serializer.writer().stream().str();

    std::stringstream ss("serialize-");
    ss << world.WorldSize() << ".raw";
    std::ofstream file(ss.str());
    file << data;
};
}

TEST_CASE("Serialization 500") {
BENCHMARK_ADVANCED("Serrialozation with wolrd of about 500 planet")(Catch::Benchmark::Chronometer meter) {
    hse::world world(500);

    using Writer = nop::StreamWriter<std::stringstream>;
    nop::Serializer<Writer> serializer;

    meter.measure([&]
    {
        serializer.Write(world) || Die();
    });

    std::string data = serializer.writer().stream().str();

    std::stringstream ss("serialize-");
    ss << world.WorldSize() << ".raw";
    std::ofstream file(ss.str());
    file << data;
};
}

TEST_CASE("Serialization 1500") {
BENCHMARK_ADVANCED("Serrialozation with wolrd of about 1500 planet")(Catch::Benchmark::Chronometer meter) {
    hse::world world(1500);

    using Writer = nop::StreamWriter<std::stringstream>;
    nop::Serializer<Writer> serializer;

    meter.measure([&]
    {
        serializer.Write(world) || Die();
    });

    std::string data = serializer.writer().stream().str();

    std::stringstream ss("serialize-");
    ss << world.WorldSize() << ".raw";
    std::ofstream file(ss.str());
    file << data;
};
}

TEST_CASE("Serialization 3200") {
BENCHMARK_ADVANCED("Serrialozation with wolrd of about 3200 planet")(Catch::Benchmark::Chronometer meter) {
    hse::world world(3200);

    using Writer = nop::StreamWriter<std::stringstream>;
    nop::Serializer<Writer> serializer;

    meter.measure([&]
    {
        serializer.Write(world) || Die();
    });

    std::string data = serializer.writer().stream().str();

    std::stringstream ss("serialize-");
    ss << world.WorldSize() << ".raw";
    std::ofstream file(ss.str());
    file << data;
};
}

TEST_CASE("Serialization 7000") {
BENCHMARK_ADVANCED("Serrialozation with wolrd of about 7000 planet")(Catch::Benchmark::Chronometer meter) {
    hse::world world(7000);

    using Writer = nop::StreamWriter<std::stringstream>;
    nop::Serializer<Writer> serializer;

    meter.measure([&]
    {
        serializer.Write(world) || Die();
    });

    std::string data = serializer.writer().stream().str();

    std::stringstream ss("serialize-");
    ss << world.WorldSize() << ".raw";
    std::ofstream file(ss.str());
    file << data;
};
}

TEST_CASE("Serialization 15000") {
BENCHMARK_ADVANCED("Serrialozation with wolrd of about 15000 planet")(Catch::Benchmark::Chronometer meter) {
    hse::world world(15000);

    using Writer = nop::StreamWriter<std::stringstream>;
    nop::Serializer<Writer> serializer;

    meter.measure([&]
    {
        serializer.Write(world) || Die();
    });

    std::string data = serializer.writer().stream().str();

    std::stringstream ss("serialize-");
    ss << world.WorldSize() << ".raw";
    std::ofstream file(ss.str());
    file << data;
};
}
