#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/Simulation.hpp"

using namespace ::testing;

TEST(SimulationTestSuite, basicSimulation)
{
    Coordinates pos {12633, 7691};
    Vector velocity {0, 0};

    std::vector<Command> commands =
    {
        {{5753, 3037}, {0, 100}},
        {{5752, 3037}, {0, 100}}
    };

    Simulation sim(pos, velocity, commands);

    EXPECT_EQ(12397, sim.nextPos.x);
    EXPECT_EQ(7532,  sim.nextPos.y);

    EXPECT_EQ(-129, sim.velocity.x);
    EXPECT_EQ(-87, sim.velocity.y);
}

TEST(SimulationTestSuite, simulation1)
{
    Coordinates pos {5182, 4694};
    Vector velocity {0, 0};

    std::vector<Command> commands =
    {
        {{5282, 4694}, {false, 100}},
        {{5382, 4694}, {false, 100}},
        {{5567, 4694}, {false, 100}},
        {{5824, 4694}, {false, 100}},
        {{6142, 4694}, {false, 100}},
        {{6512, 4694}, {false, 100}},
        {{6926, 4694}, {false, 100}},
        {{7377, 4694}, {false, 100}},
        {{7860, 4694}, {false, 100}},
        {{8370, 4694}, {false, 100}},
        {{8903, 4694}, {false, 100}},
        {{9456, 4694}, {false, 100}},
        {{10026, 4694}, {false, 100}},
        {{10610, 4694}, {false, 100}},
        {{11206, 4694}, {false, 100}},
        {{11812, 4694}, {false, 100}},
        {{12427, 4694}, {false, 100}},
        {{13049, 4694}, {false, 100}},
        {{13677, 4694}, {false, 100}},
        {{14310, 4694}, {false, 100}},
        {{14948, 4694}, {false, 100}},
        {{15590, 4694}, {false, 100}}
    };

    Simulation sim(pos, velocity, commands);

    EXPECT_EQ(16135, sim.nextPos.x);
    EXPECT_EQ(4694,  sim.nextPos.y);

    EXPECT_EQ(548, sim.velocity.x);
    EXPECT_EQ(0,   sim.velocity.y);
}

TEST(SimulationTestSuite, simulation2)
{
    Coordinates pos {12633, 7691};
    Vector velocity {0, 0};

    std::vector<Command> commands =
    {
        {{5753, 3037}, {0, 100}},
        {{5752, 3037}, {0, 100}},
        {{5752, 3037}, {0, 100}},
        {{5752, 3038}, {0, 100}},
        {{5752, 3038}, {0, 100}},
        {{5752, 3038}, {0, 100}},
        {{5751, 3039}, {0, 100}}
    };

    Simulation sim(pos, velocity, commands);

    EXPECT_EQ(10901, sim.nextPos.x);
    EXPECT_EQ(6523,  sim.nextPos.y);

    EXPECT_EQ(-316, sim.velocity.x);
    EXPECT_EQ(-214, sim.velocity.y);
}
