#include "Character.h"
#include "Sprite.h"
#include "main.h"
#include "Point2D.h"
#include <vector>
using namespace std;

Character::Character(void)
{
}

Character::Character(int xpos, int ypos, int w, int h, int spe)
	: x(xpos), y(ypos), width(w), height(h), xMovement(0), yMovement(0),
	 speed(spe), sprite(new Sprite(x,y,32,32,loadImage("../Assets/Anim/CharWalkRight/1.png"))),
	 bounceEffect(0)
{
}

Sprite * Character::getSprite(){
	return sprite;
}

int Character::getX(){
	return x;
}

int Character::getY(){
	return y;
}

double Character::getXMovement(){
	return xMovement;
}

double Character::getYMovement(){
	return yMovement;
}

double Character::getBounceEffect(){
	return bounceEffect;
}

void Character::setXMovement(double movement){
	xMovement = movement;
}

void Character::setYMovement(double movement){
	yMovement = movement;
}

int Character::getWidth(){
	return width;
}

int Character::getHeight(){
	return height;
}

int Character::getSpeed(){
	return speed;
}

void Character::setX(int xpos){
	x = xpos;
}

void Character::setY(int ypos){
	y = ypos;
}

Character::~Character(void)
{
}
