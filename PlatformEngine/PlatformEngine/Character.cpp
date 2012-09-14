#include "Character.h"
#include "Sprite.h"
#include "main.h"
#include "Point2D.h"
#include <vector>
using namespace std;

Character::Character(void)
{
}

Character::Character(int xpos, int ypos, int hei, int wid, int spe, vector<Point2D*> * points)
{
	x = xpos;
	y = ypos;
	height = hei;
	width = wid;
	xMovement = 0;
	yMovement = 0;
	speed = spe;
	sprite = new Sprite (x, y,32, 32, loadImage("../Assets/Anim/CharWalkRight/1.png"));
	hitPoints = points;
}

Sprite * Character::getSprite(){
	return sprite;
}

vector<Point2D*> * Character::getHitPoints(){
	return hitPoints;
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
