#pragma once

#include <vector>
#include <string>

class Menu {
public:
    int x;
    int y;
    int width;
	int height;
    int scaleOfText;
    int selectedOptionIndex;
    std::vector<std::string> optionList;

	Menu(int x, int y, int width, int height, int scale, const std::vector<std::string>& options);
	void selectPreviousOption();
	void selectNextOption();
};
