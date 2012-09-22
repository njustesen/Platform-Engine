#include "GameObject.h"

Sprite * GameObject::getSprite(){
	return sprite;
}

int GameObject::getX(){
	return x;
}

int GameObject::getY(){
	return y;
}

double GameObject::getXMovement(){
	return xMovement;
}

double GameObject::getYMovement(){
	return yMovement;
}

double GameObject::getBounceEffect(){
	return bounceEffect;
}

void GameObject::setXMovement(double movement){
	xMovement = movement;
}

void GameObject::setYMovement(double movement){
	yMovement = movement;
}

int GameObject::getWidth(){
	return width;
}

int GameObject::getHeight(){
	return height;
}

double GameObject::getSpeed(){
	return speed;
}

void GameObject::setX(int xpos){
	x = xpos;
}

void GameObject::setY(int ypos){
	y = ypos;
}


GameObject::~GameObject(void)
{
}
