#include "Character.h"
#include "Level.h"
#pragma once
class PhysicsController
{
private: 
	Level * level;
	Character * character;
	bool charOnGround;
public:
	void gravity(int ticks);
	bool characterOnGround();
	void move();
	PhysicsController(Character * chara, Level * lv);
	PhysicsController(void);
	~PhysicsController(void);
};

