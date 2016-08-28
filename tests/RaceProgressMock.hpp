#pragma once

#include "../src/RaceProgress.hpp"
#include <gmock/gmock.h>

struct RaceProgressMock : public RaceProgress
{
    RaceProgressMock() :
        RaceProgress(1, 1)
    {}

    MOCK_METHOD1(update, void(unsigned int target));
    MOCK_CONST_METHOD0(lapsToGo, unsigned int());
    MOCK_CONST_METHOD0(totalNumOfPointsToGo, unsigned int());
    MOCK_CONST_METHOD0(pointsToGoOnThisLap, unsigned int());
    MOCK_CONST_METHOD0(isLastLap, bool());
    MOCK_CONST_METHOD0(isLastPointInRace, bool());
};
