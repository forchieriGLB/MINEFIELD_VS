#include <minefield/Game.h>
#include <iostream>


namespace gameLogic {
    gameConstants::Coordinates getCoordinatesFromUser(const std::string& prompt, int maxRow, int maxCol) {
        gameConstants::Coordinates coord;
        bool coordinatesValid = false;
        while (!coordinatesValid) {
            int tempRow = -1;
            int tempCol = -1;
            std::cout << prompt;
            std::cout << "Row (0-" << (maxRow - 1) << "):";
            std::cin >> tempRow;
            std::cout << "Column (0-" << (maxCol - 1) << "):";
            std::cin >> tempCol;
            std::cout << '\n';

            coordinatesValid = !std::cin.fail() &&
                            tempRow >= 0 && tempRow < maxRow &&
                            tempCol >= 0 && tempCol < maxCol;

            if (!coordinatesValid) {
                std::cout << "Invalid Coordinates. Please try again.\n";
                std::cin.clear();
                clearInputBuffer();
            } else {
                coord.row = static_cast<unsigned int>(tempRow);
                coord.col = static_cast<unsigned int>(tempCol);
            }
        }
        clearInputBuffer();
        return coord;
    }

    void rebuildPlayersCurrentMines(Player& p1, Player& p2, int boardRows, int boardCols, const gameConstants::Board& gameBoard) {
        for (unsigned int r = 0; r < boardRows; ++r) {
            for (unsigned int c = 0; c < boardCols; ++c) {
                if (gameBoard[r][c] == p1.myMineState) {
                    p1.myCurrentMines.push_back({r, c});
                } else if (gameBoard[r][c] == p2.myMineState) {
                    p2.myCurrentMines.push_back({r, c});
                }
            }
        }
    }

    PlacementResult processMinePlacements(gameConstants::Board& gameBoard, Player& p1, Player& p2, int boardRows, int boardCols,
                                        const std::vector<gameConstants::Coordinates>& p1PlacementsAttempt,
                                        const std::vector<gameConstants::Coordinates>& p2PlacementsAttempt) {
        
        PlacementResult result;
        
        // Clear board from previous turn
        for (int r = 0; r < boardRows; ++r) {
            for (int c = 0; c < boardCols; ++c) {
                if (gameBoard[r][c] == gameConstants::CellState::PLAYER1_MINE ||
                    gameBoard[r][c] == gameConstants::CellState::PLAYER2_MINE) {
                        gameBoard[r][c] = gameConstants::CellState::EMPTY;
                }
            }
        }

        p1.myCurrentMines.clear(); 
        p2.myCurrentMines.clear();

        // place new mines for Player1
        for (const auto& coord : p1PlacementsAttempt) {
            if (gameBoard[coord.row][coord.col] != gameConstants::CellState::GUESSED_EMPTY && 
                gameBoard[coord.row][coord.col] != gameConstants::CellState::DETECTED_MINE) {
                gameBoard[coord.row][coord.col] = gameConstants::CellState::PLAYER1_MINE;
            }
        }
        
        // place mines for Player2
        for (const auto& coord : p2PlacementsAttempt) {
            if (gameBoard[coord.row][coord.col] != gameConstants::CellState::GUESSED_EMPTY && 
                gameBoard[coord.row][coord.col] != gameConstants::CellState::DETECTED_MINE) {
                
                if (gameBoard[coord.row][coord.col] == gameConstants::CellState::PLAYER1_MINE) {
                    gameBoard[coord.row][coord.col] = gameConstants::CellState::EMPTY;
                    result.eliminatedMines.push_back({coord.row, coord.col}); 
                } else {
                    gameBoard[coord.row][coord.col] = gameConstants::CellState::PLAYER2_MINE;
                }
            }
        }

        rebuildPlayersCurrentMines(p1, p2, boardRows, boardCols, gameBoard);
        return result;
    }

    void processPlayerGuesses(Player& guessingPlayer, 
                            Player& opponentPlayer,
                            const std::vector<gameConstants::Coordinates>& guesses,
                            gameConstants::Board& gameBoard,
                            std::vector<gameConstants::Coordinates>& detectedMines,
                            std::vector<gameConstants::Coordinates>& selfGuessedMines,
                            std::vector<gameConstants::Coordinates>& emptyGuesses) {
        // Bound checking done when user imputs data.
        for (const auto& currentGuess : guesses) {
            auto& cell = gameBoard[currentGuess.row][currentGuess.col];

            if (cell == opponentPlayer.myMineState) {
                detectedMines.push_back(currentGuess);
                cell = gameConstants::CellState::DETECTED_MINE;
            } 
            else if (cell == guessingPlayer.myMineState) {
                if (guessingPlayer.minesToPlace > 0) {
                    guessingPlayer.minesToPlace--;
                }
                selfGuessedMines.push_back(currentGuess);
                cell = gameConstants::CellState::GUESSED_EMPTY;
            } 
            else {
                emptyGuesses.push_back(currentGuess);
                cell = gameConstants::CellState::GUESSED_EMPTY;
            }
        }
    }

    GuessResults processGuesses(Player& p1, Player& p2, gameConstants::Board& gameBoard, int boardRows, int boardCols,
                                const std::vector<gameConstants::Coordinates>& p1Guesses,
                                const std::vector<gameConstants::Coordinates>& p2Guesses) {
        GuessResults results;

        processPlayerGuesses(p1, p2, p1Guesses, gameBoard, results.p1DetectedMines, results.p1SelfGuessedMines, results.p1EmptyGuesses);
        processPlayerGuesses(p2, p1, p2Guesses, gameBoard, results.p2DetectedMines, results.p2SelfGuessedMines, results.p2EmptyGuesses);

        p1.detectedMines += results.p1DetectedMines.size();
        p2.detectedMines += results.p2DetectedMines.size();

        p1.myCurrentMines.clear();
        p2.myCurrentMines.clear();
        rebuildPlayersCurrentMines(p1, p2, boardRows, boardCols, gameBoard);

        return results;
    }

    std::vector<gameConstants::Coordinates> getPlayerActionCoordinates(Player& player, int boardRows, int boardCols, const gameConstants::Board& gameBoard, 
                                                                    const std::string& actionDescription, int numActionsToPerform) {
        std::vector<gameConstants::Coordinates> actionsAttempt;
        std::cout << "Insert your " << numActionsToPerform << ' ' << actionDescription << ":\n";

        for (int i = 0; i < numActionsToPerform; ++i) {
            gameConstants::Coordinates coord;
            bool validInput = false;
            while (!validInput) {
                coord = getCoordinatesFromUser(actionDescription + '(' + std::to_string(i + 1) + ")\n", boardRows, boardCols);
                
                bool alreadyUsedThisTurn = false;
                for (const auto& existingCoord : actionsAttempt) { 
                    if (existingCoord.row == coord.row && existingCoord.col == coord.col) {
                        alreadyUsedThisTurn = true;
                        std::cout << "Already used this turn. Try again.\n";
                        break;
                    }
                }
                if (alreadyUsedThisTurn) {
                    continue;
                }
                if (gameBoard[coord.row][coord.col] == gameConstants::CellState::GUESSED_EMPTY ||
                    gameBoard[coord.row][coord.col] == gameConstants::CellState::DETECTED_MINE) {
                    std::cout << "Blocked cell (guessed or mine detected). Try again.\n";
                } else {
                    actionsAttempt.push_back(coord);
                    validInput = true;
                }
            }
        }
        std::cout << player.name << " has finished.\n"; 
        return actionsAttempt;
    }

    void reportPlayerGuessResults(const Player& guessingPlayer, const Player& opponentPlayer, const GuessResults& allResults) {
        std::cout << "\n--- " << guessingPlayer.name << " Turn results ---\n";

        std::vector<gameConstants::Coordinates> const* detectedMines = nullptr;
        std::vector<gameConstants::Coordinates> const* selfGuessedMines = nullptr;
        std::vector<gameConstants::Coordinates> const* emptyGuesses = nullptr;

        if (guessingPlayer.myMineState == gameConstants::CellState::PLAYER1_MINE) {
            detectedMines = &allResults.p1DetectedMines;
            selfGuessedMines = &allResults.p1SelfGuessedMines;
            emptyGuesses = &allResults.p1EmptyGuesses;
        } else {
            detectedMines = &allResults.p2DetectedMines;
            selfGuessedMines = &allResults.p2SelfGuessedMines;
            emptyGuesses = &allResults.p2EmptyGuesses;
        }

        for (const auto& detectedMine : *detectedMines) {
            std::cout << guessingPlayer.name << " detected a mine from " << opponentPlayer.name << " in (" << detectedMine.row << "," << detectedMine.col << ")!\n";
        }
        for (const auto& selfGuessedMine : *selfGuessedMines) {
            std::cout << guessingPlayer.name << " guessed it's own mine in (" << selfGuessedMine.row << "," << selfGuessedMine.col << "). One less!\n";
        }
        for (const auto& emptyGuess : *emptyGuesses) {
            std::cout << guessingPlayer.name << " guessed in (" << emptyGuess.row << "," << emptyGuess.col << ") - empty!\n";
        }
        
        if (!detectedMines->empty()) {
            std::cout << guessingPlayer.name << " detected " << detectedMines->size() << " mine(s) from " << opponentPlayer.name << " this turn.\n";
        }
    }
}

WinCheckResult checkWinCondition(const Player& p1, const Player& p2, int totalMines) {
    WinCheckResult result = WinCheckResult::None;

    bool p1Wins = (p1.detectedMines >= totalMines);
    bool p2Wins = (p2.detectedMines >= totalMines);

    if (p1Wins && p2Wins) {
        result = WinCheckResult::Draw;
    }
    else if (p1Wins) {
        result = WinCheckResult::WinP1;
    }
    else if (p2Wins) {
        result = WinCheckResult::WinP2;
    }

    return result;
}


namespace prints {
    void printWinner(Player const& winner, Player const& loser) {
        std::cout << "Congratulations, " << winner.name << "! You found all of " << loser.name << "'s mines. You won!\n";
    }

    void printEndGameStats(Player const& winner, Player const& loser, const gameConstants::Board& board, int rows, int cols) {
        std::cout << "Mines detected by " << winner.name << ": " << winner.detectedMines << "\n";
        std::cout << "Mines detected by " << loser.name << ": " << loser.detectedMines << "\n";
        printBoard(board, rows, cols, winner, true);
    }

    void printPlaceMinesText(const Player& p) {
        std::cout << "\n--- " << p.name << " time to place mines ---\n";
    }

    void printGuessText(const Player& p) {
        std::cout << "\n--- " << p.name << " time to guess ---\n";
    }
}


// Main loop, links UI and logic 
void runMainLoop() {
    std::cout << "Welcome to Minefield (1v1)!\n----------------------------------\n";
    int boardRows = getValidIntInput("Enter the number of rows (24-50): ", gameConstants::MIN_BOARD_DIMENSION_CONST, gameConstants::MAX_BOARD_DIMENSION_CONST);
    int boardCols = getValidIntInput("Enter the number of columns (24-50): ", gameConstants::MIN_BOARD_DIMENSION_CONST, gameConstants::MAX_BOARD_DIMENSION_CONST);
    int numMinesPerPlayer = getValidIntInput("Enter the amount of mines per player (3-8): ", gameConstants::MIN_MINES_CONST, gameConstants::MAX_MINES_CONST);
    clearConsoleBuffer();

    // Initializes the global board
    gameConstants::Board gameBoard(boardRows, std::vector<gameConstants::CellState>(boardCols, gameConstants::CellState::EMPTY));
    Player player1 = {"Player 1", numMinesPerPlayer, 0, std::vector<gameConstants::Coordinates>(), gameConstants::CellState::PLAYER1_MINE};
    Player player2 = {"Player 2", numMinesPerPlayer, 0, std::vector<gameConstants::Coordinates>(), gameConstants::CellState::PLAYER2_MINE};

    int turn = 1;
    bool gameOver = false;
    WinCheckResult winResult = WinCheckResult::None;

    while (!gameOver) {
        // Insert mines
        std::cout << "\n===== Turn " << turn << " =====\n";
        prints::printPlaceMinesText(player1);
        std::vector<gameConstants::Coordinates> p1PlacementsAttempt = gameLogic::getPlayerActionCoordinates(player1, boardRows, boardCols, gameBoard, "MINES", player1.minesToPlace);
        std::cout << "Press Enter to continue...\n";
        clearInputBuffer();

        prints::printPlaceMinesText(player2);
        std::vector<gameConstants::Coordinates> p2PlacementsAttempt = gameLogic::getPlayerActionCoordinates(player2, boardRows, boardCols, gameBoard, "MINES", player2.minesToPlace);
        std::cout << "Press Enter to continue...\n";
        clearInputBuffer();

        gameLogic::PlacementResult placementInfo = gameLogic::processMinePlacements(gameBoard, player1, player2, boardRows, boardCols, p1PlacementsAttempt, p2PlacementsAttempt);
        for (const auto& eliminatedMine : placementInfo.eliminatedMines) { 
            std::cout << "Mine eliminated in (" << eliminatedMine.row << "," << eliminatedMine.col << ") by superposition!\n";
        }

        // Guesses 
        // PLAYER 1
        prints::printGuessText(player1);
        printBoard(gameBoard, boardRows, boardCols, player1);
        std::vector<gameConstants::Coordinates> p1Guesses = gameLogic::getPlayerActionCoordinates(player1, boardRows, boardCols, gameBoard, "GUESSES", player2.minesToPlace);
        std::cout << "Press Enter to continue...\n";
        clearInputBuffer();

        // PLAYER 2
        prints::printGuessText(player2);
        printBoard(gameBoard, boardRows, boardCols, player2);
        std::vector<gameConstants::Coordinates> p2Guesses = gameLogic::getPlayerActionCoordinates(player2, boardRows, boardCols, gameBoard, "GUESSES", player1.minesToPlace);
        std::cout << "Press Enter to continue and check the results...\n";
        clearInputBuffer();

        gameLogic::GuessResults guessInfo = gameLogic::processGuesses(player1, player2, gameBoard, boardRows, boardCols, p1Guesses, p2Guesses);
        
        std::cout << "\n--- Turn results ---\n"; 

        reportPlayerGuessResults(player1, player2, guessInfo);
        reportPlayerGuessResults(player2, player1, guessInfo);

        // Checks if the game ended 
        winResult = checkWinCondition(player1, player2, numMinesPerPlayer);
        gameOver = (winResult != WinCheckResult::None);

        if (!gameOver) {
            std::cout << "\n--- The game continues! Next turn " << (turn + 1) << " ---" << '\n';
            std::cout << "Press Enter to continue...\n";
            clearInputBuffer();
        }
        turn++;
    }

    // End of the game 
    std::cout << "\n--- End of the Game ---\n";
    switch (winResult) {
        case WinCheckResult::Draw:
            std::cout << "Draw!\n";
            printBoard(gameBoard, boardRows, boardCols, player1, true);
            break;
        case WinCheckResult::WinP1:
            prints::printWinner(player1, player2);
            break;
        case WinCheckResult::WinP2:
            prints::printWinner(player2, player1);
            break;
        default:
            break;
    }
    prints::printEndGameStats(player1, player2, gameBoard, boardRows, boardCols);
}