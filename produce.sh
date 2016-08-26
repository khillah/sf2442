#!/bin/bash

FILE_LIST="\
	src/RaceProgress.hpp \
	src/Coordinates.hpp \
	src/Command.hpp \
	src/Checkpoint.hpp \
	src/Player.hpp \
	src/Params.hpp \
	src/Logic.hpp \
	src/IO.hpp \
	src/Game.hpp \
	src/main.cpp \
"

grep -h "#include <" ${FILE_LIST} | sort -u

for FILE in ${FILE_LIST};
do
	grep -v "#include" ${FILE} | grep -v "#pragma once";
done
