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

#include "Texture.h"
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

	//Initialize SDL_TTF subsystem.
	if (TTF_Init() == -1)
	{
		printf("SDL_TTF could not initialize! SDL_Error: %s\n", TTF_GetError());
		return false;
	}

	if(fullScreen) //Create fullscreen window if fullScreen is set to true.
	{
		//Construct and check window construction
		screen = SDL_CreateWindow("Cereal Killer",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
	}
	else //Create window.
	{
		screen = SDL_CreateWindow("Cereal Killer",
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
	
	/*SDL_Surface* bg = IMG_Load("./Assets/Images/bg_Level1.png");
	background = SDL_CreateTextureFromSurface(renderer, bg);*/
	//Set the background color (default)
	//SDL_SetRenderTarget(renderer, background);
	//SDL_SetRenderDrawColor(renderer,237,201,175,255);

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
	TTF_Quit();

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
		//SDL_RenderCopy(renderer, background, NULL, NULL);

		Begin();

		Present();

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
}

bool GraphicsDevice::SetFont(std::string path, GAME_INT size, GAME_RGBA color)
{
	font = TTF_OpenFont(path.c_str(), size);
	if (font == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	this->color = color;

	return(true);

}

//**************************************
//adds text to be displayed to the text vector pased on a string and position
void GraphicsDevice::Text2Screen(std::string text, GAME_VEC position)
//**************************************
{
	int widthIncrease = 10; //left and right padding
	int heightIncrease = 2; //top and bottom padding


							//set color of text
	SDL_Color textColor = { color.R, color.G, color.B, color.A };

	//create texture
	SDL_Texture* textSheetTexture = SDL_CreateTextureFromSurface(
		renderer,
		TTF_RenderText_Solid(
			font,
			text.c_str(),
			textColor));

	//create a texture for the game.
	Texture* textTexture = new Texture();
	textTexture->load(textSheetTexture);

	int width = 0, height = 0;
	//grab textures' with and ehight.
	SDL_QueryTexture(textSheetTexture, NULL, NULL, &width, &height);
	//If we set a position of the box to -1, we center it.
	//bottomRight needs to be the width + 1;
	if (position.x == -1)
	{
		position.x = Center(SCREEN_WIDTH, width);

	}
	if (position.y == -1)
	{
		position.y = Center(SCREEN_HEIGHT, height);
	}

	GAME_VEC topLeft = { position.x - widthIncrease, position.y - heightIncrease };
	GAME_VEC bottomRight = { position.x + width + widthIncrease, position.y + height + heightIncrease };

	GAME_RGBA background = { 255, 255, 255, 255 };
	GAME_RGBA border = { 0, 0, 0, 255 };


	std::map<Texture*, GAME_VEC> objects;
	objects[textTexture] = position;

	DrawOverlay(topLeft, bottomRight, background, border, objects);

}
//**************************************
//adds text to be displayed to the text vector pased on a string and position
//this one let's us directly type the position's values
void GraphicsDevice::Text2Screen(std::string text, GAME_FLT x, GAME_FLT y)
//**************************************
{
	GAME_VEC position = { x,y };
	Text2Screen(text, position);
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

//Remove a sprite.
void GraphicsDevice::removeSprite(SpriteComponent* dSprite)
{
	std::vector<SpriteComponent*>::iterator spriteIter;
	for (spriteIter = sprites.begin(); spriteIter != sprites.end(); ++spriteIter)
	{
		if (*spriteIter == dSprite)
		{
			sprites.erase(spriteIter);
			break;
		}
	}
}

//Draw all loaded sprites and the background image.
void GraphicsDevice::Draw()
{
	SDL_RenderCopy(renderer, background, NULL, NULL);
	for (auto sprite : sprites)
	{
		sprite->Draw();
	}
}

GAME_FLT GraphicsDevice::Center(GAME_FLT centerOn, GAME_FLT width)
{
	GAME_FLT point = (centerOn - width) / 2;
	return point;
}

void GraphicsDevice::DrawOverlay(GAME_VEC topLeft, GAME_VEC bottomRight, GAME_RGBA boxBackgroundColor, GAME_RGBA boxBorderColor, std::map<Texture*, GAME_VEC> objects)
{
	overlay newOverlay = { topLeft, bottomRight, boxBackgroundColor, boxBorderColor, objects };
	overlays.push_back(newOverlay);
}