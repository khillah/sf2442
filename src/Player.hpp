#pragma once

#include "Coordinates.hpp"

struct Player
{
    Coordinates pos;
    Coordinates v;
    size_t checkpoint;
};
