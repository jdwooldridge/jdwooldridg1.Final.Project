#include <iostream>
#include "Texture.h"

//Set the texture's members to 0/NULL.
Texture::Texture()
{
	width = 0;
	height = 0;
	texture = NULL;
}


Texture::~Texture()
{
	free(); //Remove texture info.
}

//Load the texture.
bool Texture::load(SDL_Renderer* renderer, std::string path)
{

	//Destroy existing texture information
	free();

	//The image that's loaded
	SDL_Surface* surface = NULL;

	//Load the image
	surface = IMG_Load(path.c_str());

	//If the image loaded
	if (surface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());

	}
	else
	{
		//Color key image
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));

		//Create an optimized image
		texture = SDL_CreateTextureFromSurface(renderer, surface);

		if (texture == NULL)
		{
			printf("Unable to create texture from image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());

		}
		else
		{

			//Set the height and width from the texture
			SDL_QueryTexture(texture, NULL, NULL, &width, &height);

			//Free the loaded image; no longer needed
			SDL_FreeSurface(surface);

		}

	}

	return(texture != NULL);

}

bool Texture::load(SDL_Texture* texture)
{
	this->texture = texture;
	//Set the height and width from the texture
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	return true;
}

//Purge the texture if it is not null.
void Texture::free()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}
//Draw texture onto screen and set render space.
void Texture::Draw(SDL_Renderer * renderer, View * view, GAME_VEC position, GAME_FLT angle, SDL_Rect * clip, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen.
	SDL_Rect renderQuad = { position.x - view->getPosition().x, position.y - view->getPosition().y, width, height };

	//Set clip rendering dimensions
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Set level render space.
    /*SDL_Rect screen = { view->getPosition().x, view->getPosition().y, SCREEN_WIDTH, SCREEN_HEIGHT };
    
	//Set level viewport space.
    SDL_RenderSetViewport( renderer, &screen );
	SDL_RenderGetViewport(renderer, &screen);*/

	//Render to screen
	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, NULL, flip);

}

//Retrieve texture width.
int Texture::getWidth() {
	return width;
}

//Retrieve texture height.
int Texture::getHeight() {
	return height;
}
