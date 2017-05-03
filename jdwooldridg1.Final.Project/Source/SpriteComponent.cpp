#include "Game.h"
#include "GraphicsDevice.h"
#include "SpriteComponent.h"

bool SpriteComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS presets)
{
	this->gDevice = presets.game->getGraphicsDevice();
	this->view = presets.game->getView();

	//Add the sprite to the sprite vector in the graphics device.
	gDevice->addSprite(this);

	//Set the texture.
	texture = presets.game->getArtAssetLibrary()->Search(presets.objectType).get();

	return true;
}

std::unique_ptr<Object> SpriteComponent::Update()
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
	texture->Draw(gDevice->getRenderer(), view, _owner->GetComponent<BodyComponent>()->getPosition(), _owner->GetComponent<BodyComponent>()->getAngle(), NULL);
}