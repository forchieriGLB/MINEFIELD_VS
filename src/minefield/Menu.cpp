#include <minefield/Menu.h>
#include <minefield/Utils.h>
#include <iostream>
#include <limits>


void Menu::addOption(std::string const& text, std::function<void()> action) {
    mOptions.push_back({text, action});
}

void Menu::display() const {
    std::cout << "Colonel, you are finally here! Command was starting to think you had been vaporized. The battlefield is hotter than a frying pan in hell, and our situation is about as stable as a grenade in a blender. You have the lives of your men, the fate of the mission, and probably the entire free world riding on your shoulders. No pressure. Now grab your gear and try not to get us all killed." << '\n';
    std::cout << "-- -- -- -- -- -- -- -- -- -- -- --[REPORT]-- -- -- -- -- -- -- -- -- -- -- --" << '\n';
    int i = 1; 
    for (auto option : mOptions) {
        std::cout << i++ << ". " << option.text << '\n';
    }
}

void Menu::run() {
    bool exitMenu = false;
    display();
    while (!exitMenu) {
        std::cout << "Colonel, make the call our survival is waiting on your orders:";
        int choice;
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > static_cast<int>(mOptions.size())) {
            std::cin.clear();
            clearInputBuffer();
            std::cout << "\nYou are talking nonsense.\n";
            continue;
        }

        if (mOptions[choice - 1].text == "Abort Mission")
        {
            exitMenu = true;
        }

        mOptions[choice - 1].action();
    }
}