#pragma once

#include <string>

#include "ComponentList.h"

class PhysicsDevice;

class BodyComponent : public Component
{
public:
    BodyComponent(std::shared_ptr<Object> owner)
        : Component(owner)
    { };

    bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers);
    std::unique_ptr<Object> Update();
    bool Finish();
    GAME_VEC getPosition();
    GAME_FLT getAngle();
    GAME_VEC getStartPosition();
    void setPositionX(GAME_FLT);
    void setPositionY(GAME_FLT);
    void setAngle(GAME_FLT);
private:
    GAME_VEC startPosition;
    GAME_VEC position;
    GAME_FLT angle;

	PhysicsDevice* pDevice;
};