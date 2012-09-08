#include "PhysicsController.h"
#include "Character.h"
#include "Level.h"
#include "main.h"

PhysicsController::PhysicsController(void)
{
}

PhysicsController::PhysicsController(Character * chara, Level * lv)
{
	character = chara;
	level = lv;
	charOnGround = false;
}

double round(double number)
{
    return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
}

void PhysicsController::gravity(int ticks){
	if (!charOnGround){
		float yMove = character->getYMovement() + ((float)1000/ticks)/200;
		//
		character->setYMovement(yMove);
	}
}

void PhysicsController::move(){
	// New position
	int newX = character->getX() + (int)(character->getXMovement());
	int newY = character->getY() + (int)(character->getYMovement());

	// Can char move vertical down?
	if (character->getYMovement() != 0){
		if (level->at(newX/TILE_SIZE, newY/TILE_SIZE) != 0){
			// Move down to tile
			int yTile = newY/TILE_SIZE;
			character->setY(yTile*TILE_SIZE);
			character->setYMovement(0);
			charOnGround = true;
		} else {
			charOnGround = false;
			character->setY(newY);
		}
	}
	
	// Can char move right?
	if (character->getXMovement() > 0){
		if (level->at( (newX + character->getWidth()/2) / TILE_SIZE,
						(newY - character->getHeight()/2) / TILE_SIZE) != 0){

			// Move to tile
			int xTile = (newX + character->getWidth()/2) / TILE_SIZE;
			character->setX(xTile * TILE_SIZE - character->getWidth()/2);
			character->setXMovement(0);
		} else {
			character->setX(newX);
			if (charOnGround){
				character->setXMovement(character->getXMovement()*0.85f);
			}
		}
	}

	// Can char move left?
	if (character->getXMovement() < 0){
		if (level->at( (newX - character->getWidth()/2) / TILE_SIZE,
						(newY - character->getHeight()/2) / TILE_SIZE) != 0){

			// Move to tile
			int xTile = (newX - character->getWidth()/2) / TILE_SIZE;
			character->setX(xTile * TILE_SIZE + TILE_SIZE + character->getWidth()/2);
			character->setXMovement(0);
		} else {
			character->setX(newX);
			if (charOnGround){
				character->setXMovement(character->getXMovement()*0.85f);
			}
		}
	}

}

bool PhysicsController::characterOnGround(){
	return charOnGround;
}

PhysicsController::~PhysicsController(void)
{
}
