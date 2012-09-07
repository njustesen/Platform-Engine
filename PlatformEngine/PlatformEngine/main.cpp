#include "SDL.h"
#include <string>
#include "SDL_image.h"
#include "MapController.h"
#include "InputController.h"
#include "PhysicsController.h"
#include "Level.h"
#include "Character.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//The attributes of the screen
const extern int SCREEN_WIDTH = 800;
const extern int SCREEN_HEIGHT = 600;
const extern int SCREEN_BPP = 32;
const extern int TILE_SIZE = 32;
const extern int VISION = 25;
const extern int CHAR_SPEED = 20;
const extern int LEVEL_HEIGHT = 20;
const extern int LEVEL_WIDTH = 320;
const extern int FPS = 60;

SDL_Surface * screen;
MapController * mapController;
Character * character;
InputController * inputController;
PhysicsController * physicsController;

string intToString(int i){
	stringstream out;
	out << i;
	return out.str();
}

SDL_Surface *loadImage( std::string filename ) {
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;
    
    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;
    
    //Load the image using SDL_image
    loadedImage = IMG_Load( filename.c_str() );
    
    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
        
        //Free the old image
        SDL_FreeSurface( loadedImage );
    }
    
    //Return the optimized image
    return optimizedImage;
}

// Blitting function
void applySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;
    
    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;

	//Blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}

int initGame(){
	//Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return 1;    
    }

	//Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

	//If there was an error in setting up the screen
    if( screen == NULL ){
        return -1;    
    }

	//Set the window caption
    SDL_WM_SetCaption( "Dark something", NULL );

	// Setup controllers
	mapController =  new MapController("level1");

	// Create character
	character = new Character(mapController->getCharX()*TILE_SIZE+TILE_SIZE/2, mapController->getCharY()*TILE_SIZE+TILE_SIZE-1, 32, 32, CHAR_SPEED);

	inputController = new InputController();
	physicsController = new PhysicsController(character, mapController->getLevel());	
	
	return 1;
}

void moveCharacter(int ticks){
	int movement = character->getSpeed()*ticks/100;
	if (inputController->right() && physicsController->characterOnGround()){
		character->setXMovement(movement);
	}
	if (inputController->left() && physicsController->characterOnGround()){
		character->setXMovement(movement*-1);
	}
	if (inputController->jump() && physicsController->characterOnGround()){
		character->setYMovement(-6.5f);
	}
	if (physicsController->characterOnGround()){
		int i = 0;
	}
}

int update(int ticks){
	moveCharacter(ticks);
	physicsController->gravity(ticks);
	physicsController->move();
	return 1;
}

void drawLevel(){
	int xFrom = max(0, (character->getX()/TILE_SIZE)-VISION);
	int xTo = min(LEVEL_WIDTH, (character->getX()/TILE_SIZE)+VISION);

	for(int y = 0; y < LEVEL_HEIGHT; y++){
		for(int x = xFrom; x < xTo; x++){
			int val = mapController->getLevel()->at(x,y);
			if (val > 0 && val < 10){
				applySurface(x*TILE_SIZE,y*TILE_SIZE,mapController->getTileImage(val),screen);
			}
		}
	}
}

void drawCharacter(){

	//Apply the character to the screen
	applySurface( character->getX()-TILE_SIZE/2, character->getY()-TILE_SIZE, character->getSprite()->getImage(), screen);

}

int draw(){
	//Load the background
	Sprite* bg = mapController->getBackground();

	//Apply the background to the screen
	applySurface( 0, 0, bg->getImage(), screen);

	// Apply the level to the screen
	drawLevel();

	// Apply the character to the screen
	drawCharacter();

	//Update the screen
    if( SDL_Flip( screen ) == -1 ){
        return -1;    
    }

	return 1;
}

int main( int argc, char* args[] ){

	// Init game
	if (initGame() == -1){
		return -1;
	}

	// Prepare timer and stuff
	Uint32 oldTime;
	oldTime = SDL_GetTicks();
	SDL_Event sdlEvent;
	bool quit = false;
	Uint32 loopStarted;

	// Game loop
	while(!quit){
		loopStarted = SDL_GetTicks();

		// Poll events
		while(SDL_PollEvent(&sdlEvent)) {
			switch(sdlEvent.type){
				case SDL_QUIT : quit = true; break;
				case SDL_KEYDOWN : inputController->handleKeyEvent(&sdlEvent); break;
				case SDL_KEYUP : inputController->handleKeyEvent(&sdlEvent); break;
			}
		}

		// Update
		int newTime = SDL_GetTicks();
		int TimeSinceLastFrame = newTime - oldTime;
		oldTime = newTime;
		if (update(TimeSinceLastFrame) == -1){
			return -1;
		}

		// Draw
		if (draw() == -1){
			return -1;
		}	

		if ((SDL_GetTicks() - loopStarted) < 1000/FPS){
			SDL_Delay((1000/FPS) - (SDL_GetTicks() - loopStarted));
		}
	}

    //Quit SDL
    SDL_Quit();
    
    //Return
    return 0;
}

