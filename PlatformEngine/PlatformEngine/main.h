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

SDL_Surface *loadImage(std::string filename);