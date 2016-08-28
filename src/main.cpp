#include "Game.hpp"
#include "IO.hpp"

int main()
{
    IoImpl io;
    Game game(io);

    while (true)
    {
        game.turn();
    }
}
