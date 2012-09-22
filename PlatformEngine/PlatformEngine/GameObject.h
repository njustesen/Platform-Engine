#include "Sprite.h"

#pragma once
class GameObject
{
protected:
	int x;
	int y;
	double xMovement;
	double yMovement;
	int width;
	int height;
	double speed;
	double bounceEffect;
	Sprite * sprite;
public:
	virtual void act() = 0;
	int getWidth();
	int getHeight();
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
	~GameObject(void);
};

