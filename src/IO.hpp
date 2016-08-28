#pragma once

#include <iostream>
#include <vector>
#include "IoInterface.hpp"
#include "Player.hpp"
#include "Params.hpp"
#include "Command.hpp"

struct IoImpl : public IO
{
    Params readParams() override
    {
        Params params;

        std::cin >> params.numOfPlayers; std::cin.ignore();

        std::cin >> params.numOfLaps; std::cin.ignore();
        std::cin >> params.numOfBoosts; std::cin.ignore();

        size_t checkpointCount; std::cin >> checkpointCount; std::cin.ignore();
        std::cerr << params.numOfPlayers << " "
                  << params.numOfLaps << " "
                  << params.numOfBoosts << " "
                  << params.checkpoints.size() << " " << std::endl;
        Coordinates pos;
        for (size_t i = 0; i < checkpointCount; i++)
        {
            std::cin >> pos.x >> pos.y; std::cin.ignore();
            std::cerr << pos.x <<  " " << pos.y << std::endl;
            params.checkpoints.push_back(pos);
        }

        return params;
    }

    std::vector<Player> readPlayers(size_t numOfPlayers) override
    {
        std::vector<Player> players;

        for (size_t i = 0; i < numOfPlayers; i++)
        {
            players.push_back(readPlayer());
        }

        Player& p = players[0];

        std::cerr << "POS: [" << p.pos.x << ", " << p.pos.y << "]"
                  << " SPEED: [" << p.v.x << ", " << p.v.y << "]" << std::endl;

        return players;
    }

    void executeCommand(const Command& cmd) override
    {
        std::cout << cmd.pos.x << " " << cmd.pos.y << " ";
        std::cerr << "CMD: [" << cmd.pos.x << ", " << cmd.pos.y << ", ";
        if(cmd.thrust.useBoost)
        {
            std::cout << "BOOST" << std::endl;
            std::cerr << "BOOST]" << std::endl;
        }
        else
        {
            std::cout << cmd.thrust.value << std::endl;
            std::cerr << cmd.thrust.value << "]" << std::endl;
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
