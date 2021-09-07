FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update

RUN apt-get install --yes --no-install-recommends \
    git \
    ca-certificates \
    build-essential \
    cmake \
    ninja-build

WORKDIR /root/game/

COPY . .

RUN git submodule init
RUN git submodule update

RUN cmake \

    -DCMAKE_BUILD_TYPE=Debug \

    -DCMAKE_CXX_FLAGS="-std=c++17" \

    -B build -G Ninja

RUN cmake --build build

WORKDIR build

ENTRYPOINT ./hse-serialization-game
