#pragma once
#include <functional>
#include <memory>
#include <string>
#include <vector>

enum class MenuContinuity {
    BreakFlow = 0,
    ContinueFlow = 1
};

class Menu
{
public:
    void addOption(std::string const& text, std::function<MenuContinuity()> action);
    void display() const;
    void run();

private:
    struct Option
    {
        std::string text;
        std::function<MenuContinuity()> action;
    };
    std::vector<Option> mOptions;
};
