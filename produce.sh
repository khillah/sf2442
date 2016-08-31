#!/bin/bash

OUTPUT=source.cpp

FILE_LIST="\
	src/Thrust.hpp \
	src/RaceProgress.hpp \
	src/Coordinates.hpp \
	src/Vector.hpp \
	src/TargetCalculator.hpp \
	src/ThrustCalculator.hpp \
	src/Command.hpp \
	src/Simulation.hpp \
	src/Checkpoint.hpp \
	src/Player.hpp \
	src/Params.hpp \
	src/Logic.hpp \
	src/IoInterface.hpp \
	src/IO.hpp \
	src/Game.hpp \
	src/main.cpp \
"

grep -h "#include <" ${FILE_LIST} | sort -u > ${OUTPUT}

for FILE in ${FILE_LIST};
do
	grep -v "#include" ${FILE} | grep -v "#pragma once" >> ${OUTPUT};
done

ERRORS=`g++ -Wall --pedantic -std=c++11 ${OUTPUT} -o /dev/null 2>&1`

if [ -z "${ERRORS}" ];
then
	leafpad ${OUTPUT} &
else
	g++ -Wall --pedantic -std=c++11 ${OUTPUT} -o /dev/null
fi
