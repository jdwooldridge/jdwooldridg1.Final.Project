#pragma once
#include "ComponentList.h"

class DeviceAndLibraryManager;

class SlideBehaviorComponent : public Component
{
public:
    //SlideBehaviorComponent();
    SlideBehaviorComponent(std::shared_ptr<Object> owner)
        : Component(owner)
    { };

    bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers);
    std::shared_ptr<Object> Update();
    bool Finish();
private:
    bool vertical;
    int posNeg;
    GAME_FLT aDelta;
	std::shared_ptr<DeviceAndLibraryManager> devicesAndLibraries;
};