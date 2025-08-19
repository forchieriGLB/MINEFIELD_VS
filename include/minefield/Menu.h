#pragma once
#include <functional>
#include <memory>
#include <string>
#include <vector>

class Menu
{
public:
    struct Option
    {
        std::string text;
        std::function<void()> action;
    };
    void addOption(std::string const& text, std::function<void()> action);
    void display() const;
    void run();

private:
    std::vector<Option> mOptions;
};
