#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

const double FiveDegreesInRadians = 0.0872664626;
const double NinetyDegreesInRadians = 1.57079633;

struct Position
{
    int x;
    int y;
};

struct Player
{
    Position pos;
    Position v;
    double angle;
    int previousCheckpointId;
    int nextCheckpointId;
    int availableBoosts;
};

struct Game
{
    int laps;
    int boosts;
    std::vector<Position> checkpoints;
    std::vector<double> expectedAngle;
    std::vector<Player> players;
    int remainingLaps;
    int boostsPerLap;
    int remainingBoosts;
    int longestPathEnd;
    bool emergencyBoost;
};

struct Command
{
    Position pos;
    bool useBoost;
    int thrust;
};

void execute(const Command& cmd)
{
    cout << cmd.pos.x << " " << cmd.pos.y << " ";
    if(cmd.useBoost)
    {
        cout << "BOOST" << endl;
    }
    else
    {
        cout << cmd.thrust << endl;
    }
}

int pathLength(const Position& a, const Position& b)
{
    return (int)(sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

Position expectedVector(const Position& a, const Position& b)
{
    Position pos;
    pos.x = b.x - a.x;
    pos.y = b.y - a.y;
    return pos;
}

void readConfig(Game& game)
{
    int players;
    cin >> players; cin.ignore();
    game.players.resize(players);

    cin >> game.laps; cin.ignore();
    cin >> game.boosts; cin.ignore();
    game.remainingLaps = game.laps + 1;
    game.remainingBoosts = game.boosts;

    Position pos;
    int checkpointCount;
    cin >> checkpointCount; cin.ignore();
    for (int i = 0; i < checkpointCount; i++)
    {
        cin >> pos.x >> pos.y; cin.ignore();
        game.checkpoints.push_back(pos);
    }

    for(int i = 0; i < checkpointCount - 1; i++)
    {
        Position pos = expectedVector(game.checkpoints[i], game.checkpoints[i + 1]);
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
}

void readPlayers(std::vector<Player>& players)
{
    for (auto& player : players)
    {
        player.previousCheckpointId = player.nextCheckpointId;
        cin >> player.pos.x >> player.pos.y >> player.v.x >> player.v.y >> player.nextCheckpointId; cin.ignore();
        player.angle = atan2(player.v.y, player.v.x);
    }
}

bool isOnLongestPath(const Game& game)
{
    return game.players[0].nextCheckpointId == game.longestPathEnd;
}

bool isBoostAvailable(const Game& game)
{
    return game.players[0].availableBoosts > 0;
}

double angleDifference(const Game& game)
{
    Position vector = expectedVector(game.players[0].pos, game.checkpoints[game.players[0].nextCheckpointId]);
    return fabs(atan2(vector.y, vector.x) - game.players[0].angle);
}

bool angleIsProperForBoost(const Game& game)
{
    return angleDifference(game) < FiveDegreesInRadians;
}

bool shouldUseBoost(Game& game)
{
    return angleIsProperForBoost(game) && (game.emergencyBoost || isOnLongestPath(game) && isBoostAvailable(game));
}

bool isLastLap(const Game& game)
{
    return game.remainingLaps == 0;
}

bool isLastCheckpoint(const Game& game)
{
    return game.players[0].nextCheckpointId == 0;
}

void onCheckpointChange(Game& game)
{
    if(isLastLap(game) and isLastCheckpoint(game))
    {
        game.emergencyBoost = true;
    }
}

void onNewLap(Game& game)
{
    game.players[0].availableBoosts = game.boostsPerLap;
}

int calculateThrust(const Game& game)
{
    double diff = angleDifference(game);
    int distance = pathLength(game.players[0].pos, game.checkpoints[game.players[0].nextCheckpointId]);

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

Command calculateCommand(Game& game)
{
    Command cmd{};

    if(shouldUseBoost(game) and game.players[0].availableBoosts > 0)
    {
        cmd.useBoost = true;
        game.remainingBoosts--;
        game.players[0].availableBoosts--;
    }
    else
    {
        cmd.thrust = calculateThrust(game);
    }

    cmd.pos = game.checkpoints[game.players[0].nextCheckpointId];

    return cmd;
}

int main()
{
    Game game;
    readConfig(game);

    Command cmd;
    while (true)
    {
        readPlayers(game.players);
        if(game.players[0].previousCheckpointId != game.players[0].nextCheckpointId)
        {
            if(game.players[0].nextCheckpointId == 1)
            {
                onNewLap(game);
            }
            onCheckpointChange(game);
        }
        execute(calculateCommand(game));
    }
}

