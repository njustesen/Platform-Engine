#include "Character.h"
#include "Sprite.h"
#include "main.h"

Character::Character(void)
{
}

Character::Character(int xpos, int ypos)
{
	x = xpos;
	y = ypos;
	sprite = new Sprite (x, y, 32, 32, loadImage("../Assets/Images/char.png"));
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


Character::~Character(void)
{
}
