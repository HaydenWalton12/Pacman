#pragma once

// If Windows and not in Debug, this will run without a console window
// You can use this to output information when debugging using cout or cerr
#ifdef WIN32 
	#ifndef _DEBUG
		#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	#endif
#endif

// Just need to include main header file
#include "S2D/S2D.h"

// Reduces the amount of typing by including all classes in S2D namespace
using namespace S2D;
#define MUNCHIECOUNT 50 
// Declares the Pacman class which inherits from the Game class.
// This allows us to overload the Game class methods to help us
// load content, draw and update our game.


// Structure Definition
struct Player
{
	
	float speedMultiplier;
	int currentFrameTime;
	int cFrameTime;
	int direction;
	int frame;
	Rect* sourceRect;
	Texture2D* texture;
	Vector2* position;
};
struct Enemy
{
	int frameCount;
	Rect* rect;
	Rect* spriteRect;
	Vector2* ePosition;
	Texture2D* eTexture;
	Texture2D* spriteSheet;
	int eFrameTime = 500;
	int eFrame;
	int eCurrentFrameTime;




};
struct Movement
{
	bool _paused;
	bool _pKeyDown;
	bool _start;
	bool _sKeyDown;
};
struct Menu
{
	Texture2D* _menuBackground;
	Rect* _menuRectangle;
	Vector2* _menuStringPosition;



};
class Pacman : public Game
{
private:
	
	Player* _pacman;
	Enemy* _munchies[MUNCHIECOUNT];
	Enemy* _cherry;
	Movement* _move;
	Menu* _menu;

	// Position for Strings
	Vector2* _stringPosition;
	

	//Input Methods
	void  user_Input(int elapsedTime, Input::KeyboardState* state, Input::MouseState* mouseState);

	

	//check methods
	void CheckPaused(Input::KeyboardState* state, Input::Keys pauseKey);
	void CheckStart(Input::KeyboardState* state, Input::Keys startKey);
	void CheckViewportCollision();


	//Update methods
	void UpdatePacman(int elapsedTime);
	void  UpdateMunchie(int elapsedTime);
	void Pacman::UpdateCherry(int elapsedTime);
public:
	
	/// <summary> Constructs the Pacman class. </summary>
	Pacman(int argc, char* argv[]);

	/// <summary> Destroys any data associated with Pacman class. </summary>
	virtual ~Pacman();

	/// <summary> All content should be loaded in this method. </summary>
	void virtual LoadContent();

	/// <summary> Called every frame - update game logic here. </summary>
	void virtual Update(int elapsedTime);

	/// <summary> Called every frame - draw game here. </summary>
	void virtual Draw(int elapsedTime);
bool CollisionCheck(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2);

};