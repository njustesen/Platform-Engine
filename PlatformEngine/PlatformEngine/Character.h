#include "Sprite.h"
#include "CollisionBox.h"
#include <vector>
using namespace std;

#pragma once
class Character
{
private: 
	int x;
	int y;
	double xMovement;
	double yMovement;
	int width;
	int height;
	int speed;
	double bounceEffect;
	Sprite * sprite;
public:
	int getX();
	int getY();
	int getHeight();
	int getWidth();
	int getSpeed();
	double getXMovement();
	double getYMovement();
	double getBounceEffect();
	void setXMovement(double movement);
	void setYMovement(double movement);
	void setX(int xpos);
	void setY(int ypos);
	Sprite * getSprite();
	Character(void);
	Character(int xpos, int ypos, int w, int h, int spe);
	~Character(void);
};

