#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../src/Game.hpp"
#include "IoMock.hpp"

#include <memory>

using namespace ::testing;

struct ModuleTests : public Test
{
    void setGameCtorExpectations(const Params& params)
    {
        EXPECT_CALL(ioMock, readParams())
                .WillOnce(Return(params));
    }

    ::testing::StrictMock<IoMock> ioMock;
    std::unique_ptr<Game> game;
    std::vector<Player> players;
};

TEST_F(ModuleTests, test1)
{
    Params params{1, 3, 4,
                  std::vector<Checkpoint>(
                  {
                    {{4105, 7329}},
                    {{13552, 2394}},
                    {{13005, 7161}},
                    {{5621, 2503}}
                  })};
    setGameCtorExpectations(params);
    game = std::make_unique<Game>(ioMock);

    players.push_back({{3873, 6886}, {0, 0}, 1});
    EXPECT_CALL(ioMock, readPlayers(1))
            .WillOnce(Return(players));
    EXPECT_CALL(ioMock, executeCommand(13245, 2818, false, 100));
    game->turn();
}

TEST_F(ModuleTests, test2)
{
    Params params{1, 1, 4,
                  std::vector<Checkpoint>(
                  {
                    {{4105, 7329}}
                  })};
    setGameCtorExpectations(params);
    game = std::make_unique<Game>(ioMock);

    players.push_back({{3873, 6886}, {0, 0}, 0});
    EXPECT_CALL(ioMock, readPlayers(1))
            .WillOnce(Return(players));
    EXPECT_CALL(ioMock, executeCommand(_, _, true, 100));
    game->turn();
}

TEST_F(ModuleTests, test3)
{
    Params params{1, 2, 4,
                  std::vector<Checkpoint>(
                  {
                      {{4105, 7329}},
                      {{13005, 7161}},
                      {{5621, 2503}}
                  })};
    setGameCtorExpectations(params);
    game = std::make_unique<Game>(ioMock);

    players.push_back({{5621, 2503}, {0, 0}, 0});
    EXPECT_CALL(ioMock, readPlayers(1))
            .WillOnce(Return(players));
    EXPECT_CALL(ioMock, executeCommand(4494, 7036, false, 100));
    game->turn();

    players[0] = {{4494, 7036}, {0, 0}, 1};
    EXPECT_CALL(ioMock, readPlayers(1))
            .WillOnce(Return(players));
    EXPECT_CALL(ioMock, executeCommand(12451, 6996, false, 100));
    game->turn();

    players[0] = {{12451, 6996}, {100, 100}, 2};
    EXPECT_CALL(ioMock, readPlayers(1))
            .WillOnce(Return(players));
    EXPECT_CALL(ioMock, executeCommand(5781, 2953, false, 100));
    game->turn();

    players[0] = {{5781, 2953}, {100, 100}, 0};
    EXPECT_CALL(ioMock, readPlayers(1))
            .WillOnce(Return(players));
    EXPECT_CALL(ioMock, executeCommand(4511, 7042, false, 100));
    game->turn();

    players[0] = {{4511, 7042}, {100, 100}, 1};
    EXPECT_CALL(ioMock, readPlayers(1))
            .WillOnce(Return(players));
    EXPECT_CALL(ioMock, executeCommand(12451, 6996, false, 100));
    game->turn();

    players[0] = {{12451, 6996}, {100, 100}, 2};
    EXPECT_CALL(ioMock, readPlayers(1))
            .WillOnce(Return(players));
    EXPECT_CALL(ioMock, executeCommand(5781, 2953, true, 100));
    game->turn();
}
