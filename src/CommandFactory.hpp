#pragma once

#include <functional>
#include "Command.hpp"

struct CommandFactory
{
    CommandFactory(std::function<void(int, int, bool, int)> execute) :
        execute(execute)
    {}

    Command create()
    {
        return Command(execute);
    }

private:
    std::function<void(int, int, bool, int)> execute;
};
