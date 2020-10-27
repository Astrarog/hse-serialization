cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(hse-serialization
            VERSION 1.0.0
            DESCRIPTION "HSE serialization task. Persistent world game."
            LANGUAGES CXX)

#main part of the poject
add_library(${PROJECT_NAME}-lib STATIC
    src/color.cpp   include/color.hpp
    src/planet.cpp  include/planet.hpp
    src/world.cpp   include/world.hpp
    src/random.cpp  include/random.hpp
)

target_compile_features(${PROJECT_NAME}-lib PRIVATE cxx_std_20)

set_target_properties(${PROJECT_NAME}-lib PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(${PROJECT_NAME}-lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#list(APPEND CMAKE_MODULE_PATH "C:/dev/lib/boost/lib/cmake")

#find_package(Boost REQUIRED)

#target_link_libraries(${PROJECT_NAME}-lib PUBLIC Boost::headers)


#gui part of the project
add_executable(${PROJECT_NAME}-game
                    src/main.cpp)
target_compile_features(${PROJECT_NAME}-game PRIVATE cxx_std_20)

set_target_properties(${PROJECT_NAME}-game PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(${PROJECT_NAME}-game
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}-game PRIVATE ${PROJECT_NAME}-lib)

#testing
enable_testing()

add_subdirectory(test)
