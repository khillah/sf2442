#pragma once

#include "Thrust.hpp"
#include "Coordinates.hpp"
#include "RaceProgress.hpp"
#include "Vector.hpp"
#include <cmath>

constexpr unsigned int BOOSTS_RESERVED_FOR_LAST_LAP_PERCENTAGE = 5u;
constexpr double TEN_DEGREES_IN_RADIANS = 0.174532925;

struct ThrustCalculator
{
    ThrustCalculator(const RaceProgress& progress,
                     unsigned int numOfBoosts) :
        progress(progress),
        reservedBoosts(reserveBoosts(numOfBoosts)),
        numOfBoosts(numOfBoosts - reservedBoosts)
    {}

    Thrust calculate(const Coordinates& position,
                     const Coordinates& velocity,
                     const Coordinates& target)
    {
        Vector targetVec(position, target);
        Vector shipVelocity(velocity.x, velocity.y);
        targetVec.normalize();
        shipVelocity.normalize();

        if(progress.isLastPointInRace() && shipVelocity.angleBetweenVectorsNormalized(targetVec) < TEN_DEGREES_IN_RADIANS)
        {
            return {true, 100};
        }
        return {false, 100};
    }

private:
    unsigned int reserveBoosts(unsigned int numOfBoosts)
    {
        return static_cast<unsigned int>(std::fmax(1.0f, numOfBoosts * 100 / BOOSTS_RESERVED_FOR_LAST_LAP_PERCENTAGE));
    }

    const RaceProgress& progress;
    unsigned int reservedBoosts;
    unsigned int numOfBoosts;
};
