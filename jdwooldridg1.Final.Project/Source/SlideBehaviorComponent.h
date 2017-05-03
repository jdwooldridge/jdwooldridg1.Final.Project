#pragma once
#include "ComponentList.h"

class SlideBehaviorComponent : public Component
{
public:
    //SlideBehaviorComponent();
    SlideBehaviorComponent(std::shared_ptr<Object> owner)
        : Component(owner)
    { };

    bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers);
    std::unique_ptr<Object> Update();
    bool Finish();
private:
    bool vertical;
    int posNeg;
    GAME_FLT aDelta;
	PhysicsDevice* pDevice;
};