#include "GameStatus.h"

Game::Game(int hp)
{
	mHp = hp;
}

int Game::getHp()
{
	return mHp;
}

void Game::takeDamage(int amount)
{
	mHp -= amount;

	if (mHp < 0)
		mHp = 0;
}