#pragma once

struct RaceProgress
{
    RaceProgress(unsigned int numOfLaps, unsigned int numOfPoints) :
        numOfPoints(numOfPoints),
        numOfLapsToGo(numOfLaps),
        numOfPointsToGo(numOfPoints + 1)
    {}

    void update(unsigned int target)
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

    unsigned int lapsToGo()
    {
        return numOfLapsToGo;
    }

    unsigned int totalNumOfPointsToGo()
    {
        return (numOfLapsToGo - 1) * numOfPoints + numOfPointsToGo;
    }

    unsigned int pointsToGoOnThisLap()
    {
        return numOfPointsToGo;
    }

    bool isLastLap()
    {
        return numOfLapsToGo == 1;
    }

    bool isLastPointInRace()
    {
        return totalNumOfPointsToGo() == 1;
    }

private:
    unsigned int numOfPoints;
    unsigned int numOfLapsToGo;
    unsigned int numOfPointsToGo;
    unsigned int lastTarget;
};
