#pragma once
#include "S2D/S2D.h"
using namespace S2D;
struct Player
{
	bool dead;
	bool sound;
	bool moving;
	float speedMultiplier;
	int currentFrameTime;
	int cFrameTime;
	int direction;
	int _cPacmanSpeed;
	int frame;


//Pointers
	Rect* sourceRect; 
	Texture2D* _pTexture;
	Vector2* position;
};

enum Direction { 
	RIGHT,
	UP,
	LEFT,
	DOWN,

};