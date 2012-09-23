#include "Sprite.h"
#include "GameObject.h"
using namespace std;

#pragma once
class Character: public GameObject
{
private: 

public:
	void act();
	void setupAnimations();
	Character(int xpos, int ypos, int w, int h, double spd, double bounceEffect);
	~Character(void);
};

