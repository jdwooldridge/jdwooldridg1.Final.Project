#pragma once
//#include "SDL.h"
//#include "InputDevice.h"
#include "Definitions.h"

class InputDevice;
class View
{
public:
	View();
	~View();
	bool Initialize(InputDevice*, GAME_FLT, GAME_FLT);
	bool Update(char);
	GAME_VEC getPosition();
	void setPositionX(GAME_FLT);
	void setPositionY(GAME_FLT);

private:
	InputDevice* iDevice;
	GAME_VEC position;
	GAME_VEC center;

};

