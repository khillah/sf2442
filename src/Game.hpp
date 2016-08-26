#pragma once

#include <vector>
#include <memory>

#include "IO.hpp"
#include "Params.hpp"
#include "Logic.hpp"

struct Game
{
    Game(IO& io) :
        io(io),
        params(io.readParams()),
        logic(params)
    {}

    void turn()
    {
        players = io.readPlayers(params.numOfPlayers);
        io.executeCommand(logic.turn(players[0]));
    }

private:

    IO& io;
    const Params params;
    Logic logic;
    std::vector<Player> players;
};
