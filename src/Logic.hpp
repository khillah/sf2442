#pragma once

#include "Player.hpp"
#include "Params.hpp"
#include "Command.hpp"
#include "RaceProgress.hpp"

struct Logic
{
    Logic(const Params& params) :
        params(params),
        progress(params.numOfLaps, params.checkpoints.size())
    {}

    Command turn(const Player& p)
    {
        const Checkpoint& target = params.checkpoints[p.checkpoint];
        return Command{target.getCoordinates(), progress.isLastPointInRace(), 100};
    }

private:
    const Params& params;
    RaceProgress progress;
};
