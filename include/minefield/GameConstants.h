#pragma once
#include <vector>
#define DEBUG_MODE 

namespace gameConstants {
    enum class CellState {
        EMPTY,
        PLAYER1_MINE,
        PLAYER2_MINE,
        GUESSED_EMPTY,
        DETECTED_MINE
    };

    struct Coordinates {
        unsigned int row = 0;
        unsigned int col = 0;
    };

    using Board = std::vector<std::vector<CellState>>;

    #ifdef DEBUG_MODE
        static const int MIN_BOARD_DIMENSION_CONST = 3;
    #else
        static const int MIN_BOARD_DIMENSION_CONST = 24;
    #endif

    static const int MAX_BOARD_DIMENSION_CONST = 50;
    static const int MIN_MINES_CONST = 3;
    static const int MAX_MINES_CONST = 8;
}
