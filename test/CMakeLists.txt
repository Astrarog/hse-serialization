add_executable(${PROJECT_NAME}-test tests.cpp)

target_compile_features(${PROJECT_NAME}-test PRIVATE cxx_std_20)

set_target_properties(${PROJECT_NAME}-test PROPERTIES CXX_EXTENSIONS OFF)

target_link_libraries(${PROJECT_NAME}-test PRIVATE ${PROJECT_NAME}-lib)

# try to find system Catch
find_package(Catch2 2.13.3)
if(NOT Catch2_FOUND)
    add_subdirectory(${CMAKE_SOURCE_DIR}/lib/Catch2 ${CMAKE_BINARY_DIR}/Catch2)
endif()

find_package(Libnop REQUIRED)

target_link_libraries(${PROJECT_NAME}-test PRIVATE Catch2::Catch2)

target_link_libraries(${PROJECT_NAME}-test PRIVATE Libnop::Libnop)

# add catch2 cmake scripts for bundling
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/lib/Catch2/contrib")

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME}-test)

