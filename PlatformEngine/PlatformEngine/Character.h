#include "Sprite.h"

#pragma once
class Character
{
private: 
	int x;
	int y;
	float xMovement;
	float yMovement;
	int width;
	int height;
	int speed;
	Sprite * sprite;
public:
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	int getSpeed();
	float getXMovement();
	float getYMovement();
	void setXMovement(float movement);
	void setYMovement(float movement);
	void setX(int xpos);
	void setY(int ypos);
	Sprite * getSprite();
	Character(void);
	Character(int xpos, int ypos, int height, int width, int spe);
	~Character(void);
};

