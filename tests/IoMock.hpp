#pragma once

#include "gmock/gmock.h"
#include "../src/IoInterface.hpp"

struct IoMock : public IO
{
    MOCK_METHOD0(readParams, Params());
    MOCK_METHOD1(readPlayers, std::vector<Player>(size_t numOfPlayers));
    MOCK_METHOD4(executeCommand, void(int, int, bool ,int));

    void executeCommand(const Command& cmd) override
    {
        executeCommand(cmd.pos.x, cmd.pos.y, cmd.thrust.useBoost, cmd.thrust.value);
    }
};
