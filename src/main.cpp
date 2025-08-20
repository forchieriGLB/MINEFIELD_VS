#include <iostream> 
#include <minefield/Game.h>
#include <minefield/Menu.h>

MenuContinuity startPlayerVsPlayer()
{
    clearConsoleBuffer();
    runMainLoop();
    return MenuContinuity::ContinueFlow;
}

MenuContinuity startPlayerVsAI()
{
    std::cout << "[TODO] Player vs AI coming soon!\n";
    return MenuContinuity::ContinueFlow;
}

MenuContinuity changeLanguage()
{
    std::cout << "[TODO] Language settings coming soon!\n";
    return MenuContinuity::ContinueFlow;
}

int main() {
    Menu menu;
    menu.addOption("Officer vs Officer, the battlefield just got personal.", startPlayerVsPlayer);
    menu.addOption("Colonel vs T-1000, let us see if circuits can bleed.", startPlayerVsAI);
    menu.addOption("Communication Protocol", changeLanguage);
    menu.addOption("Abort Mission", []() {
        std::cout << "\nIt is over, Colonel...the battlefield is silent. No survivors. Pulling you out...\n";
        return MenuContinuity::BreakFlow;
        });

    menu.run();
    return 0;
}