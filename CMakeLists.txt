cmake_minimum_required(VERSION 2.6)

SET(CMAKE_CXX_FLAGS "-std=gnu++11")

set(HEADERS
	src/Command.hpp
	src/CommandFactory.hpp
	src/Coordinates.hpp
	src/Game.hpp
	src/Player.hpp
	src/Checkpoint.hpp
)	

set(SOURCES
	src/main.cpp
)

add_executable(hackaton ${SOURCES} ${HEADERS})
