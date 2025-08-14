#pragma once
#include <minefield/Player.h>


void printBoard(const gameConstants::Board& board, int rows, int cols, const Player& currentPlayer, bool showAll = false);
void printColumnNumbers(int cols);
void printRowNumber(int row);
std::string const getBoardCharPlayer(gameConstants::CellState cellState, bool isUserMine);
std::string const getBoardCharOmniscient(gameConstants::CellState cellState);