#include "MapController.h"
#include "Sprite.h"
#include "SDL.h"
#include "main.h"
#include "Level.h"
#include <string>
#include "SDL_image.h"
#include <iostream>
#include <fstream>
using namespace std;

//The surfaces that will be used

MapController::MapController(void)
{
	
}

int MapController::intFromChar(char c){
	switch(c){
		case '0' : return 0;
		case '1' : return 1;
		case '2' : return 2;
		case '3' : return 3;
		case '4' : return 4;
		case '5' : return 5;
		case '6' : return 6;
		case '7' : return 7;
		case '8' : return 8;
		case '9' : return 9;
	}
	return 0;
}

void MapController::loadLevel(string levelName){
	// Load background
	SDL_Surface surf = *loadImage("../Assets/Images/background.png");
	Sprite bg = Sprite(0,0,0,0, surf);
	background = bg;

	// Load level
	level.clear();
	string line;
	ifstream myfile ("../Levels/level1.lv");
	if (myfile.is_open()){
		int y = 0;
		while (myfile.good()){
			getline (myfile,line);
			for (int x = 0; x < line.length(); x++){
				int xx = x/2;
				if (line.at(x) != 9){
					level.insert(xx, y, intFromChar(line.at(x)));
				}
			}
			y++;
		}
		myfile.close();	
	} else cout << "Unable to open file"; 
}

Sprite *MapController::getBackground(){
	return &background;
}

Level *MapController::getLevel(){
	return &level;
}

SDL_Surface *MapController::getTileImage(int tile){
	string img = "../Assets/Images/";
	switch(tile){
	case 1 : img.append("1.png"); break;
	case 2 : img.append("2.png"); break;
	case 3 : img.append("3.png"); break;
	case 4 : img.append("4.png"); break;
	case 5 : img.append("5.png"); break;
	case 6 : img.append("6.png"); break;
	case 7 : img.append("7.png"); break;
	case 8 : img.append("8.png"); break;
	case 9 : img.append("9.png"); break;
	}
	return loadImage(img);
}

MapController::~MapController(void)
{
}
