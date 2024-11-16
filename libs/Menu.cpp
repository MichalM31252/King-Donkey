#include "Menu.h"

Menu::Menu(int x, int y, int width, int height, int scale, const std::vector<std::string>& options)
    : x(x), y(y), width(width), height(height), selectedOptionIndex(0), scaleOfText(scale), optionList(options) {}


void Menu::selectPreviousOption() {
    if (selectedOptionIndex > 0) selectedOptionIndex--;
}

void Menu::selectNextOption() {
    if (selectedOptionIndex < optionList.size() - 1) selectedOptionIndex++;
}