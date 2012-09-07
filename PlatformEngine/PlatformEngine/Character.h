#include "Sprite.h"

#pragma once
class Character
{
private: 
	int x;
	int y;
	Sprite * sprite;
public:
	int getX();
	int getY();
	Sprite * getSprite();
	Character(void);
	Character(int xpos, int ypos);
	~Character(void);
};

