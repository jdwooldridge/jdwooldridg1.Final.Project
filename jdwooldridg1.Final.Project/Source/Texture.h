#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "View.h"
#include "Definitions.h"
#include <iostream>

class Texture
{
public:
	//Initializes variables
	Texture();

	//Deallocates memory
	~Texture();

	//Loads image at specified path
	bool load(SDL_Renderer* renderer, std::string path);

	//Deallocates texture
	void free();

	//Renders texture at a certain point.
	void Draw(SDL_Renderer* renderer, View* view, GAME_VEC position, GAME_FLT angle, SDL_Rect* clip, SDL_RendererFlip flip);

	int getWidth();
	int getHeight();

private:

	//The actual hardware texture
	SDL_Texture* texture;

	//Image dimensions
	int width;
	int height;
};