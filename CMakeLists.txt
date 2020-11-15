cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(hse-serialization
            VERSION 1.0.0
            DESCRIPTION "HSE serialization task. Persistent world game."
            LANGUAGES CXX)

# finding libnop
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(Libnop REQUIRED)

#main part of the poject
add_library(${PROJECT_NAME}-lib
    src/color.cpp   include/color.hpp
    src/planet.cpp  include/planet.hpp
    src/world.cpp   include/world.hpp
    src/random.cpp  include/random.hpp
)

target_compile_features(${PROJECT_NAME}-lib PRIVATE cxx_std_20)

set_target_properties(${PROJECT_NAME}-lib PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(${PROJECT_NAME}-lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE "${Libnop_INCLUDE_DIR}"
)

#gui part of the project
add_executable(${PROJECT_NAME}-game
                    src/main.cpp
                    src/input_handler.cpp src/input_handler.hpp)
target_compile_features(${PROJECT_NAME}-game PRIVATE cxx_std_20)

set_target_properties(${PROJECT_NAME}-game PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(${PROJECT_NAME}-game
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE "${Libnop_INCLUDE_DIR}"
)

target_link_libraries(${PROJECT_NAME}-lib PRIVATE Libnop::Libnop)

target_link_libraries(${PROJECT_NAME}-game PRIVATE ${PROJECT_NAME}-lib)

target_link_libraries(${PROJECT_NAME}-game PRIVATE Libnop::Libnop)

#testing
enable_testing()

add_subdirectory(test)
