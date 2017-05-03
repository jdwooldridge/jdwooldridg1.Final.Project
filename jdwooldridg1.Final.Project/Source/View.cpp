#include <iostream>
#include "View.h"

View::View()
{

}

View::~View()
{

}


//Set initial values
bool View::Initialize(InputDevice* iDevice, GAME_FLT x, GAME_FLT y)
{
	this->iDevice = iDevice;
	position.x = x;
	position.y = y;
	center.x = x;
	center.y = y;
	return true;
}

//Retrieve the position of the view.
GAME_VEC View::getPosition()
{
	return position;
}

void View::setPositionX(GAME_FLT x)
{
	this->position.x = x;
}

void View::setPositionY(GAME_FLT y)
{
	this->position.y = y;
}


//Update 
bool View::Update(char direction)
{
	//switch (direction)
	//{
	//case 'u':
	//	for (int i = 0; i < SCREEN_HEIGHT; ++i)
	//	{
	//		--position.y;
	//	}
	//	break;
	//case 'd':
	//	for (int i = 0; i < SCREEN_HEIGHT; ++i)
	//		++position.y;
	//	break;
	//case 'l':
	//	for (int i = 0; i < SCREEN_WIDTH; ++i)
	//		--position.x;
	//	break;
	//case 'r':
	//	for (int i = 0; i < SCREEN_WIDTH; ++i)
	//		++position.x;
	//	break;
	//}
	//switch (iDevice->GetEvent()) //Change the view's coordinates. based on the current input.
	//{
	//case GAME_UP: //Move view up if up arrow key is pressed.
	//	position.y = position.y - 2;
	//	std::cout << "ViewY: " << position.y << std::endl;
	//	break;
	//case GAME_DOWN: //Move view up if down arrow key is pressed.
	//	position.y = position.y + 2;
	//	std::cout << "ViewY: " << position.y << std::endl;
	//	break;
	//case GAME_LEFT: //Move view left if left arrow key is pressed.
	//	position.x = position.x - 2; //Increment position here since that moves the screen to the left and not right.
	//	std::cout << "ViewX: " << position.x << std::endl;
	//	break;
	//case GAME_RIGHT: //Move view right if the right arrow key is pressed.
	//	position.x = position.x + 2; //Decrement position here since that moves the screen to the right and not left.
	//	std::cout << "ViewX: " << position.x << std::endl;
	//	break;
	//default:
	//	break;
	//}
	return true;
}
