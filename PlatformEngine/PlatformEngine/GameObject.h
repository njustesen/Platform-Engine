#include "Sprite.h"
#include "Animation.h"

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
	Animation * walkingRight;
	Animation * walkingLeft;
	Animation * currentAnimation;
public:
	virtual void act() = 0;
	int getWidth();
	int getHeight();
	int getX();
	int getY();
	void setX(int xpos);
	void setY(int ypos);
	Animation * getCurrentAnim();
	Animation * getRightAnim();
	Animation * getLeftAnim();
	void setWalkingRightAnim(Animation * animation);
	void setWalkingLeftAnim(Animation * animation);
	void setCurrentAnim(Animation * animation);
	double getSpeed();
	double getXMovement();
	double getYMovement();
	void setXMovement(double movement);
	void setYMovement(double movement);
	double getBounceEffect();
	Sprite * getSprite();
	~GameObject(void);
};

