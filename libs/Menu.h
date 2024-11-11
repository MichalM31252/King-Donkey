#pragma once

#include <vector>
#include <string>

class Menu {
public:
    int x, y;                        // Top-left corner position of the menu
    int width, height;               // Dimensions of the menu rectangle
    int scale;                       // Scaling factor for the text
    int selectedOption;              // Index of the currently selected option
    std::vector<std::string> options; // List of menu options


	Menu(int x, int y, int width, int height, int scale);
	void moveUp();
	void moveDown();

};
