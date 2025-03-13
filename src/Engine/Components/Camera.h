#ifndef ENGINE_CAMERA_H_INCLUDED
#define ENGINE_CAMERA_H_INCLUDED

#include "define.h"

#include "Math/Matrix4x4.hpp"

#include "ComponentBase.h"

namespace Engine { struct Camera; }
struct Engine::Camera final : Engine::ComponentBase<Component::Camera>
{
    float32 viewWidth  = 1920.0f; // TODO Change
    float32 viewHeight = 1080.0f; // TODO Change

    float32 fov = 0.25f * 3.1415f;

    float32 nearZ = 1.0f;
    float32 farZ  = 10000000.0f;

    Matrix4x4 projectionMatrix;
    Matrix4x4 viewMatrix;
};


#endif