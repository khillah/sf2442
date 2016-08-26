#include <iostream>
#include <vector>
#include <functional>
#include <memory>

#include "Coordinates.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "Command.hpp"

void readPlayer(Player& player, std::shared_ptr<std::vector<Checkpoint>>& checkpoints)
{
    size_t checkpointId;
    Coordinates coords;
    Coordinates velocity;

    std::cin >> coords.x >> coords.y >> velocity.x >> velocity.y >> checkpointId; std::cin.ignore();
    player.update(coords, velocity, &(checkpoints->at(checkpointId)));
}

void readPlayers(Player& me,
                 std::vector<Player>& others,
                 std::shared_ptr<std::vector<Checkpoint>>& checkpoints)
{
    readPlayer(me, checkpoints);
    for (auto& player : others)
    {
        readPlayer(player, checkpoints);
    }
}

void executeCommand(int x, int y, bool boost, int thrust)
{
    std::cout << x << " " << y << " ";
    if(boost)
    {
        std::cout << "BOOST" << std::endl;
    }
    else
    {
        std::cout << thrust << std::endl;
    }
}

Game&& createGame(std::shared_ptr<std::vector<Checkpoint>>& checkpoints)
{
    size_t numOfPlayers; std::cin >> numOfPlayers; std::cin.ignore();

    int laps; std::cin >> laps; std::cin.ignore();
    int boosts; std::cin >> boosts; std::cin.ignore();

    size_t checkpointCount; std::cin >> checkpointCount; std::cin.ignore();
    Coordinates pos;
    for (size_t i = 0; i < checkpointCount; i++)
    {
        std::cin >> pos.x >> pos.y; std::cin.ignore();
        checkpoints->emplace_back(pos);
    }

    Player me(&checkpoints->at(0), boosts);

    Game game(me,
         laps,
         checkpoints,
         CommandFactory(executeCommand),
         std::bind(readPlayers,
                   std::placeholders::_1,
                   std::placeholders::_2,
                   checkpoints));

    game.nextTurn();

    return std::move(game);
}

int main()
{
    std::shared_ptr<std::vector<Checkpoint>> checkpoints;
    Game game = createGame(checkpoints);

    while (true)
    {
        game.tick();
        game.nextTurn();
    }
}
