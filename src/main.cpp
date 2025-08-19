#include <iostream> 
#include <minefield/Game.h>
#include <minefield/Menu.h>

void startPlayerVsPlayer() {
    clearConsoleBuffer();
    runMainLoop();
}

void startPlayerVsAI() {
    std::cout << "\n[TODO] Player vs AI coming soon!\n";
}

void changeLanguage() {
    std::cout << "\n[TODO] Language settings coming soon!\n";
}

int main() {
    Menu menu;
    menu.addOption("Officer vs Officer, the battlefield just got personal.", startPlayerVsPlayer);
    menu.addOption("Colonel vs T-1000, let us see if circuits can bleed.", startPlayerVsAI);
    menu.addOption("Communication Protocol", changeLanguage);
    menu.addOption("Abort Mission", []() { 
        std::cout << "\nIt is over, Colonel...the battlefield is silent. No survivors. Pulling you out...\n"; });

    menu.run();
    return 0;
}