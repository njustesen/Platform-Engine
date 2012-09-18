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
	CollisionBox * collisionBox;
public:
	int getX();
	int getY();
	int getSpeed();
	double getXMovement();
	double getYMovement();
	double getBounceEffect();
	void setXMovement(double movement);
	void setYMovement(double movement);
	void setX(int xpos);
	void setY(int ypos);
	CollisionBox * getCollisionBox();
	Sprite * getSprite();
	Character(void);
	Character(int xpos, int ypos, CollisionBox * box, int spe);
	~Character(void);
};

