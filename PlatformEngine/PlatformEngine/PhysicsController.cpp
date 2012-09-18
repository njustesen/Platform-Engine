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

bool PhysicsController::isSolid(int tile){
	switch(tile){
	case 0: return false;
	case 10: return false;
	}
	return true;
}

int PhysicsController::checkDownwards(int x, int y, int moveX, int moveY){
	// Calculate positions
	int realX = x + character->getX();
	int realY = y + character->getY();
	int newRealX = realX + moveX;
	int newRealY = realY + moveY;

	// Check for collisions
	if (moveY > 0){
		// Collision?
		if (isSolid(level->at(newRealX / TILE_SIZE, newRealY / TILE_SIZE))){
			// Correct position
			newRealY = (newRealY / TILE_SIZE) * TILE_SIZE;
			// Bounce?
			if (character->getBounceEffect() > 0 && moveY > 1.6f){
				character->setYMovement(moveY*(-1)*character->getBounceEffect());
			} else {
				character->setYMovement(0);
				charOnGround = true;
			}
		} else {
			charOnGround = false;
		}
	}

	return newRealY - character->getY() - y;
}

int PhysicsController::checkUpwards(int x, int y, int moveX, int moveY){
	// Calculate positions
	int realX = x + character->getX();
	int realY = y + character->getY();
	int newRealX = realX + moveX;
	int newRealY = realY + moveY;

	// Check for collisions
	if (moveY < 0){
		// Collision?
		if (isSolid(level->at(newRealX / TILE_SIZE, newRealY / TILE_SIZE))){
			// Correct position
			newRealY = min(realY, (newRealY / TILE_SIZE) * TILE_SIZE + TILE_SIZE);
			// Bounce?
			if (character->getBounceEffect() > 0){
				character->setYMovement(character->getYMovement()*(-1)*character->getBounceEffect());
			} else {
				if (character->getYMovement() < 0){
					character->setYMovement(0);
				}
			}
		}
	}

	return newRealY - character->getY() - y;
}

int PhysicsController::checkRight(int x, int y, int moveX, int moveY){
	// Calculate positions
	int realX = x + character->getX();
	int realY = y + character->getY();
	int newRealX = realX + moveX;
	int newRealY = realY + moveY;

	// Check for collisions
	if (moveX > 0){
		// Collision?
		if (isSolid(level->at(newRealX / TILE_SIZE, newRealY / TILE_SIZE))){
			// Bounce?
			if (character->getBounceEffect() > 0 && moveX > 1.6f){
				character->setXMovement(moveX*(-1)*character->getBounceEffect());
			} else {
				// Correct position
				newRealX = max(realX, ((newRealX / TILE_SIZE) * TILE_SIZE - 1));
				character->setXMovement(0);
			}
		}
	}

	return newRealX - character->getX() - x;
}

int PhysicsController::checkLeft(int x, int y, int moveX, int moveY){
	// Calculate positions
	int realX = x + character->getX();
	int realY = y + character->getY();
	int newRealX = realX + moveX;
	int newRealY = realY + moveY;

	// Check for collisions
	if (moveX < 0){
		// Collision?
		if (isSolid(level->at(newRealX / TILE_SIZE, newRealY / TILE_SIZE))){
			// Bounce?
			if (character->getBounceEffect() > 0 && moveX > -1.6f){
				character->setXMovement(moveX*(-1)*character->getBounceEffect());
			} else {
				newRealX = min(realX, (newRealX / TILE_SIZE) * TILE_SIZE + TILE_SIZE);
				character->setXMovement(0);
			}
		}
	}

	return newRealX - character->getX() - x;
}

void PhysicsController::move(){

	// get object properties
	charOnGround = false;
	int width = character->getCollisionBox()->getWidth();
	int height = character->getCollisionBox()->getHeight();
	int moveX = character->getXMovement();
	int moveY = character->getYMovement();

	// check for vertical collision
	moveY = checkDownwards((width) / 2, 0, 0, moveY);
	moveY = checkDownwards((width * (-1)) / 2, 0, 0, moveY);
	moveY = checkUpwards((width) / 2, -height, 0, moveY);
	moveY = checkUpwards((width * (-1)) / 2, -height, 0, moveY);

	// check for horizontal collision
	moveX = checkRight(width / 2, -1, moveX, moveY);
	moveX = checkRight(width / 2, -height+1, moveX, moveY);
	moveX = checkLeft((width * (-1)) / 2, -1, moveX, moveY);
	moveX = checkLeft((width * (-1)) / 2, -height+1, moveX, moveY);

	/*
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
			if (isSolid(level->at(newRealX / TILE_SIZE, newRealY / TILE_SIZE))){
				newRealY = (newRealY / TILE_SIZE) * TILE_SIZE;
				// Bounce?
				if (character->getBounceEffect() > 0 && character->getYMovement() > 1.6f){
					character->setYMovement(character->getYMovement()*(-1)*character->getBounceEffect());
				} else {
					character->setYMovement(0);
					charOnGround = true;
				}
			} else charOnGround = false;
		} else if ((int)(character->getYMovement()) < 0 && y == character->getHeight()*-1 +1){
			if (isSolid(level->at(newRealX / TILE_SIZE, newRealY / TILE_SIZE))){
				newRealY = min(realY, (newRealY / TILE_SIZE) * TILE_SIZE + TILE_SIZE);
				if (character->getBounceEffect() > 0){
					character->setYMovement(character->getYMovement()*(-1)*character->getBounceEffect());
				} else {
					if (character->getYMovement() < 0){
						character->setYMovement(0);
					}
				}
			}
		}

		
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
			if (isSolid(level->at(newRealX / TILE_SIZE, newRealY / TILE_SIZE))){
 				if (character->getBounceEffect() > 0 && character->getXMovement() > 1.6f){
					character->setXMovement(character->getXMovement()*(-1)*character->getBounceEffect());
				} else {
					newRealX = max(realX, ((newRealX / TILE_SIZE) * TILE_SIZE - 1));
					character->setXMovement(0);
				}
			}
		} else if ((int)(character->getXMovement()) < 0 && x < 0){
			if (isSolid(level->at(newRealX / TILE_SIZE, newRealY / TILE_SIZE))){
				if (character->getBounceEffect() > 0 && character->getXMovement() > -1.6f){
					character->setXMovement(character->getXMovement()*(-1)*character->getBounceEffect());
				} else {
					newRealX = min(realX, (newRealX / TILE_SIZE) * TILE_SIZE + TILE_SIZE);
					character->setXMovement(0);
				}
			}
		}
		
		moveX = newRealX - character->getX() - x;
	}
	*/

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
