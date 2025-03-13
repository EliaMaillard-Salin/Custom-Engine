#pragma once


#include "define.h"
#include "BuffersStruct.h"

#include "ComponentBase.h"
#include "Math/Vector3.hpp"

namespace Engine { class Scene; }

namespace Engine { struct Light; }
struct Engine::Light : Engine::ComponentBase<Component::Light>
{
    void SetColor(Vector3f color);
    void SetType(int type);
    void SetPosition(Vector3f position);
    void SetIntensity(float32 intensity);
    void SetDirection(Vector3f direction);
    void SetSpotAngle(float32 angle);

private:
    LightCB lightCB = {};
    friend Scene;
};
