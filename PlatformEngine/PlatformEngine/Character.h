#include "Sprite.h"
#include "GameObject.h"
using namespace std;

#pragma once
class Character: public GameObject
{
private: 

public:
	void act();
	/*
	int getHeight();
	int getWidth();
	int getX();
	int getY();
	void setX(int xpos);
	void setY(int ypos);
	double getSpeed();
	double getXMovement();
	double getYMovement();
	void setXMovement(double movement);
	void setYMovement(double movement);
	double getBounceEffect();
	Sprite * getSprite();
	*/
	Character(int xpos, int ypos, int w, int h, double spd, double bounceEffect);
	~Character(void);
};

