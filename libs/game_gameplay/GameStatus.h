#pragma once

class Game
{
public:
	Game(int hp);
	int getHp();
	void takeDamage(int amount);
private:
		int mHp;
};