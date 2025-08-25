#include <gtest/gtest.h>

#include <minefield/Game.h>

namespace minefield::tests
{

void expectCoordsEqual(gameConstants::Coordinates const& a, gameConstants::Coordinates const& b)
{
    EXPECT_EQ(a.row, b.row);
    EXPECT_EQ(a.col, b.col);
}

TEST(GuessResultsTest, should_initialize_with_empty_vectors)
{
    gameLogic::GuessResults results;

    EXPECT_TRUE(results.p1DetectedMines.empty());
    EXPECT_TRUE(results.p2DetectedMines.empty());
    EXPECT_TRUE(results.p1SelfGuessedMines.empty());
    EXPECT_TRUE(results.p2SelfGuessedMines.empty());
    EXPECT_TRUE(results.p1EmptyGuesses.empty());
    EXPECT_TRUE(results.p2EmptyGuesses.empty());
}

TEST(GuessResultsTest, should_store_p1_detected_mines_correctly)
{
    gameLogic::GuessResults results;
    gameConstants::Coordinates coord{1, 2};
    results.p1DetectedMines.push_back(coord);

    ASSERT_EQ(results.p1DetectedMines.size(), 1);
    EXPECT_EQ(results.p1DetectedMines[0].row, coord.row);
    EXPECT_EQ(results.p1DetectedMines[0].col, coord.col);
}

TEST(GuessResultsTest, should_store_p2_self_guessed_mines_correctly)
{
    gameLogic::GuessResults results;
    gameConstants::Coordinates coord{3, 4};
    results.p2SelfGuessedMines.push_back(coord);

    ASSERT_EQ(results.p2SelfGuessedMines.size(), 1);
    expectCoordsEqual(results.p2SelfGuessedMines[0], coord);
}

TEST(GuessResultsTest, should_store_empty_guesses_separately_for_each_player)
{
    gameLogic::GuessResults results;
    gameConstants::Coordinates coord1{0, 0};
    gameConstants::Coordinates coord2{1, 1};

    results.p1EmptyGuesses.push_back(coord1);
    results.p2EmptyGuesses.push_back(coord2);

    ASSERT_EQ(results.p1EmptyGuesses.size(), 1);
    ASSERT_EQ(results.p2EmptyGuesses.size(), 1);
    expectCoordsEqual(results.p1EmptyGuesses[0], coord1);
    expectCoordsEqual(results.p2EmptyGuesses[0], coord2);
}

TEST(GuessResultsTest, should_support_multiple_coordinates)
{
    gameLogic::GuessResults results;
    results.p1DetectedMines.push_back({0, 0});
    results.p1DetectedMines.push_back({0, 1});
    results.p1DetectedMines.push_back({0, 2});

    EXPECT_EQ(results.p1DetectedMines.size(), 3);
    EXPECT_EQ(results.p1DetectedMines[1].row, 0);
    EXPECT_EQ(results.p1DetectedMines[1].col, 1);
}

} // namespace minefield::tests