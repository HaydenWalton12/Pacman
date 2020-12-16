#pragma once
#include "S2D/S2D.h"
using namespace S2D;
struct EnemyMovement
{
	Vector2* position;
	Texture2D* _eTexture;
	Rect* _eRect;
	int direction;
	float speed;
	int currentFrameTime;
	int FrameTime = 500;
	int FrameCount;
	int Frame = 0 ;

};

struct Enemy
{

	int frameCount;
	int eFrameTime;
	int eFrame;
	int eCurrentFrameTime;
	Rect* rect;
	Rect* spriteRect;
	Vector2* ePosition;
	Texture2D* eTexture;
	Texture2D* spriteSheet;



};