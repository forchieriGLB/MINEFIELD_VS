#include <minefield/Game.h> 

#include <gtest/gtest.h>

namespace minefield::winConditions::tests {
TEST(CheckWinCondition, should_return_none_if_no_player_detected_all_mines)
{
    Player p1{"P1", 0, 0, {}, gameConstants::CellState::PLAYER1_MINE};
    Player p2{"P2", 0, 0, {}, gameConstants::CellState::PLAYER2_MINE};

    auto result = checkWinCondition(p1, p2, 3);

    EXPECT_EQ(result, WinCheckResult::None);
}

TEST(CheckWinCondition, should_return_winP1_if_player1_detected_all_mines)
{
    Player p1{"P1", 0, 3, {}, gameConstants::CellState::PLAYER1_MINE};
    Player p2{"P2", 0, 0, {}, gameConstants::CellState::PLAYER2_MINE};

    auto result = checkWinCondition(p1, p2, 3);

    EXPECT_EQ(result, WinCheckResult::WinP1);
}

TEST(CheckWinCondition, should_return_draw_if_both_players_detected_all_mines)
{
    Player p1{"P1", 0, 3, {}, gameConstants::CellState::PLAYER1_MINE};
    Player p2{"P2", 0, 3, {}, gameConstants::CellState::PLAYER2_MINE};

    auto result = checkWinCondition(p1, p2, 3);

    EXPECT_EQ(result, WinCheckResult::Draw);
}

}
