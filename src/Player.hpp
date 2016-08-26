#pragma once

#include "Coordinates.hpp"
#include "Checkpoint.hpp"

#include <math.h>

struct Player
{
    Player(Checkpoint* checkpoint,
           int numOfBoosts) :
        previousCheckpoint(checkpoint),
        checkpoint(checkpoint),
        availableBoosts(numOfBoosts)
    {}

    void update(Coordinates& coords, Coordinates& velocity, Checkpoint* checkpoint)
    {
        previousCheckpoint = this->checkpoint;
        this->checkpoint = checkpoint;
        pos = coords;
        v = velocity;
        angle = atan2(v.y, v.x);
    }

    const Coordinates& getPosition()
    {
        return pos;
    }

    const Coordinates& getVelocity()
    {
        return v;
    }

    bool checkpointChanged()
    {
        return previousCheckpoint != checkpoint;
    }

    const Checkpoint* getCurrentCheckpoint()
    {
        return checkpoint;
    }

    void useBoost()
    {
        availableBoosts--;
    }

    int getAvailableBoosts() const
    {
        return availableBoosts;
    }

    void setAvailableBoosts(int boosts)
    {
        availableBoosts = boosts;
    }

    double getAngle() const
    {
        return  angle;
    }


private:
    Coordinates pos;
    Coordinates v;
    double angle;
    Checkpoint* previousCheckpoint;
    Checkpoint* checkpoint;
    int availableBoosts;
};
