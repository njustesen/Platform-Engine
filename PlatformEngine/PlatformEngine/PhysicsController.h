#include "Character.h"
#include "Level.h"
#pragma once
class PhysicsController
{
private: 
	Level * level;
	Character * character;
	bool charOnGround;
	double round(double number);
	bool isSolid(int tile);
	int checkDownwards(int x, int y, int moveX, int moveY);
	int checkUpwards(int x, int y, int moveX, int moveY);
	int checkRight(int x, int y, int moveX, int moveY);
	int checkLeft(int x, int y, int moveX, int moveY);
public:
	void gravity(int ticks);
	bool characterOnGround();
	void move();
	PhysicsController(Character * chara, Level * lv);
	PhysicsController(void);
	~PhysicsController(void);
};

