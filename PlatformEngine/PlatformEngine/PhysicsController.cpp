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

double PhysicsController::getGravitationalAcceleration(int ticks){
	return ((double)1000/ticks)/200;
}

void PhysicsController::gravity(int ticks){
	if (!charOnGround){
		double yMove = character->getYMovement() + getGravitationalAcceleration(ticks);
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

double PhysicsController::checkDownwards(int x, int y, double moveX, double moveY){
	// Calculate positions
	int realX = x + character->getX();
	int realY = y + character->getY();
	int newRealX = realX + int(moveX);
	int newRealY = realY + int(moveY);

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

double PhysicsController::checkUpwards(int x, int y, double moveX, double moveY){
	// Calculate positions
	int realX = x + character->getX();
	int realY = y + character->getY();
	int newRealX = realX + int(moveX);
	int newRealY = realY + int(moveY);

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

double PhysicsController::checkRight(int x, int y, double moveX, double moveY){
	// Calculate positions
	int realX = x + character->getX();
	int realY = y + character->getY();
	int newRealX = realX + int(moveX);
	int newRealY = realY + int(moveY);

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

double PhysicsController::checkLeft(int x, int y, double moveX, double moveY){
	// Calculate positions
	int realX = x + character->getX();
	int realY = y + character->getY();
	int newRealX = realX + int(moveX);
	int newRealY = realY + int(moveY);

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
	int width = character->getWidth();
	int height = character->getHeight();
	double moveX = character->getXMovement();
	double moveY = character->getYMovement();

	// check for vertical collision
	moveY = checkDownwards(width / 2, 0, 0, moveY);
	moveY = checkDownwards(-width / 2, 0, 0, moveY);
	moveY = checkUpwards(width / 2, -height, 0, moveY);
	moveY = checkUpwards(-width / 2, -height, 0, moveY);

	// check for horizontal collision
	moveX = checkRight(width / 2, -1, moveX, moveY);
	moveX = checkRight(width / 2, -height+1, moveX, moveY);
	moveX = checkLeft((width * (-1)) / 2, -1, moveX, moveY);
	moveX = checkLeft((width * (-1)) / 2, -height+1, moveX, moveY);

	// Update position
	character->setX(character->getX() + int(moveX));
	character->setY(character->getY() + int(moveY));

	// Slow down horizontal movement
	character->setXMovement(moveX*0.85f);
	
}

bool PhysicsController::characterOnGround(){
	return charOnGround;
}

PhysicsController::~PhysicsController(void)
{
}
