#include "MapController.h"
#include "Sprite.h"
#include "SDL.h"
#include <string>
#include "SDL_image.h"
#include <iostream>
#include <fstream>
using namespace std;

const extern int SCREEN_WIDTH;
const extern int SCREEN_HEIGHT;
const extern int SCREEN_BPP;
const extern int LEVEL_HEIGHT;
const extern int LEVEL_WIDTH;
const extern int TILE_SIZE;
const extern int CAMERA_DELAY;
const extern int CHARACTER_JUMP_POWER;

SDL_Surface *loadImage(std::string filename);