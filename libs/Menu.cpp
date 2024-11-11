#include "Menu.h"

Menu::Menu(int x, int y, int width, int height, int scale = 3)
    : x(x), y(y), width(width), height(height), scale(scale), selectedOption(0) {
    options = { "Resume", "Leaderboard", "Quit" };
}

void Menu::moveUp() {
    if (selectedOption > 0) selectedOption--;
}

// Moves the selection down
void Menu::moveDown() {
    if (selectedOption < options.size() - 1) selectedOption++;
}