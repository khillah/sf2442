#pragma once

#include <vector>
#include <memory>

#include "Coordinates.hpp"
#include "Player.hpp"
#include "Command.hpp"
#include "CommandFactory.hpp"
#include "Checkpoint.hpp"

struct Game
{
    Game(Player & me,
         int laps,
         std::shared_ptr<std::vector<Checkpoint>>& checkpoints,
         CommandFactory commandFactory,
         std::function<void(Player& me, std::vector<Player>& others)> getState
         ) :
        me(me),
        others(others),
//        numberOfLaps(laps),
        checkpoints(checkpoints),
        commandFactory(commandFactory),
        getState(getState),
        remainingLaps(laps + 1),
        longestPathEnd(&checkpoints->at(0)) // issue
    {}

    void tick()
    {
        if(me.checkpointChanged())
        {
            if(*me.getCurrentCheckpoint() == checkpoints->at(0))
            {
                onNewLap();
            }
            onCheckpointChange();
        }
        calculateCommand().execute();
    }

    void nextTurn()
    {
        getState(me, others);
    }

    std::vector<Checkpoint>& getCheckpoints()
    {
        return *checkpoints;
    }

private:

    const double FiveDegreesInRadians = 0.0872664626;
//    const double NinetyDegreesInRadians = 1.57079633;

    int pathLength(const Coordinates& a, const Coordinates& b)
    {
        return static_cast<int>(sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
    }

    void readConfig()
    {
#if 0
        int players;
        cin >> players; cin.ignore();
        game.players.resize(players);

        cin >> game.laps; cin.ignore();
        cin >> game.boosts; cin.ignore();
        game.remainingLaps = game.laps + 1;
        game.remainingBoosts = game.boosts;

        Coordinates pos;
        int checkpointCount;
        cin >> checkpointCount; cin.ignore();
        for (int i = 0; i < checkpointCount; i++)
        {
            cin >> pos.x >> pos.y; cin.ignore();
            game.checkpoints.push_back(pos);
        }

        for(int i = 0; i < checkpointCount - 1; i++)
        {
            Coordinates pos = expectedVector(game.checkpoints[i], game.checkpoints[i + 1]);
            game.expectedAngle.push_back(atan2(pos.y, pos.x));
        }
        pos = expectedVector(game.checkpoints[game.checkpoints.size()], game.checkpoints[0]);
        game.expectedAngle.push_back(atan2(pos.y, pos.x));

        game.longestPathEnd = 1;
        int maxLength = pathLength(game.checkpoints[game.checkpoints.size()], game.checkpoints[0]);
        for(int i = 1; i < checkpointCount; i++)
        {
            int length = pathLength(game.checkpoints[i-1], game.checkpoints[i]);
            if(length > maxLength)
            {
                maxLength = length;
                game.longestPathEnd = i;
            }
        }

        game.boostsPerLap = game.boosts / game.laps;
#endif
    }

    bool isOnLongestPath()
    {
        return *me.getCurrentCheckpoint() == *longestPathEnd;
    }

    bool isBoostAvailable()
    {
        return me.getAvailableBoosts() > 0;
    }

    double angleDifference()
    {
        Coordinates vector(me.getPosition(), me.getCurrentCheckpoint()->getPos());
        return fabs(atan2(vector.y, vector.x) - me.getAngle());
    }

    bool angleIsProperForBoost()
    {
        return angleDifference() < FiveDegreesInRadians;
    }

    bool shouldUseBoost()
    {
        return angleIsProperForBoost() && (emergencyBoost || (isOnLongestPath() && isBoostAvailable()));
    }

    bool isLastLap()
    {
        return remainingLaps == 0;
    }

    bool isLastCheckpoint()
    {
        return *me.getCurrentCheckpoint() == checkpoints->at(0);
    }

    void onCheckpointChange()
    {
        if(isLastLap() and isLastCheckpoint())
        {
            emergencyBoost = true;
        }
    }

    void onNewLap()
    {
        me.setAvailableBoosts(boostsPerLap);
    }

    Command calculateCommand()
    {
        Command cmd = commandFactory.create();

        if(shouldUseBoost() and me.getAvailableBoosts() > 0)
        {
            cmd.setBoost();
            me.useBoost();        }
        else
        {
            cmd.setThrust(calculateThrust());
        }

        cmd.setCoordinates(me.getCurrentCheckpoint()->getPos());

        return cmd;
    }

    int calculateThrust()
    {
        double diff = angleDifference();
        int distance = pathLength(me.getPosition(), me.getCurrentCheckpoint()->getPos());

        if(diff > 5.0 || distance < 6000)
        {
            return 50;
        }
        else if(diff > 4.0 || distance < 7000)
        {
            return 70;
        }
        else if(diff > 3.0 || distance < 8000)
        {
            return 80;
        }
        else if(diff > 2.0 || distance < 9000)
        {
            return 90;
        }
        else
        {
            return 100;
        }
    }

    Player me;
    std::vector<Player> others;
//    int numberOfLaps;
    std::shared_ptr<std::vector<Checkpoint>> checkpoints;
    CommandFactory commandFactory;
    std::function<void(Player& me, std::vector<Player>& others)> getState;
    std::vector<double> expectedAngle;
    int remainingLaps;
    int boostsPerLap;
    Checkpoint* longestPathEnd;
    bool emergencyBoost;
};
