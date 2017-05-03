#pragma once

//#include "SDL.h"
#include "Definitions.h"

#ifndef _VECTOR_
    #include <vector>
#endif
#ifndef _MEMORY_
    #include <memory>
#endif

union SDL_Event;

class InputDevice
{
public:
    InputDevice();
    ~InputDevice();
    bool Initialize();
	void Update();
    bool GetEvent(GAME_EVENT event);
private:
    std::unique_ptr<SDL_Event> event;
    GAME_EVENT Translate(SDL_Event*);
    std::vector<bool> keyStates;
};