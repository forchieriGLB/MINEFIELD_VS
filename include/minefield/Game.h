#pragma once
#include <minefield/Player.h>
#include <minefield/Board.h>
#include <minefield/Utils.h>

namespace gameLogic {
    gameConstants::Coordinates getCoordinatesFromUser(const std::string& prompt, int maxRow, int maxCol);

    void rebuildPlayersCurrentMines(Player& p1, Player& p2, int boardRows, int boardCols, const gameConstants::Board& gameBoard);

    struct PlacementResult {
        std::vector<gameConstants::Coordinates> eliminatedMines; 
    };

    PlacementResult processMinePlacements(gameConstants::Board& gameBoard, Player& p1, Player& p2, int boardRows, int boardCols, const std::vector<gameConstants::Coordinates>& p1PlacementsAttempt, const std::vector<gameConstants::Coordinates>& p2PlacementsAttempt);

    void processPlayerGuesses(Player& guessingPlayer, 
                            Player& opponentPlayer,
                            const std::vector<gameConstants::Coordinates>& guesses,
                            gameConstants::Board& gameBoard,
                            std::vector<gameConstants::Coordinates>& detectedMines,
                            std::vector<gameConstants::Coordinates>& selfGuessedMines,
                            std::vector<gameConstants::Coordinates>& emptyGuesses);
                            
    struct GuessResults {
        std::vector<gameConstants::Coordinates> p1DetectedMines;
        std::vector<gameConstants::Coordinates> p2DetectedMines;
        std::vector<gameConstants::Coordinates> p1SelfGuessedMines;
        std::vector<gameConstants::Coordinates> p2SelfGuessedMines;
        std::vector<gameConstants::Coordinates> p1EmptyGuesses;
        std::vector<gameConstants::Coordinates> p2EmptyGuesses;
    };

    GuessResults processGuesses(Player& p1, Player& p2, gameConstants::Board& gameBoard, int boardRows, int boardCols,
                                const std::vector<gameConstants::Coordinates>& p1Guesses,
                                const std::vector<gameConstants::Coordinates>& p2Guesses);

    std::vector<gameConstants::Coordinates> getPlayerActionCoordinates(Player& player, int boardRows, int boardCols, const gameConstants::Board& gameBoard, 
                                                                    const std::string& actionDescription, int numActionsToPerform);

    void reportPlayerGuessResults(const Player& guessingPlayer, const Player& opponentPlayer, const GuessResults& allResults);
}

enum class WinCheckResult { 
    None, 
    Draw, 
    WinP1, 
    WinP2 
};

WinCheckResult checkWinCondition(const Player& p1, const Player& p2, int totalMines);

namespace prints {
    void printWinner(Player const& winner, Player const& loser);

    void printEndGameStats(Player const& winner, Player const& loser, const gameConstants::Board& board, int rows, int cols);

    void printPlaceMinesText(const Player& p);

    void printGuessText(const Player& p);
}

void runMainLoop();
