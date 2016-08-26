#pragma once

#include <vector>
#include "Checkpoint.hpp"

struct Params
{
    unsigned int numOfPlayers;
    unsigned int numOfLaps;
    unsigned int numOfBoosts;
    std::vector<Checkpoint> checkpoints;
};
