cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(hse-serialization
            VERSION 0.0.1
            DESCRIPTION "HSE serialization task. Persistent world game."
            LANGUAGES CXX)

add_library(${PROJECT_NAME}-lib STATIC
    src/planet.cpp  include/planet.hpp
    src/world.cpp   include/world.hpp
    src/color.cpp   include/color.hpp
    src/portal.cpp  include/portal.hpp
)

add_executable(${PROJECT_NAME}-game
                    src/main.cpp)

target_compile_features(${PROJECT_NAME}-lib PRIVATE cxx_std_20)
target_compile_features(${PROJECT_NAME}-game PRIVATE cxx_std_20)

#set(HSE_SERIALIZATION_DIR)

set_target_properties(${PROJECT_NAME}-lib PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(${PROJECT_NAME}-game PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(${PROJECT_NAME}-lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_include_directories(${PROJECT_NAME}-lib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}-game PRIVATE ${PROJECT_NAME}-lib)

enable_testing()

add_subdirectory(test)
