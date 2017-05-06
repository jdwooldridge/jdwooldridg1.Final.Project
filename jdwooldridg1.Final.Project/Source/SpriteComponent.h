#pragma once

#include "SDL.h"
#include "ComponentList.h"

class GraphicsDevice;

class SpriteComponent : public Component
{
public:
	SpriteComponent(std::shared_ptr<Object> owner)
		: Component(owner)
	{ };

	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS);
	std::unique_ptr<Object> Update();
	bool Finish();
	void Draw();
	Texture* GetTexture() { return texture; }
	void setFlip(SDL_RendererFlip flip) { this->flip = flip; }
private:
	Texture* texture;
	GraphicsDevice* gDevice;
	View* view;
	SDL_RendererFlip flip;
};