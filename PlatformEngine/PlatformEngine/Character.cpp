#include "Character.h"
#include "Sprite.h"
#include "main.h"
#include "Point2D.h"
#include <vector>
using namespace std;

Character::Character(void)
{
}

Character::Character(int xpos, int ypos, CollisionBox * box, int spe)
{
	x = xpos;
	y = ypos;
	xMovement = 0;
	yMovement = 0;
	speed = spe;
	sprite = new Sprite (x, y,32, 32, loadImage("../Assets/Anim/CharWalkRight/1.png"));
	collisionBox = box;
	bounceEffect = 0.0f;
}

Sprite * Character::getSprite(){
	return sprite;
}

CollisionBox * Character::getCollisionBox(){
	return collisionBox;
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
/*
int Character::getWidth(){
	return width;
}

int Character::getHeight(){
	return height;
}
*/
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
