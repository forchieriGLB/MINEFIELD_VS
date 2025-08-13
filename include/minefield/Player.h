#pragma once
#include <string>
#include <vector>
#include <minefield/GameConstants.h>

struct Player {
    std::string name;
    int minesToPlace = 0;
    int detectedMines = 0;
    std::vector<gameConstants::Coordinates> myCurrentMines;
    gameConstants::CellState myMineState;
};
