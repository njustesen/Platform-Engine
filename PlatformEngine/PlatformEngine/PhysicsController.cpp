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
		character->setYMovement(yMove);
	}
}

void PhysicsController::move(){

	int moveX = character->getXMovement();
	int moveY = character->getYMovement();

	charOnGround = false;

	// Check vertically
	for(int i = 0; i < character->getHitPoints()->size(); i++){
		// New position
		int x = character->getHitPoints()->at(i)->getX();
		int y = character->getHitPoints()->at(i)->getY();
		int realX = x + character->getX();
		int realY = y + character->getY();
		int newRealX = realX + moveX;
		int newRealY = realY + moveY;

		if ((int)(character->getYMovement()) > 0 && y == 0){
			if (level->at(newRealX / TILE_SIZE, newRealY / TILE_SIZE) != 0){
				newRealY = (newRealY / TILE_SIZE) * TILE_SIZE;
				character->setYMovement(0);
				charOnGround = true;
			} else charOnGround = false;
		} else if ((int)(character->getYMovement()) < 0 && y == character->getHeight()*-1 +1){
			if (level->at(newRealX / TILE_SIZE, newRealY / TILE_SIZE) != 0){
				newRealY = min(realY, (newRealY / TILE_SIZE) * TILE_SIZE + TILE_SIZE);
				if (character->getYMovement() < 0){
					character->setYMovement(0);
				}
			}
		}

		moveY = newRealY - character->getY() - y;
	}

	// Move horizontally
	for(int i = 0; i < character->getHitPoints()->size(); i++){
		// New position
		int x = character->getHitPoints()->at(i)->getX();
		int y = character->getHitPoints()->at(i)->getY();
		int realX = x + character->getX();
		int realY = y + character->getY();
		int newRealX = realX + moveX;
		int newRealY = realY + moveY;
		
		// Check horizontally - return newX if collision
		if ((int)(character->getXMovement()) > 0 && x > 0){
			if (level->at(newRealX / TILE_SIZE, newRealY / TILE_SIZE) != 0){
				newRealX = max(realX, ((newRealX / TILE_SIZE) * TILE_SIZE - 1));
				character->setXMovement(0);
			}
		} else if ((int)(character->getXMovement()) < 0 && x < 0){
			if (level->at(newRealX / TILE_SIZE, newRealY / TILE_SIZE) != 0){
				newRealX = min(realX, (newRealX / TILE_SIZE) * TILE_SIZE + TILE_SIZE);
				character->setXMovement(0);
			}
		}
		
		moveX = newRealX - character->getX() - x;
	}

	// Update position
	character->setX(character->getX() + moveX);
	character->setY(character->getY() + moveY);

	// Slow down horizontal movement
	character->setXMovement(character->getXMovement()*0.85f);
}

bool PhysicsController::characterOnGround(){
	return charOnGround;
}

PhysicsController::~PhysicsController(void)
{
}
