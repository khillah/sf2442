#pragma once

struct RaceProgress
{
    RaceProgress(unsigned int numOfLaps, unsigned int numOfPoints) :
        numOfPoints(numOfPoints),
        numOfLapsToGo(numOfLaps),
        numOfPointsToGo(numOfPoints + 1),
        lastTarget(0xffffffff)
    {}

    virtual void update(unsigned int target)
    {
        if(lastTarget != target)
        {
            numOfPointsToGo--;
            if(numOfPointsToGo == 0)
            {
                numOfPointsToGo = numOfPoints;
                numOfLapsToGo--;
            }
            lastTarget = target;
        }
    }

    virtual unsigned int lapsToGo() const
    {
        return numOfLapsToGo;
    }

    virtual unsigned int totalNumOfPointsToGo() const
    {
        return (numOfLapsToGo - 1) * numOfPoints + numOfPointsToGo;
    }

    virtual unsigned int pointsToGoOnThisLap() const
    {
        return numOfPointsToGo;
    }

    virtual bool isLastLap() const
    {
        return numOfLapsToGo == 1;
    }

    virtual bool isLastPointInRace() const
    {
        return totalNumOfPointsToGo() <= 1;
    }

private:
    unsigned int numOfPoints;
    unsigned int numOfLapsToGo;
    unsigned int numOfPointsToGo;
    unsigned int lastTarget;
};
