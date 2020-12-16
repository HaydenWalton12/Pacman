#pragma once
#include "S2D/S2D.h"
using namespace S2D;

struct Menu
{//These pointers are used within our draw function to draw our menu
	Texture2D* _menuTexture;
	Texture2D* _background;
	Rect* _mRect;
	Vector2* _menuStringPosition;
	
	Input::Keys interactKey;

	bool keyPressedDown;
	bool inUse;

};