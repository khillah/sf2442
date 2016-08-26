#pragma once

#include "Coordinates.hpp"
#include <functional>

struct Command
{
    Command(std::function<void(int, int, bool, int)> executeFunc) :
        executeFunc(executeFunc)
    {}

    void execute()
    {
        executeFunc(pos.x, pos.y, useBoost, thrust);
    }

    void setCoordinates(const Coordinates& coords)
    {
        pos = coords;
    }

    void setBoost()
    {
        useBoost = true;
    }

    void setThrust(int thrust)
    {
        this->thrust = thrust;
    }

private:
    Coordinates pos;
    bool useBoost;
    int thrust;
    std::function<void(int, int, bool, int)> executeFunc;
};
