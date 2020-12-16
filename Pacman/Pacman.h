#pragma once

// If Windows and not in Debug, this will run without a console window
// You can use this to output information when debugging using cout or cerr
#ifdef WIN32 
	#ifndef _DEBUG
		#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	#endif
#endif

#include "S2D/S2D.h"
#include "Player.h"
#include "Enemy.h"
#include "Menu.h"
using namespace S2D;
#define MUNCHIECOUNT 50 
#define Ghost 8 
class Pacman : public Game
{
private://optional - members are private by default

	/* The Player,Enemy,Movement,Menu are our Structs, by using * operator, they are being used to create members for class, by creating pointers.
	The Structs are being pointed too Names, these names will be seen throughout the Pacman.cpp source file as these new class memebers are used to 
	reference the struct to then point to a variable from within a struct.*/
	Player* _pacman;
	Enemy* _munchies[MUNCHIECOUNT];
	EnemyMovement* _ghosts[Ghost];
	Menu* _StartMenu;
	Menu* _PauseMenu;
	Menu* _HelpMenu;
	Menu* _GameOverMenu;
	Menu* _YouWin;

	SoundEffect* _PacmanMunch;
	SoundEffect* _PacmanDeath;
	SoundEffect* _StartUp;
	SoundEffect* _EatMunchie;
	SoundEffect* _EatCherry;
	SoundEffect* _youwin; 

	Menu* _menu;
	Enemy* _cherry;

	//Used to draw
	Vector2* _stringPosition;
	
	
	Direction direction;
	//Input Methods
	void  user_Input(int elapsedTime);


	//check methods - These will check player input and other functions such as collision 
	void CheckPaused(Input::KeyboardState* state, Input::Keys pauseKey);
	void CheckStart(Input::KeyboardState* state, Input::Keys startKey);
	void CheckHelp(Input::KeyboardState* state, Input::Keys helpKey);


	void CheckViewportCollision();
	void CheckGhostCollisions();

	
	//Update methods
	void UpdateGhost(int elapsedTime);
	void UpdatePacman(int elapsedTime);
	void UpdateMunchie(int elapsedTime);
	void UpdateCherry(int elapsedTime);
	void UpdateGhostMovementX(EnemyMovement*, int elapsedTime);
	void UpdateGhostMovementY(EnemyMovement*, int elapsedTime);
	void PollInput();


public:
	bool CollisionCheck(int x1, int y1, int width1, int height1, int x2, int y2 , int widht2 , int height2);
	/*
	This constructor is used to set up the members within the memory when program is executed,
	
	*/
	Pacman(int argc, char* argv[]);

	/*This is the destructor within our program, it will delete all the objects/members off the heap when program stops being executed*/
	virtual ~Pacman();

	/*These Virtual Functions allow us to declare functions as member functions within a class, as seen we have 4, the first one is the destructor function (isnt needed as they are automatically created
	The second is the load content function, third is update, fourth is draw.
	These were created within the class (in result having to be viritual functions) as it will allow us to access variable members within the class easier ,
	and to further for these functions to be automatically 
	to be executed within the program.This further achieves polymorphism.
	 link to these https://www.geeksforgeeks.org/virtual-function-cpp/

	*/
	void virtual LoadContent();
	void virtual Update(int elapsedTime);
	void virtual Draw(int elapsedTime);

	

};