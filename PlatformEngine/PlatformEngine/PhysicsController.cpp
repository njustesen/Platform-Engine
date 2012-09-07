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

void PhysicsController::gravity(int ticks){
	if (!charOnGround){
		float yMove = character->getYMovement() + ((float)1000/ticks)/200;
		//
		character->setYMovement(yMove);
	}
}

void PhysicsController::move(){
	// New position
	int newX = character->getX() + character->getXMovement();
	int newY = character->getY() + character->getYMovement();

	// Can char move vertical down?
	if (character->getYMovement() != 0){
		if (level->at(newX/TILE_SIZE, newY/TILE_SIZE) != 0){
			// Move down to tile
			newY = newY/TILE_SIZE;
			character->setY(newY*TILE_SIZE);
			character->setYMovement(0);
			charOnGround = true;
		} else {
			charOnGround = false;
			character->setY(newY);
		}
	}
	/*
	// Can char move right?
	if (character->getXMovement() > 0){
		if (level->at( (newX + character->getWidth()/2) / TILE_SIZE,
						newY/TILE_SIZE) != 0){

			// Move to tile
			newX = (newX + character->getWidth()/2) / TILE_SIZE;
			character->setX(newX * TILE_SIZE);
			character->setXMovement(0);
		}
	}

	// Can char move left?
	if (character->getXMovement() < 0){
		if (level->at( (newX - character->getWidth()/2) / TILE_SIZE,
						newY/TILE_SIZE) != 0){

			// Move to tile
			newX = (newX - character->getWidth()/2) / TILE_SIZE;
			character->setX(newX * TILE_SIZE);
			character->setXMovement(0);
		}
	}
	*/

}

bool PhysicsController::characterOnGround(){
	return charOnGround;
}

PhysicsController::~PhysicsController(void)
{
}
