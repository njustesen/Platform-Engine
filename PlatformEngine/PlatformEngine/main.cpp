#include "SDL.h"
#include <string>
#include "SDL_image.h"
#include "MapController.h"

//The attributes of the screen
const extern int SCREEN_WIDTH = 1280;
const extern int SCREEN_HEIGHT = 800;
const extern int SCREEN_BPP = 32;
SDL_Surface *screen;
MapController mapController;

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
        optimizedImage = SDL_DisplayFormat( loadedImage );
        
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
	mapController.loadLevel("level1");

	return 1;
}

int update(){
	return 1;
}

int draw(){
	//Load the level sprites
	Sprite* bg = mapController.getBackground();
    vector<Sprite> tiles = *mapController.getTiles();
    SDL_Surface* surf = bg->getImage();

	//Apply the background to the screen
	applySurface( 0, 0, surf, screen );

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

	while(1){

		// Update
		if (update() == -1){
			return -1;
		}

		// Draw
		if (draw() == -1){
			return -1;
		}

	}
	
	//Wait 2 seconds
    SDL_Delay( 8000 );
    
    //Quit SDL
    SDL_Quit();
    
    //Return
    return 0;
}

