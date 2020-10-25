cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(hse-serialization LANGUAGES CXX)

add_executable(${PROJECT_NAME}
                    src/main.cpp
                    src/world.cpp
                    include/world.hpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)


set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
