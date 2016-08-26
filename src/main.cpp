#include <vector>
#include <functional>
#include <memory>

#include "Coordinates.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "Command.hpp"
#include "IO.hpp"

int main()
{
    IO io;
    Game game(io);

    while (true)
    {
        game.turn();
    }
}
