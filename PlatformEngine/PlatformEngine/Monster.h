#include "GameObject.h"
#pragma once
class Monster: public GameObject
{
private:
	int timeSinceLastAttack;
public:
	void act(int ticks);
	void setupAnimations();
	Monster(int xpos, int ypos);
	~Monster(void);
};

