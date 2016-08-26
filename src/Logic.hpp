#pragma once

#include "Player.hpp"
#include "Params.hpp"
#include "Command.hpp"
#include "RaceProgress.hpp"
#include "TargetCalculator.hpp"
#include "ThrustCalculator.hpp"

struct Logic
{
    Logic(const Params& params) :
        params(params),
        progress(params.numOfLaps,
                 static_cast<unsigned int>(params.checkpoints.size())),
        thrustCalc(progress, params.numOfBoosts)
    {}

    Command turn(const Player& p)
    {
        const Checkpoint& prev = params.checkpoints[(p.checkpoint + params.checkpoints.size() - 1) % params.checkpoints.size()];
        const Checkpoint& next = params.checkpoints[p.checkpoint];
        const Checkpoint& afterNext = params.checkpoints[(p.checkpoint + 1) % params.checkpoints.size()];
        Coordinates target = targetCalc.calculate(p.pos,
                                                  prev.getCoordinates(),
                                                  next.getCoordinates(),
                                                  afterNext.getCoordinates());
        return {target, thrustCalc.calculate(p.pos, p.v, target)};
    }

private:
    const Params& params;
    RaceProgress progress;
    TargetCalculator targetCalc;
    ThrustCalculator thrustCalc;
};
