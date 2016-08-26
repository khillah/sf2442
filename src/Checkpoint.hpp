#pragma once

#include "Coordinates.hpp"

struct Checkpoint
{
    Checkpoint(const Coordinates& pos) :
        pos(pos)
    {}

    bool operator==(const Checkpoint& param) const
    {
        return pos.x == param.pos.x && pos.y == param.pos.y;
    }

    bool operator!=(const Checkpoint& param) const
    {
        return !operator==(param);
    }

    const Coordinates& getPos() const
    {
        return pos;
    }

private:
    Coordinates pos;
};
