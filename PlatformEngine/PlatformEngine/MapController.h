#include "Sprite.h"
#include "SDL.h"
#include "Level.h"
#include <string>
#include "SDL_image.h"
#include <vector>
using namespace std;

#pragma once
class MapController
{
private: 
	Level level;
	Sprite background;
	int intFromChar(char c);
public:
	Level *getLevel();
	SDL_Surface *getTileImage(int tile);
	Sprite *getBackground();
	void loadLevel(string levelName);
	MapController(void);
	~MapController(void);
};

