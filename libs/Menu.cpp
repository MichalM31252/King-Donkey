#include "Menu.h"

Menu::Menu(int x, int y, int width, int height, int scale = 3)
    : x(x), y(y), width(width), height(height), scaleOfText(scale), selectedOptionIndex(0) {
    optionList = { "Resume", "Leaderboard", "Quit" };
}

void Menu::moveUp() {
    if (selectedOptionIndex > 0) selectedOptionIndex--;
}

// Moves the selection down
void Menu::moveDown() {
    if (selectedOptionIndex < optionList.size() - 1) selectedOptionIndex++;
}