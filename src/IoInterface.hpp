#pragma once

#include <vector>
#include "Player.hpp"
#include "Params.hpp"
#include "Command.hpp"

struct IO
{
    virtual ~IO() = default;
    virtual Params readParams() = 0;
    virtual std::vector<Player> readPlayers(size_t numOfPlayers) = 0;
    virtual void executeCommand(const Command& cmd) = 0;
};
