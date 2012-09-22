#include "Character.h"
#include "Sprite.h"
#include "main.h"
#include "GameObject.h"
#include "Point2D.h"
#include <vector>
using namespace std;

Character::Character(int xpos, int ypos, int w, int h, double spd, double bounceEffect)
{
	x = xpos;
	y = ypos;
	width = w;
	height = h;
	speed = spd;
	bounceEffect = bounceEffect;
	sprite = new Sprite(x,y,32,32,loadImage("../Assets/Anim/CharWalkRight/1.png"));
	xMovement = 0.0;
	yMovement = 0.0;
}

void Character::act(){}


Character::~Character(void)
{
}
