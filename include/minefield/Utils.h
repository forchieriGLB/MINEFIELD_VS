#pragma once
#include <string>
#include <minefield/GameConstants.h>

void clearInputBuffer();
void clearConsoleBuffer();
int getValidIntInput(const std::string& prompt, int minVal, int maxVal);