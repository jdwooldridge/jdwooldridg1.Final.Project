#include "DamageComponent.h"

bool DamageComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	damageAmt = initializers.damageAmt;
	return true;
}
