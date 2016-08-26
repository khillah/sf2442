#pragma once

#include "Coordinates.hpp"
#include "Thrust.hpp"
#include <functional>

struct Command
{
    Coordinates pos;
    Thrust thrust;
};
