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
#include "SDL_ttf.h"
#include "Definitions.h"

class GraphicsDevice
{
		
public:
	GraphicsDevice(Uint32, Uint32);
	~GraphicsDevice();

	bool Initialize(bool);
	bool ShutDown();
	bool SetFont(std::string, GAME_INT, GAME_RGBA);
	
	void Begin();
	void Present();

	void Draw();
	void addSprite(SpriteComponent*);
	void removeSprite(SpriteComponent*);
	void Text2Screen(std::string text, GAME_VEC position);
	void Text2Screen(std::string text, GAME_FLT x, GAME_FLT y);

	void setBackground(std::string background);
	SDL_Renderer* getRenderer();

	void DrawOverlay
	(
		//round corner box that contains overlay
		GAME_VEC topLeft, GAME_VEC bottomRight, GAME_RGBA boxBackgroundColor, GAME_RGBA boxBorderColor,
		//any objects drawn in stated box
		//at given position
		std::map<Texture*, GAME_VEC> objects
	);

private:
	GAME_FLT Center(GAME_FLT centerOn, GAME_FLT width);

	SDL_Texture* background;
	
	//Window(s) to display graphics
	SDL_Window* screen;
	SDL_Renderer* renderer;

	//Parameter
	const Uint32 SCREEN_WIDTH;
	const Uint32 SCREEN_HEIGHT;

	typedef struct overlay
	{
		GAME_VEC topLeft;
		GAME_VEC bottomRight;
		GAME_RGBA boxBackgroundColor;
		GAME_RGBA boxBorderColor;
		std::map<Texture*, GAME_VEC> objects;
	}overlay;

	std::vector<overlay> overlays;

	std::vector<SpriteComponent*> sprites;

	TTF_Font* font;
	GAME_RGBA color;
};

#endif