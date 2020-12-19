#include "Pacman.h"
#include <iostream>
#include <sstream>
	int score = 0;
	bool won = false;

Pacman::Pacman(int argc, char* argv[]) : Game(argc, argv)
/*Above is the constructor
within the constructor, this is establishing all member variables (which we created during the intilsation of the class within the headerfile.
This constructor sets up all member variables values
*/
{

	_pacman = new Player();
	_pacman->dead = false;
	_pacman->direction = 0;
	_pacman->currentFrameTime = 0;
	_pacman->frame = 0;
	_pacman->speedMultiplier = 0.1f;
	_pacman->_cPacmanSpeed = 1 ;
	_pacman->cFrameTime = 250;
	
	_cherry = new Enemy;
	_cherry->frameCount = 0;
	_cherry->eCurrentFrameTime = 500;
	_cherry->eFrameTime = 250;

	for (int i = 0; i < Ghost; i++)
	{
		_ghosts[i] = new EnemyMovement();
		_ghosts[i]->speed = 0.025f;
		_ghosts[i]->currentFrameTime = 0;
		_ghosts[i]->Frame = 0;
	}

	int i;
	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		_munchies[i] = new Enemy(); //This is assigning "_munchies" to be a new enemy type, this allows all members of the enemy Struct to be referenced to _munchies[i] by using "->", this further applies to
		//the other functions below

		_munchies[i]->frameCount = rand() % 1;
		_munchies[i]->eCurrentFrameTime = 0;
		_munchies[i]->eFrameTime = rand() % 500 + 50;
	

	}
	
	_StartMenu = new Menu();
	_StartMenu->inUse = true;
	_StartMenu->interactKey = Input::Keys::SPACE;

	_PauseMenu = new Menu();
	_PauseMenu->keyPressedDown = false;
	_PauseMenu->inUse = false;
	_PauseMenu->interactKey = Input::Keys::P;

	_GameOverMenu = new Menu();
	_GameOverMenu->inUse = false;
	_GameOverMenu->interactKey = Input::Keys::R;

	_HelpMenu = new Menu();
	_HelpMenu->keyPressedDown = false;
	_HelpMenu->inUse = false;
	_HelpMenu->interactKey = Input::Keys::H;

	_YouWin = new Menu();



	_PacmanMunch = new SoundEffect();
	_StartUp = new SoundEffect();
	_EatMunchie = new SoundEffect();
	_PacmanDeath = new SoundEffect();
	_EatCherry = new SoundEffect();
	_youwin = new SoundEffect();

	//The arrow operator (->) is used to reference the struct variables to the pointers created in the class Pacman , the pointers being _pacman ,_munchies,_move _menu
	//This constructor is referencing the struct variables to the pointers declared within the class, initalising the variables values for the rest of the program to use.

	Audio::Initialise();
	Graphics::Initialise(argc, argv, this, 900, 900, false, 25, 25, "Pacman", 60);
	Input::Initialise();

	//This generates the game loop which is needed for the game to work and draw eveything ina  contionous loop, till program ends
	Graphics::StartGameLoop();
}

Pacman::~Pacman()
{
	//This is the destructor method, this deletes all members off the memory

	delete _munchies[0]->eTexture;

	int nCount = 0;
	for (int i = 0; i < MUNCHIECOUNT; nCount++)
	{
		delete _munchies[nCount]->ePosition;
		delete _munchies[nCount]->spriteRect;
		delete _munchies[nCount];
	}

	for (int i = 0; i < Ghost; nCount++)
	{
		delete _ghosts[nCount]->position;
		delete _ghosts[nCount]->_eRect;
		delete _ghosts[nCount];
	}
	delete[]_cherry;
	delete[] _munchies;
	delete _pacman->_pTexture;
	delete _pacman->sourceRect;
	

	delete _PacmanMunch;
	delete _EatCherry;
	delete _EatMunchie;
	delete _youwin;
	delete _PacmanDeath;
	delete _StartUp;

	delete _YouWin;
	delete _HelpMenu;
	delete _GameOverMenu;
	delete _PauseMenu;
	delete _StartMenu;

	
}

void Pacman::LoadContent()
{
	//Load Content (which is a virtual function)  creates the menu, pacman , munchie , and cherry via the  by loading in the member variables in the class (the class constructor
	// on top of the program intialsed all s
	

	// Load Pacman
	_pacman->_pTexture = new Texture2D();
	_pacman->_pTexture->Load("Textures/Pacman.png", false);
	_pacman->position = new Vector2(350.0f, 350.0f);
	_pacman->sourceRect = new Rect(0.0f, 0.0f, 32, 32);

	//Initialises Pinky 1 & 2 ghosts
	_ghosts[0] ->_eTexture = new Texture2D();
	_ghosts[0]->_eTexture->Load("Textures/Pinky1Spritesheet.png", false);
	_ghosts[0]->position = new Vector2((rand() % Graphics::GetViewportWidth()), (rand() % Graphics::GetViewportHeight()));
	_ghosts[0]->_eRect = new Rect(0.0f, 0.0f, 24, 24);

	_ghosts[1]->_eTexture = new Texture2D();
	_ghosts[1]->_eTexture->Load("Textures/Pinky2Spritesheet.png", false);
	_ghosts[1]->position = new Vector2((rand() % Graphics::GetViewportWidth()), (rand() % Graphics::GetViewportHeight()));
	_ghosts[1]->_eRect = new Rect(0.0f, 0.0f, 24, 24);


	//Initialise inky 1 & 2 ghosts
	_ghosts[2]->_eTexture = new Texture2D();
	_ghosts[2]->_eTexture->Load("Textures/Inky1Spritesheet.png", false);
	_ghosts[2]->position = new Vector2((rand() % Graphics::GetViewportWidth()), (rand() % Graphics::GetViewportHeight()));
	_ghosts[2]->_eRect = new Rect(0.0f, 0.0f, 24, 24);

	_ghosts[3]->_eTexture = new Texture2D();
	_ghosts[3]->_eTexture->Load("Textures/Inky2Spritesheet.png", false);
	_ghosts[3]->position = new Vector2((rand() % Graphics::GetViewportWidth()), (rand() % Graphics::GetViewportHeight()));
	_ghosts[3]->_eRect = new Rect(0.0f, 0.0f, 24, 24);

	//Initialises Blinky 1 & 2 ghosts
	_ghosts[4]->_eTexture = new Texture2D();
	_ghosts[4]->_eTexture->Load("Textures/Blinky1Spritesheet.png", false);
	_ghosts[4]->position = new Vector2((rand() % Graphics::GetViewportWidth()), (rand() % Graphics::GetViewportHeight()));
	_ghosts[4]->_eRect = new Rect(0.0f, 0.0f, 24, 24);

	_ghosts[5]->_eTexture = new Texture2D();
	_ghosts[5]->_eTexture->Load("Textures/Blinky2Spritesheet.png", false);
	_ghosts[5]->position = new Vector2((rand() % Graphics::GetViewportWidth()), (rand() % Graphics::GetViewportHeight()));
	_ghosts[5]->_eRect = new Rect(0.0f, 0.0f, 24, 24);

	//Initialises Clyde 1 & 2 ghosts
	_ghosts[6]->_eTexture = new Texture2D();
	_ghosts[6]->_eTexture->Load("Textures/Clyde1Spritesheet.png", false);
	_ghosts[6]->position = new Vector2((rand() % Graphics::GetViewportWidth()), (rand() % Graphics::GetViewportHeight()));
	_ghosts[6]->_eRect = new Rect(0.0f, 0.0f, 24, 24);

	_ghosts[7]->_eTexture = new Texture2D();
	_ghosts[7]->_eTexture->Load("Textures/Clyde2Spritesheet.png", false);
	_ghosts[7]->position = new Vector2((rand() % Graphics::GetViewportWidth()), (rand() % Graphics::GetViewportHeight()));
	_ghosts[7]->_eRect = new Rect(0.0f, 0.0f, 24, 24);

	//Start Menu Parameters
	_StartMenu->_menuTexture = new Texture2D();
	_StartMenu->_menuTexture->Load("Textures/StartMenu.png", false);
	_StartMenu->_mRect = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());

	_PauseMenu->_menuTexture = new Texture2D();
	_PauseMenu->_menuTexture->Load("Textures/PauseMenu.png", false);
	_PauseMenu->_mRect = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	
	_GameOverMenu->_menuTexture = new Texture2D();
	_GameOverMenu->_menuTexture->Load("Textures/Gameover.png", false);
	_GameOverMenu->_mRect = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	
	_HelpMenu->_menuTexture = new Texture2D();
	_HelpMenu->_menuTexture->Load("Textures/HelpMenu.png", false);
	_HelpMenu->_mRect = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	
	_YouWin->_menuTexture = new Texture2D();
	_YouWin->_menuTexture->Load("Textures/YouWin.png", false);
	_YouWin->_mRect = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());


	//Generates Pacman Sounds
	_PacmanMunch->Load("Audio/pacman_walk.wav");
	_StartUp->Load("Audio/pacman_startup.wav");
	_EatMunchie->Load("Audio/pacman_eatmunchie.wav");
	_PacmanDeath->Load("Audio/pacman_death.wav");
	_EatCherry->Load("Audio/pacman_eatcherry.wav");
	_youwin->Load("Audio/YouWin.wav");

	// Load Munchie
	int i;
	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		_munchies[i]->eTexture = new Texture2D();
		_munchies[i]->eTexture->Load("Textures/Munchie.png", true);
		_munchies[i]->ePosition = new Vector2((rand() % Graphics::GetViewportWidth()), (rand() % Graphics::GetViewportHeight()));
		_munchies[i]->rect = new Rect(0.0f, 0.0f, 12, 12);
	}
	
	// Load Cherry
	_cherry->eTexture = new Texture2D();
	_cherry->eTexture->Load("Textures/Cherries.png", false);
	_cherry->ePosition = new Vector2(150.0f, 100.0f);
	_cherry->rect = new Rect(0.0f, 0.0f, 32, 32);
	_stringPosition = new Vector2(10.0f, 25.0f);
}
void Pacman::Draw(int elapsedTime)

{
	/*
	This draw function,utilising the use of the member pointers which reference the structs, which then the contents of the structs can be access to by using arrow operator (->)
	This function draws our characters and the whole game screen itself.
	*/
	std::stringstream stream;
	SpriteBatch::BeginDraw();
	stream << "Score: " << score << endl << "Press 'H' for help menu!";

	if (!_pacman->dead)
	{
		SpriteBatch::Draw(_pacman->_pTexture, _pacman->position, _pacman->sourceRect);
	}
	if (_StartMenu->inUse)
	{
		SpriteBatch::Draw(_StartMenu->_menuTexture, _StartMenu->_mRect, nullptr);
	}
	else
	{
		for (int i = 0; i < MUNCHIECOUNT; i++)
		{
			SpriteBatch::Draw(_munchies[i]->eTexture, _munchies[i]->ePosition, _munchies[i]->rect);
		}

		//Draws Ghosts
		SpriteBatch::Draw(_ghosts[0]->_eTexture, _ghosts[0]->position, _ghosts[0]->_eRect);
		SpriteBatch::Draw(_ghosts[1]->_eTexture, _ghosts[1]->position, _ghosts[1]->_eRect);
		SpriteBatch::Draw(_ghosts[2]->_eTexture, _ghosts[2]->position, _ghosts[2]->_eRect);
		SpriteBatch::Draw(_ghosts[3]->_eTexture, _ghosts[3]->position, _ghosts[3]->_eRect);
		SpriteBatch::Draw(_ghosts[4]->_eTexture, _ghosts[4]->position, _ghosts[4]->_eRect);
		SpriteBatch::Draw(_ghosts[5]->_eTexture, _ghosts[5]->position, _ghosts[5]->_eRect);
		SpriteBatch::Draw(_ghosts[6]->_eTexture, _ghosts[6]->position, _ghosts[6]->_eRect);
		SpriteBatch::Draw(_ghosts[7]->_eTexture, _ghosts[7]->position, _ghosts[7]->_eRect);

		//Draws Cherry
		SpriteBatch::Draw(_cherry->eTexture, _cherry->ePosition, _cherry->rect);

		if (_PauseMenu->inUse)
		{
			SpriteBatch::Draw(_PauseMenu->_menuTexture, _PauseMenu->_mRect, nullptr);
		}
		if (_HelpMenu->inUse)
		{
			SpriteBatch::Draw(_HelpMenu->_menuTexture, _HelpMenu->_mRect, nullptr);
		}
		SpriteBatch::Draw(_pacman->_pTexture, _pacman->sourceRect, nullptr);
	}
	if (_pacman->dead)
	{
		SpriteBatch::Draw(_GameOverMenu->_menuTexture, _GameOverMenu->_mRect, nullptr);
	}
	if (won == true)
	{
		SpriteBatch::Draw(_YouWin->_menuTexture, _YouWin->_mRect, nullptr);
	}

	SpriteBatch::DrawString(stream.str().c_str(), _stringPosition, Color::Green);
	SpriteBatch::EndDraw();

}

void Pacman::Update(int elapsedTime)
{/*This being the final function, this function calls other functions , which enable user input, pacmans and the munchies anmation,aswell as screenwrpping through the user of the
 checkviewportcollision function*/
	
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();
	Input::MouseState* mouseState = Input::Mouse::GetState();
	PollInput();
	CheckStart(keyboardState, _StartMenu->interactKey);

	if (!_pacman->dead)
	{
		if (!won)
		{
			if (!_StartMenu->inUse)
			{
				CheckHelp(keyboardState, _HelpMenu->interactKey);
				if (!_HelpMenu->inUse)
				{
					CheckPaused(keyboardState, _PauseMenu->interactKey);
					if (!_PauseMenu->inUse)
					{

						user_Input(elapsedTime);
						UpdateMunchie(elapsedTime);
						UpdatePacman(elapsedTime);
						UpdateGhost(elapsedTime);
						for (int i = 0; i < Ghost; i++)
						{
							UpdateGhostMovementX(_ghosts[i], elapsedTime);
							UpdateGhostMovementY(_ghosts[i], elapsedTime);
						}

						CheckGhostCollisions();
						CheckViewportCollision();

						for (int i = 0; i < MUNCHIECOUNT; i++)
						{
							if (CollisionCheck(_pacman->position->X, _pacman->position->Y, _pacman->sourceRect->Width, _pacman->sourceRect->Height, _munchies[i]->ePosition->X, _munchies[i]->ePosition->Y, _munchies[i]->rect->Height, _munchies[i]->rect->Width))
							{

								_munchies[i]->ePosition->X = -1000;
								_munchies[i]->ePosition->Y = -1000;
								Audio::Play(_EatMunchie);
								score++;

							}
						}
						UpdateCherry(elapsedTime);
						if (CollisionCheck(_pacman->position->X, _pacman->position->Y, _pacman->sourceRect->Width, _pacman->sourceRect->Height, _cherry->ePosition->X, _cherry->ePosition->Y, _cherry->rect->Width, _cherry->rect->Height))
						{

							_cherry->ePosition = new Vector2(-1000, -1000);
							score += 50;
							Audio::Play(_EatCherry);
						}
						if (score == 100)
						{
							won = true;
							Audio::Play(_youwin);
						}

					}

				}
			}
		}


	}
}

void Pacman::user_Input(int elapsedTime )
{

	S2D::Input::KeyboardState* keyboardState = S2D::Input::Keyboard::GetState();
	
	float pacmanSpeed = _pacman->_cPacmanSpeed * elapsedTime * _pacman->speedMultiplier;

	//WASD Movement , when keys are pressed movement sound is created , uses enums for input
	//Goes Up
	if (direction == Direction::UP)
	{
		_pacman->position->Y -= pacmanSpeed;
		_pacman->direction = -1;
		if (keyboardState->IsKeyDown(S2D::Input::Keys::W))
		{
			if (!_pacman->sound)
			{
				Audio::Play(_PacmanMunch);
				_pacman->sound = true;
			}
		}
		if (keyboardState->IsKeyUp(S2D::Input::Keys::W))
		{
			_pacman->sound = false;
			Audio::Stop(_PacmanMunch);
		}
	}
	//Goes Left
	else if (direction == Direction::LEFT)
	{
		_pacman->position->X -= pacmanSpeed;
		_pacman->direction = 2; 
		if (keyboardState->IsKeyDown(S2D::Input::Keys::A))
		{
			if (!_pacman->sound)
			{
				Audio::Play(_PacmanMunch);
				_pacman->sound = true;
			}
		}
		if (keyboardState->IsKeyUp(S2D::Input::Keys::A))
		{
			_pacman->sound = false;
			Audio::Stop(_PacmanMunch);
		}
	}
	//Goes down
	else if (direction == Direction::DOWN)
	{
		_pacman->position->Y += pacmanSpeed;
		_pacman->direction = 1;
		if (keyboardState->IsKeyDown(S2D::Input::Keys::S))
		{
			if (!_pacman->sound)
			{
				Audio::Play(_PacmanMunch);
				_pacman->sound = true;
			}
		}
		if (keyboardState->IsKeyUp(S2D::Input::Keys::S))
		{
			_pacman->sound = false;
			Audio::Stop(_PacmanMunch);
		}
	}
	//Goes right
	else if (direction == Direction::RIGHT)
	{
		_pacman->position->X += pacmanSpeed;
		_pacman->direction = 0;

		if (keyboardState->IsKeyDown(S2D::Input::Keys::D))
		{
			if (!_pacman->sound)
			{

				Audio::Play(_PacmanMunch);
				_pacman->sound = true;

			}
		}
		if (keyboardState->IsKeyUp(S2D::Input::Keys::D))
		{
			_pacman->sound = false;
			Audio::Stop(_PacmanMunch);
		}
	}
	//Speeds player movemnt if leftshift pressed
	if (keyboardState->IsKeyDown(Input::Keys::LEFTSHIFT))
	{
		_pacman->speedMultiplier = 0.2f;
	}	
	else
	{
		_pacman->speedMultiplier = 0.1f;
	}
}

void Pacman::PollInput()
{
	// Gets the current state of the keyboard
	S2D::Input::KeyboardState* keyboardState = S2D::Input::Keyboard::GetState();

	//Enums used for player movement
	if (keyboardState->IsKeyDown(S2D::Input::Keys::W))direction = Direction::UP; 
	else if (keyboardState->IsKeyDown(S2D::Input::Keys::A))direction = Direction::LEFT;
	else if (keyboardState->IsKeyDown(S2D::Input::Keys::S))direction = Direction::DOWN;
	else if (keyboardState->IsKeyDown(S2D::Input::Keys::D))direction = Direction::RIGHT;

}

void Pacman::CheckPaused(Input::KeyboardState* state, Input::Keys pauseKey)
{



	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();

	if (keyboardState->IsKeyDown(pauseKey) && !_PauseMenu->keyPressedDown)
	{
		_PauseMenu->keyPressedDown = true;
		_PauseMenu->inUse = !_PauseMenu->inUse;

	}
	if (keyboardState->IsKeyUp(pauseKey))
	{
		_PauseMenu->keyPressedDown = false;
	}
	//This function as the names implies, its checks that if the key "p" is pressed, it will either activate or distactivate the Pause menu, this will freeze all animations,
	//basically stops the game.

}

void Pacman::CheckStart(Input::KeyboardState* state, Input::Keys startKey)
{
	//This functions is used for getting of the start menu
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();
		
	if (keyboardState->IsKeyDown(startKey) && _StartMenu->inUse)
	{
		_StartMenu->inUse = false;
		Audio::Play(_StartUp);
	}

}
void Pacman::CheckHelp(Input::KeyboardState* state, Input::Keys helpKey)
{
	//if 'h' is pressed displays help menu to user
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();

	if (keyboardState->IsKeyDown(helpKey) && !_HelpMenu->keyPressedDown)
	{
		_HelpMenu->keyPressedDown = true;
		_HelpMenu->inUse = !_HelpMenu->inUse;

	}
	if (keyboardState->IsKeyUp(helpKey))
	{
		_HelpMenu->keyPressedDown = false;
	}

}
bool Pacman::CollisionCheck(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2)
{
	//checks players collision by creating bounding box over the sprite
	int left1 = x1;
	int left2 = x2;
	int right1 = x1 + width1;
	int right2 = x2 + width2;
	int top1 = y1;
	int top2 = y2;
	int bottom1 = y1 + height1;
	int bottom2 = y2 + height2;

	if (bottom1 < top2)
		return false;
	if (top1 > bottom2)
		return false;
	if (right1 < left2)
		return false;
	if (left1 > right2)
		return false;

		return true;

}
void Pacman::CheckGhostCollisions()
{

	//Used to created ghost collision ,so if player bounding box collides with a ghost, player dies
	// Local Variables
	int i = 0;
	int bottom1 = _pacman->position->Y + _pacman->sourceRect->Height;
	int bottom2 = 0;
	int left1 = _pacman->position->X;
	int left2 = 0;
	int right1 = _pacman->position->X + _pacman->sourceRect->Width;
	int right2 = 0;
	int top1 = _pacman->position->Y;
	int top2 = 0;

	for (int i = 0; i < Ghost; i++)
		{
	// Populate variables with Ghost data
			bottom2 =
				_ghosts[i]->position->Y + _ghosts[i]->_eRect->Height;
			left2 = _ghosts[i]->position->X;
			right2 =
				_ghosts[i]->position->X + _ghosts[i]->_eRect->Width;
			top2 = _ghosts[i]->position->Y;

			if ((bottom1 > top2) && (top1 < bottom2) && (right1 > left2)
				&& (left1 < right2))
			{
				_pacman->dead = true;
				Audio::Play(_PacmanDeath);
			}
		}
	}
void Pacman::CheckViewportCollision()
{
	
	//This checks whether via the use of conditionals if the player hits a world border, since in pacman 
	//you warp to other side of the map, this checks to ensure that if the player hits world edge, they will be warpped to oposite end of the map
	if (_pacman->position->X + _pacman->sourceRect->Width > 900)
	{
		_pacman->position->X = 1;
	}


	if (_pacman->position->X + _pacman->sourceRect->Width < 0)
	{
		_pacman->position->X = 850;
	}



	if (_pacman->position->Y + _pacman->sourceRect->Height > 900)
	{
		_pacman->position->Y = 30;
	}


	if (_pacman->position->Y + _pacman->sourceRect->Height < 0)
	{
		_pacman->position->Y = 850;
	}

}
void Pacman::UpdatePacman(int elapsedTime)
{
	

	_pacman->currentFrameTime += elapsedTime;
	if (_pacman->currentFrameTime > _pacman->cFrameTime)
	{

		_pacman->frame++;

		if (_pacman->frame >= 2)
			_pacman->frame = 0;

		_pacman->currentFrameTime = 0;

	}

	//This code updates the pacman frames, this inresults gives pacman his anaimation
	_pacman->sourceRect->Y = _pacman->sourceRect->Height * _pacman->direction;
	_pacman->sourceRect->X = _pacman->sourceRect->Width * _pacman->frame;


}
void Pacman::UpdateMunchie(int elapsedTime)
{
	//used for munchie animation for all 50 munchies in array
	int i;
	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		
_munchies[i]->eCurrentFrameTime += elapsedTime;

	if (_munchies[i]->eCurrentFrameTime > _munchies[i]->eFrameTime)
		{

			_munchies[i]->frameCount++;

			if (_munchies[i]->frameCount >= 2)
				_munchies[i]->frameCount = 0;
			_munchies[i]->eCurrentFrameTime = 0;
			_munchies[i]->rect->X = _munchies[i]->rect->Width * _munchies[i]->frameCount;


		}
	}
}
void Pacman::UpdateGhost(int elapsedTime)
{
	//gives all 8 ghosts animation similar to player animation method
	for (int i = 0; i < Ghost; i++)
	{
		_ghosts[i]->currentFrameTime += elapsedTime;

	if (_ghosts[i]->currentFrameTime > _ghosts[i]->FrameTime)
	{

		_ghosts[i]->FrameCount++;

		if (_ghosts[i]->FrameCount >= 2)
			_ghosts[i]->FrameCount = 0;


		_ghosts[i]->currentFrameTime = 0;


		_ghosts[i]->_eRect->Y = _ghosts[i]->_eRect->Height * _ghosts[i]->direction;
		_ghosts[i]->_eRect->X = _ghosts[i]->_eRect->Width * _ghosts[i]->FrameCount;

	}

	}
	
}

void  Pacman::UpdateCherry(int elapsedTime)
{
	//similar to munchie animation method
	_cherry->eCurrentFrameTime += elapsedTime;

	if (_cherry->eCurrentFrameTime > _cherry->eFrameTime)
	{

		_cherry->frameCount++;

		if (_cherry->frameCount >= 2)
			_cherry->frameCount = 0;
		_cherry->eCurrentFrameTime = 0;
		_cherry->rect->X = _cherry->rect->Width * _cherry->frameCount;


	}
	

}
void Pacman::UpdateGhostMovementX(EnemyMovement*, int elapsedTime)
{
	//creates movement for all 4 ghosts that are tasked to move on the x axis 

		if (_ghosts[0]->direction == 0) //Moves Right 
		{
			_ghosts[0]->position->X += _ghosts[0]->speed * elapsedTime;
		}
		else if (_ghosts[0]->direction == 1) //Moves Left 
		{
			_ghosts[0]->position->X -= _ghosts[0]->speed * elapsedTime;
		}

		if (_ghosts[0]->position->X + _ghosts[0]->_eRect->Width >=
			Graphics::GetViewportWidth()) //Hits Right edge 
		{
			_ghosts[0]->direction = 1; //Change direction 
		}
		else if (_ghosts[0]->position->X <= 0) //Hits left edge 
		{
			_ghosts[0]->direction = 0; //Change direction 
		}

		if (_ghosts[2]->direction == 0) //Moves Right 
		{
			_ghosts[2]->position->X += _ghosts[2]->speed * elapsedTime;
		}
		else if (_ghosts[2]->direction == 1) //Moves Left 
		{
			_ghosts[2]->position->X -= _ghosts[2]->speed * elapsedTime;
		}

		if (_ghosts[2]->position->X + _ghosts[2]->_eRect->Width >=
			Graphics::GetViewportWidth()) //Hits Right edge 
		{
			_ghosts[2]->direction = 1; //Change direction 
		}
		else if (_ghosts[2]->position->X <= 0) //Hits left edge 
		{
			_ghosts[2]->direction = 0; //Change direction 
		}


		if (_ghosts[4]->direction == 0) //Moves Right 
		{
			_ghosts[4]->position->X += _ghosts[4]->speed * elapsedTime;
		}
		else if (_ghosts[4]->direction == 1) //Moves Left 
		{
			_ghosts[4]->position->X -= _ghosts[4]->speed * elapsedTime;
		}

		if (_ghosts[4]->position->X + _ghosts[4]->_eRect->Width >=
			Graphics::GetViewportWidth()) //Hits Right edge 
		{
			_ghosts[4]->direction = 1; //Change direction 
		}
		else if (_ghosts[4]->position->X <= 0) //Hits left edge 
		{
			_ghosts[4]->direction = 0; //Change direction 
		}


		if (_ghosts[6]->direction == 0) //Moves Right 
		{
			_ghosts[6]->position->X += _ghosts[6]->speed * elapsedTime;
		}
		else if (_ghosts[6]->direction == 1) //Moves Left 
		{
			_ghosts[6]->position->X -= _ghosts[6]->speed * elapsedTime;
		}

		if (_ghosts[6]->position->X + _ghosts[6]->_eRect->Width >=
			Graphics::GetViewportWidth()) //Hits Right edge 
		{
			_ghosts[6]->direction = 1; //Change direction 
		}
		else if (_ghosts[6]->position->X <= 0) //Hits left edge 
		{
			_ghosts[6]->direction = 0; //Change direction 
		}

}
void Pacman::UpdateGhostMovementY(EnemyMovement*, int elapsedTime)
{


	if (_ghosts[1]->direction == 0) //Moves up
	{
		_ghosts[1]->position->Y += _ghosts[1]->speed * elapsedTime;
	}
	else if (_ghosts[1]->direction == 1) //Moves down
	{
		_ghosts[1]->position->Y -= _ghosts[1]->speed * elapsedTime;
	}

	if (_ghosts[1]->position->Y + _ghosts[1]->_eRect->Height >=
		Graphics::GetViewportWidth()) //Hits bottom edge 
	{
		_ghosts[1]->direction = 1; //Change direction 
	}
	else if (_ghosts[1]->position->Y <= 0) //Hits top edge 
	{
		_ghosts[1]->direction = 0; //Change direction 
	}


		if (_ghosts[3]->direction == 0) //Moves up 
		{
			_ghosts[3]->position->Y += _ghosts[3]->speed * elapsedTime;
		}
		else if (_ghosts[3]->direction == 1) //Moves down 
		{
			_ghosts[3]->position->Y -= _ghosts[3]->speed * elapsedTime;
		}

		if (_ghosts[3]->position->Y + _ghosts[3]->_eRect->Height >=
			Graphics::GetViewportWidth()) //Hits Right edge 
		{
			_ghosts[3]->direction = 1; //Change direction 
		}
		else if (_ghosts[3]->position->Y <= 0) //Hits left edge 
		{
			_ghosts[3]->direction = 0; //Change direction 
		}
	


		if (_ghosts[5]->direction == 0) //Moves Right 
		{
			_ghosts[5]->position->Y += _ghosts[5]->speed * elapsedTime;
		}
		else if (_ghosts[5]->direction == 1) //Moves Left 
		{
			_ghosts[5]->position->Y -= _ghosts[5]->speed * elapsedTime;
		}

		if (_ghosts[5]->position->Y + _ghosts[5]->_eRect->Height >=
			Graphics::GetViewportWidth()) //Hits Right edge 
		{
			_ghosts[5]->direction = 1; //Change direction 
		}
		else if (_ghosts[5]->position->Y <= 0) //Hits left edge 
		{
			_ghosts[5]->direction = 0; //Change direction 
		}





		if (_ghosts[7]->direction == 0) //Moves Right 
		{
			_ghosts[7]->position->Y += _ghosts[5]->speed * elapsedTime;
		}
		else if (_ghosts[7]->direction == 1) //Moves Left 
		{
			_ghosts[7]->position->Y -= _ghosts[7]->speed * elapsedTime;
		}

		if (_ghosts[7]->position->Y + _ghosts[7]->_eRect->Height >=
			Graphics::GetViewportWidth()) //Hits Right edge 
		{
			_ghosts[7]->direction = 1; //Change direction 
		}
		else if (_ghosts[7]->position->Y <= 0) //Hits left edge 
		{
			_ghosts[7]->direction = 0; //Change direction 
		}
}
