#pragma once

#include "Coordinates.hpp"
#include <functional>

struct Command
{
    Coordinates pos;
    bool useBoost;
    int thrust;
};
