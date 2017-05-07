#pragma once

#include "SDL.h"
#include "ComponentList.h"

class DeviceAndLibraryManager;

class SpriteComponent : public Component
{
public:
	SpriteComponent(std::shared_ptr<Object> owner)
		: Component(owner)
	{ };

	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS);
	std::shared_ptr<Object> Update();
	bool Finish();
	void Draw();
	Texture* GetTexture() { return texture; }
	void setFlip(SDL_RendererFlip flip) { this->flip = flip; }
	SDL_RendererFlip getFlip() { return flip; }
private:
	std::shared_ptr<DeviceAndLibraryManager> devicesAndLibraries;
	Texture* texture;
	SDL_RendererFlip flip;
};