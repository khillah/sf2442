cmake_minimum_required(VERSION 2.6)

SET(CMAKE_CXX_FLAGS "-std=gnu++14")

set(HEADERS
	src/Thrust.hpp
	src/Command.hpp
	src/Coordinates.hpp
	src/Game.hpp
	src/Player.hpp
	src/Checkpoint.hpp
	src/IoInterface.hpp
	src/IO.hpp
	src/Params.hpp
	src/Logic.hpp
	src/RaceProgress.hpp
	src/TargetCalculator.hpp
	src/ThrustCalculator.hpp
)	

set(SOURCES
	src/main.cpp
)

set(TESTS
	tests/IoMock.hpp
	tests/RaceProgressMock.hpp
	tests/gmock_main.cpp
	tests/ModuleTests.cpp
	tests/TargetCalculatorTestSuite.cpp
	tests/ThrustCalculatorTestSuite.cpp
)

find_package(Threads REQUIRED)
include(ExternalProject)
ExternalProject_Add(
    gtest
    URL https://github.com/google/googletest/archive/master.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    # Disable install step
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(gtest source_dir binary_dir)

add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)
set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)
set_target_properties(libgmock PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)
include_directories("${source_dir}/googletest/include"
                    "${source_dir}/googlemock/include")

add_executable(hackaton_tests ${TESTS} ${HEADERS})
target_link_libraries(hackaton_tests libgtest libgmock)

add_executable(hackaton ${SOURCES} ${HEADERS})
