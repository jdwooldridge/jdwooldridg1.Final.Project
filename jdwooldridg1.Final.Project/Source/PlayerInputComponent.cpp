#include "InputDevice.h";
#include "Game.h"
#include "PlayerInputComponent.h"

bool PlayerInputComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS presets)
{
	iDevice = presets.game->getInputDevice();
	view = presets.game->getView();
	pDevice = presets.game->getPhysicsDevice();
	for (int i = 0; i < GAME_NUM_EVENTS; ++i)
	{
		GAME_EVENT event = static_cast<GAME_EVENT>(i);
		controlPressed[event] = true;
	}
	return true;
}

std::unique_ptr<Object> PlayerInputComponent::Update()
{
	GAME_VEC linearVelocity = { 0, 0 };
	GAME_VEC force;
	GAME_VEC updatedPosition;
	/*if (iDevice->GetEvent(GAME_UP))
		_owner->GetComponent<BodyComponent>()->setPositionY(_owner->GetComponent<BodyComponent>()->getPosition().y - 2);*/
	if (iDevice->GetEvent(GAME_LEFT))
	{
		linearVelocity.x = -2.0f;
		pDevice->SetLinearVelocity(_owner.get(), linearVelocity);
		force = pDevice->GetLinearVelocity(_owner.get());
		updatedPosition.x = pDevice->GetPosition(_owner.get()).x + force.x;
		updatedPosition.y = pDevice->GetPosition(_owner.get()).y + force.y;
		pDevice->SetTransform(_owner.get(), updatedPosition, pDevice->GetAngle(_owner.get()));
	}
	if (iDevice->GetEvent(GAME_RIGHT))
	{
		linearVelocity.x = 2.0f;//(float)cosf((pDevice->GetAngle(_owner.get())*PI / 180) - (PI / 2)) * 2.0f;
		pDevice->SetLinearVelocity(_owner.get(), linearVelocity);
		force = pDevice->GetLinearVelocity(_owner.get());
		updatedPosition.x = pDevice->GetPosition(_owner.get()).x + force.x;
		updatedPosition.y = pDevice->GetPosition(_owner.get()).y + force.y;
		pDevice->SetTransform(_owner.get(), updatedPosition, pDevice->GetAngle(_owner.get()));
	}

	//BORDER SCROLLING

	GAME_INT borderDistance = 250;

	if (_owner->GetComponent<BodyComponent>()->getPosition().x  - view->getPosition().x > SCREEN_WIDTH - borderDistance)
	{
		//for(int i = 0; i < SCREEN_WIDTH / 2; ++i)
			view->setPositionX(view->getPosition().x + 1);
			_owner->GetComponent<BodyComponent>()->setPositionX((SCREEN_WIDTH + view->getPosition().x) - borderDistance);
		//_owner->GetComponent<BodyComponent>()->setPositionX(_owner->GetComponent<BodyComponent>()->getPosition().x - view->getPosition().x);
	}

	//Ensure the player cannot backtrack/go to the left out of the view.
	if (_owner->GetComponent<BodyComponent>()->getPosition().x < view->getPosition().x)
		_owner->GetComponent<BodyComponent>()->setPositionX(view->getPosition().x);

	return nullptr;
}

bool PlayerInputComponent::Finish()
{
	return true;
}