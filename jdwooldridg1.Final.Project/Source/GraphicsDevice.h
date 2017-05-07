/*
* Author:	Keith Bush
*			UALR
* 
* Date:		January 31, 2015	
*
* File:		GraphicsDevice.h
*
* Purpose:	Declaration of the SDL GraphicsDevice class
*/

#ifndef GRAPHICSDEVICE_H
#define GRAPHICSDEVICE_H

#include "ComponentList.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Definitions.h"

class GraphicsDevice
{
		
public:
	GraphicsDevice(Uint32, Uint32);
	~GraphicsDevice();

	bool Initialize(bool);
	bool ShutDown();
	
	void Begin();
	void Present();

	void Draw();
	void addSprite(SpriteComponent*);
	void removeSprite(SpriteComponent*);

	void setBackground(std::string background);
	SDL_Renderer* getRenderer();

private:
	
	SDL_Texture* background;
	
	//Window(s) to display graphics
	SDL_Window* screen;
	SDL_Renderer* renderer;

	//Parameter
	const Uint32 SCREEN_WIDTH;
	const Uint32 SCREEN_HEIGHT;

	std::vector<SpriteComponent*> sprites;

};

#endif