cmake_minimum_required(VERSION 2.6)

SET(CMAKE_CXX_FLAGS "-std=gnu++11")

set(HEADERS
	src/Thrust.hpp
	src/Command.hpp
	src/Coordinates.hpp
	src/Game.hpp
	src/Player.hpp
	src/Checkpoint.hpp
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

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
#find_package(GTest REQUIRED)
#find_package(GMock REQUIRED)

add_executable(hackaton ${SOURCES} ${HEADERS})
