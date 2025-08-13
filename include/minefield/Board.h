#pragma once
#include <minefield/Player.h>


void printBoard(const gameConstants::Board& board, int rows, int cols, const Player& currentPlayer, bool showAll = false);
void printColumnNumbers(int cols);
void printRowNumber(int row);
const std::string getBoardChar(gameConstants::CellState cellState, bool isUserMine, bool showAll);
