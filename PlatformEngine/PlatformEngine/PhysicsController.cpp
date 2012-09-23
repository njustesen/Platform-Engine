#include "PhysicsController.h"
#include "Character.h"
#include "Level.h"
#include "main.h"
#include <string>
#include <vector>
using namespace std;

PhysicsController::PhysicsController(void)
{
}

PhysicsController::PhysicsController(Character * chara, vector<GameObject*> * objects, Level * lv)
{
	character = chara;
	level = lv;
	charOnGround = false;
	gameObjects = objects;
}

double round(double number)
{
    return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
}

double PhysicsController::getGravitationalAcceleration(int ticks){
	return ((double)1000/ticks)/200;
}

void PhysicsController::gravity(int ticks){
	for(int i = 0; i < gameObjects->size(); i++){
		if (!gameObjects->at(i)->isOnGround()){
			double yMove = gameObjects->at(i)->getYMovement() + getGravitationalAcceleration(ticks);
			gameObjects->at(i)->setYMovement(yMove);
		}
	}
}

bool PhysicsController::isSolidRightStairs(int tile, int x, int y){
	int relX = x - ((x / TILE_SIZE) * TILE_SIZE);
	int relY = y - ((y / TILE_SIZE) * TILE_SIZE);

	if (relY > relX){
		return true;
	}
	return false;
}

bool PhysicsController::isSolidLeftStairs(int tile, int x, int y){
	int relX = x - ((x / TILE_SIZE) * TILE_SIZE);
	int relY = y - ((y / TILE_SIZE) * TILE_SIZE);

	if (relY > TILE_SIZE - relX){
		return true;
	}
	return false;
}

bool PhysicsController::isDeadly(int tile, string dir){
	if (tile==8 && dir=="down"){
		return true;
	}
	if (tile==9 && dir=="up"){
		return true;
	}
	return false;
}

bool PhysicsController::isSolid(int tile, int x, int y, string dir){
	switch(tile){
	case 0: return false;
	case 6: return isSolidRightStairs(tile, x, y);
	case 7: return isSolidLeftStairs(tile, x, y);
	case 10: return false;
	}
	return true;
}

int PhysicsController::correctYPosition(int x, int y, int mapValue){
	int relX = x - ((x / TILE_SIZE) * TILE_SIZE);
	int relY = y - ((y / TILE_SIZE) * TILE_SIZE);

	if (mapValue == 1){
		return (y / TILE_SIZE) * TILE_SIZE;
	} else if (mapValue == 6){
		y += relX - relY;
		return y;
	} else if (mapValue == 7){
		y -= (relX) - (TILE_SIZE - relY);
		return y;
	}
	return (y / TILE_SIZE) * TILE_SIZE;
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
		int mapValue = level->at(newRealX / TILE_SIZE, newRealY / TILE_SIZE);
		if (isSolid(mapValue, newRealX, newRealY, "down")){
			// Correct position
			newRealY = correctYPosition(newRealX, newRealY, mapValue);
			// Deadly?
			if (isDeadly(mapValue, "down")){
				character->die();
			} else if (character->getBounceEffect() > 0 && moveY > 1.6f){ // Bounce??
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
		int mapValue = level->at(newRealX / TILE_SIZE, newRealY / TILE_SIZE);
		if (isSolid(mapValue, newRealX, newRealY, "up")){
			// Correct position
			newRealY = min(realY, (newRealY / TILE_SIZE) * TILE_SIZE + TILE_SIZE);
			// Deadly?
			if (isDeadly(mapValue, "up")){
				character->die();
			} else if (character->getBounceEffect() > 0){
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
		int mapValue = level->at(newRealX / TILE_SIZE, newRealY / TILE_SIZE);
		if (isSolid(mapValue, newRealX, newRealY, "right")){
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
		int mapValue = level->at(newRealX / TILE_SIZE, newRealY / TILE_SIZE);
		if (isSolid(mapValue, newRealX, newRealY, "left")){
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

	if (character->isAlive()){

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

	} else {
		character->setCurrentAnim(character->getDyingAnim());
	}
	
}

bool PhysicsController::characterOnGround(){
	return charOnGround;
}

PhysicsController::~PhysicsController(void)
{
}
