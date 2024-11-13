#pragma once

#include <vector>
#include <string>

class Menu {
public:
    int x, y;
    int width, height;
    int scaleOfText;
    int selectedOptionIndex;
    std::vector<std::string> optionList;


	Menu(int x, int y, int width, int height, int scale);
	void moveUp();
	void moveDown();
};
