#include "Pacman.h"

#include <sstream>

Pacman::Pacman(int argc, char* argv[]) : Game(argc, argv)

{
	int i;
	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		_munchies[i] = new Enemy();
		_munchies[i]->eCurrentFrameTime = 0;
		_munchies[i]->frameCount = rand() % 1;
		_munchies[i]->eCurrentFrameTime = 500;
		_munchies[i]->eFrameTime = rand() % 500 + 50;
			}

	_cherry = new Enemy();
	


	_move = new Movement();
	_move->_paused = false;
	_move->_pKeyDown = false;
	_move->_start = true;
	_move->_sKeyDown = false;


	_pacman = new Player();
	_pacman->direction = 0;
	_pacman->currentFrameTime = 0;
	_pacman->frame = 0;
	_pacman->speedMultiplier = 0.1f;
	_pacman->cFrameTime = 250;
	
	


	
	//Initialise important Game aspects
	Graphics::Initialise(argc, argv, this, 900, 900, false, 25, 25, "Pacman", 60);
	Input::Initialise();

	// Start the Game Loop - This calls Update and Draw in game loop
	Graphics::StartGameLoop();
}

Pacman::~Pacman()
{ 
	delete _munchies[0]->eTexture;
	
	int nCount = 0;
	for (int i = 0; i < MUNCHIECOUNT; nCount++)
	{
		delete _munchies[nCount]->ePosition;
		delete _munchies[nCount]->spriteRect;
		delete _munchies[nCount];
	}
	delete[] _munchies;
			
	
	delete _pacman->texture;
	delete _pacman->sourceRect;

}

void Pacman::LoadContent()
{

	_menu = new Menu();
	_menu->_menuBackground = new Texture2D();
	_menu->_menuBackground->Load("Textures/Transparency.png", false);
	_menu->_menuRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(),
		Graphics::GetViewportHeight());
	_menu->_menuStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f,
		Graphics::GetViewportHeight() / 2.0f);


	// Load Pacman
	_pacman->texture = new Texture2D();
	_pacman->texture->Load("Textures/Pacman.tga", false);
	_pacman->position = new Vector2(350.0f, 350.0f);
	_pacman->sourceRect = new Rect(0.0f, 0.0f, 32, 32);

	// Load Munchie
	
	
	int i;
	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		_munchies[i]->eTexture = new Texture2D();
		_munchies[i]->eTexture->Load("Textures/Munchie.png", true);
		_munchies[i]->ePosition = new Vector2((rand() % Graphics::GetViewportWidth()), (rand() % Graphics::GetViewportHeight()));
		_munchies[i]->rect = new Rect(0.0f, 0.0f, 12, 12);
	}

	
	//load cherry

		// Load Pacman
	_cherry->eTexture = new Texture2D();
	_cherry->eTexture->Load("Textures/Cherries.png", false);
	_cherry->ePosition = new Vector2(450.0f, 450.0f);
	_cherry->rect = new Rect(0.0f, 0.0f, 32, 32);




	// Set string position
	_stringPosition = new Vector2(10.0f, 25.0f);
}
void Pacman::user_Input(int elapsedTime  ,Input::KeyboardState* state, Input::MouseState* LeftButton)
{
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();
	Input::MouseState* mouseState = Input::Mouse::GetState();
	mouseState->LeftButton;

	if (state->IsKeyDown(Input::Keys::W))
	{
		_pacman->position->Y -= _pacman->speedMultiplier * elapsedTime;
		_pacman->direction = -1;
	}


	 if (state->IsKeyDown(Input::Keys::A))
	{
		_pacman->position->X -= _pacman->speedMultiplier * elapsedTime;
		_pacman->direction = 2;
	}

	if (state->IsKeyDown(Input::Keys::S))
	{
		_pacman->position->Y += _pacman->speedMultiplier * elapsedTime;
		_pacman->direction = 1;
	}

	 if (state->IsKeyDown(Input::Keys::D))
	{
		_pacman->position->X += _pacman->speedMultiplier * elapsedTime;
		_pacman->direction = 0;

	}
	 if (mouseState->LeftButton == Input::ButtonState::PRESSED)
	 {
		 _cherry->ePosition->X = mouseState->X;
		 _cherry->ePosition->Y = mouseState->Y;
	 }




}

void Pacman::CheckPaused(Input::KeyboardState* state, Input::Keys pauseKey)
{
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();

	if (keyboardState->IsKeyDown(Input::Keys::P) && !_move->_pKeyDown)
	{
		_move->_pKeyDown = true;
		_move->_paused = !_move->_paused;

	}
	if (keyboardState->IsKeyUp(Input::Keys::P))
	{
		_move->_pKeyDown = false;
	}


}
void Pacman::CheckStart(Input::KeyboardState* state, Input::Keys startKey)
{
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();

	if (keyboardState->IsKeyDown(Input::Keys::SPACE) && !_move->_sKeyDown)
	{
		_move->_sKeyDown = true;
		_move->_start = !_move->_start;
	}

	if (keyboardState->IsKeyUp(Input::Keys::SPACE))
	{
		_move->_sKeyDown = false;


	}


}
void Pacman::CheckViewportCollision()
{
	

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
	Input::MouseState* mouseState = Input::Mouse::GetState();

	_pacman->currentFrameTime += elapsedTime;
	if (_pacman->currentFrameTime > _pacman->cFrameTime)
	{

		_pacman->frame++;

		if (_pacman->frame >= 2)
			_pacman->frame = 0;

		_pacman->currentFrameTime = 0;

	}




}

void Pacman::UpdateMunchie(int elapsedTime)
{

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
	
void Pacman::UpdateCherry(int elapsedTime)
{


	
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


	
void Pacman::Draw(int elapsedTime)

 {

			// Allows us to easily create a string
			std::stringstream stream;
			stream << "Pacman X: " << _pacman->position->X << " Y: " << _pacman->position->Y;

			SpriteBatch::BeginDraw(); // Starts Drawing
			SpriteBatch::Draw(_cherry->eTexture, _cherry->ePosition, _cherry->rect);
			SpriteBatch::Draw(_pacman->texture, _pacman->position, _pacman->sourceRect); // Draws Pacman
			int i;
			for (int i = 0; i < MUNCHIECOUNT; i++)
			{
				SpriteBatch::Draw(_munchies[i]->eTexture, _munchies[i]->ePosition, _munchies[i]->rect);
			}
			



			if (_move->_start)
			{
				std::stringstream menuStream; menuStream << "Start!";

				SpriteBatch::Draw(_menu->_menuBackground, _menu->_menuRectangle, nullptr);
				SpriteBatch::DrawString(menuStream.str().c_str(), _menu->_menuStringPosition, Color::Red);


			}



			if (_move->_paused)
			{
				std::stringstream menuStream; menuStream << "PAUSED!";

				SpriteBatch::Draw(_menu->_menuBackground, _menu->_menuRectangle, nullptr);
				SpriteBatch::DrawString(menuStream.str().c_str(), _menu->_menuStringPosition, Color::Red);


			}



			// Draws String
			SpriteBatch::DrawString(stream.str().c_str(), _stringPosition, Color::Green);
			SpriteBatch::EndDraw(); // Ends Drawing
		
	
}

bool Pacman::CollisionCheck(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2)
{

	int left1 = x1;
	int left2 = x2;
	int right1 = x1 + width1;
	int right2 = x2 + width2;
	int top1 = y1;
	int top2 = y2;
	int bottom1 = y1 + height1;
	int bottom2 = y2 + height2;

	if (bottom1 < top2)
	{
		return false;
		if (top1 > bottom2)
		{
			return false;
		}
		if (right1 < left2)
		{
			return false;
		}
		if (left1 > right2)
		{
			return false;
		}
	
	}
	return true;
}

void Pacman::Update(int elapsedTime) 
{
	_pacman->sourceRect->Y = _pacman->sourceRect->Height * _pacman->direction;
	_pacman->sourceRect->X = _pacman->sourceRect->Width * _pacman->frame;
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();



		CheckStart(keyboardState, Input::Keys::SPACE);


		CheckPaused(keyboardState, Input::Keys::P);


		if (!_move->_paused)
		{
			user_Input(elapsedTime, keyboardState);
			UpdatePacman(elapsedTime);
			UpdateCherry(elapsedTime);
			UpdateMunchie(elapsedTime);
			CheckViewportCollision();


			
			
		


		}





	}


