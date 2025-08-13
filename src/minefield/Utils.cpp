#include <minefield/Utils.h>
#include <iostream>
#include <limits>

void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void clearConsoleBuffer() {
    static char const *const kClearConsoleBufferComand = "cls";
    system(kClearConsoleBufferComand);
}

int getValidIntInput(const std::string& prompt, int minVal, int maxVal) {
    int value;
    bool valueValid = false;
    while (!valueValid) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || ((value < minVal) || (value > maxVal))) {
            std::cout << "Invalid entry. Please, insert a value between: " << minVal << " and " << maxVal << ".\n";
            std::cin.clear();
            clearInputBuffer();
        } else {
            clearInputBuffer();
            valueValid = true;
        }
    }
    return value;
}
