#include <minefield/Board.h>
#include <iostream>
#include <iomanip>

void printColumnNumbers(int cols) {
    for (int c = 0; c < cols; ++c) {
        std::cout << std::setw(2) << c << ' ';
    }
    std::cout << '\n';
}

void printRowNumber(int row) {
    std::cout << std::setw(2) << row << ' ';
}

std::string const getBoardCharPlayer(gameConstants::CellState cellState, bool isUserMine) {
    if (isUserMine) {
        return " M ";
    } else if (cellState == gameConstants::CellState::GUESSED_EMPTY) {
        return " X ";
    } else if (cellState == gameConstants::CellState::DETECTED_MINE) {
        return " * ";
    } else {
        return " . ";
    }
}

std::string const getBoardCharOmniscient(gameConstants::CellState cellState) {
        std::string cellStateAsChar;
        switch (cellState) {
        case gameConstants::CellState::PLAYER1_MINE:
            cellStateAsChar = " P1";
            break;
        case gameConstants::CellState::PLAYER2_MINE:
            cellStateAsChar = " P2";
            break;
        case gameConstants::CellState::GUESSED_EMPTY:
            cellStateAsChar = " G ";
            break;
        case gameConstants::CellState::DETECTED_MINE:
            cellStateAsChar = " * ";
            break;
        case gameConstants::CellState::EMPTY:
        default:
            cellStateAsChar = " . ";
            break;
        }
        return cellStateAsChar;
}

void printBoard(const gameConstants::Board& board, int rows, int cols, const Player& currentPlayer, bool showAll) {
    std::cout << "\n--- Game Board " << currentPlayer.name << "(POV) ---\n";
    std::cout << "   ";

    printColumnNumbers(cols);

    // Prints the row grid numbers
    for (int r = 0; r < rows; ++r) {
        printRowNumber(r);

        // For each cell...
        for (int c = 0; c < cols; ++c) {
            gameConstants::CellState cellState = board[r][c];

            bool isUserMine = false;
            // Checks if the actual cell is present in the players list of live mines
            for (const auto& mineCoord : currentPlayer.myCurrentMines) { 
                if (mineCoord.row == r && mineCoord.col == c) {
                    isUserMine = true;
                    break;
                }
            }
            if (showAll) {
                std::cout << getBoardCharOmniscient(cellState);
            } else {
                std::cout << getBoardCharPlayer(cellState, isUserMine);
            }
        }
        std::cout << '\n';
    }
    std::cout << "--------------------------------------\n";
    std::cout << "M: Your mine, X: Guessed (empty), *: Mine detected, .: Unknown\n";
    std::cout << "Mines detected by your opponent: " << currentPlayer.detectedMines << '\n';
}