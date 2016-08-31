#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/ThrustCalculator.hpp"
#include "RaceProgressMock.hpp"

using namespace ::testing;

struct ThrustCalculatorTestSuite : public Test
{
    ThrustCalculatorTestSuite() :
        position(0, 0),
        target(100, 100),
        sut(progress, 2)
    {}

    Coordinates position;
    Coordinates target;
    StrictMock<RaceProgressMock> progress;
    ThrustCalculator sut;
};

void matchThrust(const Thrust& t1, const Thrust& t2)
{
    EXPECT_EQ(t1.useBoost, t2.useBoost);
    EXPECT_EQ(t1.value, t2.value);
}

TEST_F(ThrustCalculatorTestSuite, returnsFullThrust)
{
    EXPECT_CALL(progress, isLastPointInRace())
            .WillOnce(Return(false));
    ASSERT_NO_FATAL_FAILURE(matchThrust(Thrust{false, 100}, sut.calculate(position, target, target)));
}

TEST_F(ThrustCalculatorTestSuite, returnsBoostOnALastCheckpoint)
{
    EXPECT_CALL(progress, isLastPointInRace())
            .WillOnce(Return(true));
    ASSERT_NO_FATAL_FAILURE(matchThrust(Thrust{true, 100}, sut.calculate(position, target, target)));
}
