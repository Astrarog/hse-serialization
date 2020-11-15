add_executable(${PROJECT_NAME}-test tests.cpp test_runner.hpp)

target_compile_features(${PROJECT_NAME}-test PRIVATE cxx_std_20)

set_target_properties(${PROJECT_NAME}-test PROPERTIES CXX_EXTENSIONS OFF)

target_link_libraries(${PROJECT_NAME}-test PRIVATE ${PROJECT_NAME}-lib)

find_package(Catch2 2.13.3 REQUIRED)

find_package(Libnop REQUIRED)

target_link_libraries(${PROJECT_NAME}-test PRIVATE Catch2::Catch2)

target_link_libraries(${PROJECT_NAME}-test PRIVATE Libnop::Libnop)

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME}-test)

