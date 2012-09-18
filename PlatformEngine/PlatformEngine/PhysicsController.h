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
	bool isSolid(int tile, int x, int y);
	double checkDownwards(int x, int y, double moveX, double moveY);
	double checkUpwards(int x, int y, double moveX, double moveY);
	double checkRight(int x, int y, double moveX, double moveY);
	double checkLeft(int x, int y, double moveX, double moveY);
	bool isSolidRightStairs(int tile, int x, int y);
	bool isSolidLeftStairs(int tile, int x, int y);
	double getGravitationalAcceleration(int ticks);
	int correctYPosition(int x, int y, int mapValue);
public:
	void gravity(int ticks);
	bool characterOnGround();
	void move();
	PhysicsController(Character * chara, Level * lv);
	PhysicsController(void);
	~PhysicsController(void);
};

