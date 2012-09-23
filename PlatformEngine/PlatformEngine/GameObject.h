#include "Sprite.h"
#include "Animation.h"

#pragma once
class GameObject
{
protected:
	int x;
	int y;
	bool alive;
	bool onGround;
	double xMovement;
	double yMovement;
	int width;
	int height;
	double speed;
	double bounceEffect;
	Animation * walkingRight;
	Animation * walkingLeft;
	Animation * dying;
	Animation * currentAnimation;
public:
	virtual void act() = 0;
	void die();
	void setOnGround(bool ground);
	int getWidth();
	int getHeight();
	int getX();
	int getY();
	void setX(int xpos);
	void setY(int ypos);
	Animation * getCurrentAnim();
	Animation * getRightAnim();
	Animation * getLeftAnim();
	Animation * getDyingAnim();
	void setWalkingRightAnim(Animation * animation);
	void setWalkingLeftAnim(Animation * animation);
	void setDyingAnim(Animation * animation);
	void setCurrentAnim(Animation * animation);
	double getSpeed();
	double getXMovement();
	double getYMovement();
	void setXMovement(double movement);
	void setYMovement(double movement);
	double getBounceEffect();
	bool isAlive();
	bool isOnGround();
	~GameObject(void);
};

