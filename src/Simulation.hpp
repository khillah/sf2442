#pragma once

#include "Coordinates.hpp"
#include "Command.hpp"
#include "Vector.hpp"

#include <vector>

struct Simulation
{
    Simulation(const Coordinates& pos, const Vector& v, const std::vector<Command>& commands) :
        nextPos(pos)
    {
        velocity.x = static_cast<int>(v.x);
        velocity.y = static_cast<int>(v.y);

        for(const Command& cmd : commands)
        {
            nextTurn(cmd);
        }
    }

    void nextTurn(const Command& cmd)
    {
        Vector vAddition(nextPos, cmd.pos);
        vAddition.normalize();
        Vector v {static_cast<double>(velocity.x), static_cast<double>(velocity.y)};
        v.addVectorMultipliedByFloat(vAddition, cmd.thrust.value);

        nextPos = v.translatePoint(nextPos);
        v.multiply(0.85).cut();
        velocity.x = static_cast<int>(v.x);
        velocity.y = static_cast<int>(v.y);
    }

    Coordinates nextPos;
    Coordinates velocity;
};
