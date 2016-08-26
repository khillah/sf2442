#pragma once

#include "Player.hpp"
#include "Params.hpp"
#include "Command.hpp"

struct Logic
{
    Logic(const Params& params) :
        params(params)
    {}

    Command turn(const Player& p)
    {
        const Checkpoint& target = params.checkpoints[p.checkpoint];
        return Command{target.getCoordinates(), false, 100};
    }

private:
    const Params& params;
};
