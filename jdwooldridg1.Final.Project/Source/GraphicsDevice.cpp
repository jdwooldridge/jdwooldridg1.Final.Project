/*
* Author:	Keith Bush
*			UALR
* 
* Date:		January 31, 2015	
*
* File:		GraphicsDevice.cpp
*
* Purpose:	Definition of the SDL GraphicsDevice class
*/
#include <Windows.h>
#include<iostream>

#include "SpriteComponent.h"
#include "GraphicsDevice.h"

GraphicsDevice::GraphicsDevice(Uint32 width, Uint32 height) : SCREEN_WIDTH(width), SCREEN_HEIGHT(height)
{
	screen = NULL;
	renderer = NULL;
}

GraphicsDevice::~GraphicsDevice()
{
	if(!ShutDown())
	{
		printf( "SDL could not shut down! SDL_Error: %s\n", SDL_GetError() );
		exit(1);
	}
}

bool GraphicsDevice::Initialize(bool fullScreen)
{

	//Initialize all SDL subsystems
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return(false);
	}

	//Initialize SDL_image subsystems
	if(!IMG_Init(IMG_INIT_PNG))
	{
		printf( "SDL_image could not initialize! SDL_Error: %s\n", IMG_GetError() );
		return(false);
	}

	if(fullScreen) //Create fullscreen window if fullScreen is set to true.
	{
		//Construct and check window construction
		screen = SDL_CreateWindow("Demonstration Window",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
	}
	else //Create window.
	{
		screen = SDL_CreateWindow("Demonstration Window",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	}
	if(screen==NULL)
	{
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		return(false);
	}

	//Construct the renderer
	renderer = SDL_CreateRenderer(screen,-1,SDL_RENDERER_ACCELERATED);
	if(renderer==NULL)
	{
		printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
		return(false);
	}
	
	//Set the background color (default)
	SDL_SetRenderDrawColor(renderer,237,201,175,255);

	//Clear the renderer.
	Begin();

	//Present the renderer.
	Present();

	return(true);

}

bool GraphicsDevice::ShutDown()
{
	//Free the window
	SDL_DestroyWindow(screen);
	screen = NULL;

	SDL_DestroyTexture(background);
	background = NULL;

	//Free renderer
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	//Quit SDL Subsystems
	IMG_Quit();
	SDL_Quit();

	return(true);
}

//Clear the renderer to begin drawing textures.
void GraphicsDevice::Begin()
{
	SDL_RenderClear(renderer);
}

//Update screen with any rendering.
void GraphicsDevice::Present()
{
	SDL_RenderPresent(renderer);
}

//Set the level's background.
void GraphicsDevice::setBackground(std::string bgPath)
{
	background = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(bgPath.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", bgPath.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		background = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (background == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", bgPath.c_str(), SDL_GetError());
		}

		//Display the background itself.
		SDL_RenderCopy(renderer, background, NULL, NULL);

		Begin();

		Present();

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
}

//Retrieve the renderer.
SDL_Renderer* GraphicsDevice::getRenderer()
{
	return(renderer);
}

//Add a sprite.
void GraphicsDevice::addSprite(SpriteComponent* sprite)
{
	sprites.push_back(sprite);
}

//Draw all loaded sprites.
void GraphicsDevice::Draw()
{
	for (auto sprite : sprites)
	{
		sprite->Draw();
	}
}