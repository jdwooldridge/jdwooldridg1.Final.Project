#include "SDL.h"
#include "SDL_image.h"

#include "InputDevice.h"

InputDevice::InputDevice() :
	keyStates(GAME_NUM_EVENTS, false)
{
}

InputDevice::~InputDevice()
{

}

bool InputDevice::Initialize()
{
	//========================================
	//Construct Event System
	//========================================
	event = std::make_unique<SDL_Event>();
	if (!event) {
		printf("SDL Event could not initialize!");
		exit(1);
	}
	keyStates[GAME_DOWN] = false;
	keyStates[GAME_UP] = false;
	keyStates[GAME_LEFT] = false;
	keyStates[GAME_RIGHT] = false;
	keyStates[GAME_SPACE] = false;
	keyStates[GAME_QUIT] = false;
	//keyStates[GAME_SHIFT] = false;
	//keyStates[GAME_B] = false;
	Update();
	return true;
}

//Translate the
//void InputDevice::Update()
//{
//	/*switch (event->key.keysym.sym) //Get the key event.
//	{
//	case SDLK_LEFT: //Return GAME_LEFT if the left arrow key was pressed.
//		return GAME_LEFT;
//		break;
//	case SDLK_RIGHT: //Return GAME_RIGHT if the right arrow key was pressed.
//		return GAME_RIGHT;
//		break;
//	case SDLK_UP: //Return GAME_UP if the up arrow key was pressed.
//		return GAME_UP;
//		break;
//	case SDLK_DOWN: //Return GAME_DOWN if the down arrow key was pressed.
//		return GAME_DOWN;
//		break;
//	}*/
//	GAME_EVENT gEvent;
//	if (SDL_PollEvent(event.get()))
//	{
//		if (event->key.keysym.sym == SDLK_LEFT)
//		{
//			keyStates[GAME_LEFT] = true;
//		}
//		if (event->key.keysym.sym == SDLK_RIGHT)
//		{
//			keyStates[GAME_RIGHT] = true;
//		}
//		if (event->key.keysym.sym == SDLK_UP)
//		{
//			keyStates[GAME_UP] = true;
//		}
//		if (event->key.keysym.sym == SDLK_DOWN)
//		{
//			keyStates[GAME_DOWN] = true;
//		}
//		if (event->key.keysym.sym == SDLK_q)
//		{
//			keyStates[GAME_QUIT] = true;
//		}
//	}
//	//return GAME_NA; //Return nothing by default.
//}

//**************************************
//Updates the event based on the passed in SDL_EVENT
void InputDevice::Update()
//**************************************
{
	GAME_EVENT gEvent;
	if (SDL_PollEvent(event.get()))
	{
		//updates the proper key state based on the event that was passed in
		switch (event->type)
		{
		case SDL_KEYDOWN:
			//translates the SDL even to a game event.
			gEvent = Translate(event.get());
			keyStates[gEvent] = true;
			break;
		case SDL_KEYUP:
			//translates the SDL even to a game event.
			gEvent = Translate(event.get());
			keyStates[gEvent] = false;
			break;
		case SDL_QUIT:
			gEvent = Translate(event.get());
			keyStates[gEvent] = true;
			break;
		default:
			break;
		}
	}



}

//**************************************
//converts the SDL event to a game event
GAME_EVENT InputDevice::Translate(SDL_Event* event)
//**************************************
{
	//This switch is here in case we want to add other events, such as mouse events.
	switch (event->key.keysym.sym)
	{
	case SDLK_LEFT:
		return GAME_LEFT;
		break;
	case SDLK_RIGHT:
		return GAME_RIGHT;
		break;
	case SDLK_UP:
		return GAME_UP;
		break;
	case SDLK_DOWN:
		return GAME_DOWN;
		break;
	case SDLK_SPACE:
		return GAME_SPACE;
		break;
	case SDLK_q:
		return GAME_QUIT;
		break;
	case SDLK_p:
		return GAME_PAUSE;
		break;
	}



	return GAME_NA;
}

//Poll for the current event and return its equivalent GAME_EVENT.
bool InputDevice::GetEvent(GAME_EVENT event)
{
	return keyStates[event];
}