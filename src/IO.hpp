#pragma once

#include <iostream>
#include <vector>
#include "Player.hpp"
#include "Params.hpp"
#include "Command.hpp"

struct IO
{
    Params readParams()
    {
        Params params;

        std::cin >> params.numOfPlayers; std::cin.ignore();

        std::cin >> params.numOfLaps; std::cin.ignore();
        std::cin >> params.numOfBoosts; std::cin.ignore();

        size_t checkpointCount; std::cin >> checkpointCount; std::cin.ignore();
        Coordinates pos;
        for (size_t i = 0; i < checkpointCount; i++)
        {
            std::cin >> pos.x >> pos.y; std::cin.ignore();
            params.checkpoints.push_back(pos);
        }

        return params;
    }

    std::vector<Player> readPlayers(size_t numOfPlayers)
    {
        std::vector<Player> players;

        for (size_t i = 0; i < numOfPlayers; i++)
        {
            players.push_back(readPlayer());
        }

        return players;
    }

    void executeCommand(const Command& cmd)
    {
        std::cout << cmd.pos.x << " " << cmd.pos.y << " ";
        if(cmd.useBoost)
        {
            std::cout << "BOOST" << std::endl;
        }
        else
        {
            std::cout << cmd.thrust << std::endl;
        }
    }

private:
    Player readPlayer()
    {
        Player player;
        std::cin >> player.pos.x >> player.pos.y >> player.v.x >> player.v.y >> player.checkpoint; std::cin.ignore();
        return player;
    }
};
