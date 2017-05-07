#include "DeviceAndLibraryManager.h"
#include "GraphicsDevice.h"
#include "SpriteComponent.h"

bool SpriteComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS presets)
{
	devicesAndLibraries = presets.devicesAndLibraries;

	//Add the sprite to the sprite vector in the graphics device.
	devicesAndLibraries->getGraphicsDevice()->addSprite(this);

	flip = SDL_FLIP_NONE;

	//Set the texture.
	texture = presets.devicesAndLibraries->getArtLibrary()->Search(presets.objectType).get();

	return true;
}

std::shared_ptr<Object> SpriteComponent::Update()
{
	return nullptr;
}

bool SpriteComponent::Finish()
{
	return true;
}
//Draw this sprite.
void SpriteComponent::Draw()
{
	texture->Draw(devicesAndLibraries->getGraphicsDevice()->getRenderer(), devicesAndLibraries->getView(), _owner->GetComponent<BodyComponent>()->getPosition(), 0, NULL, flip);
}