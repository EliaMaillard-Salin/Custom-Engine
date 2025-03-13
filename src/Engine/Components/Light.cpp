#include "pch.h"
#include "Light.h"
#include "RenderUtils.h"


void Engine::Light::SetColor(Vector3f color)
{
	lightCB.color = RenderUtils::Vect3ToXMFloat3(color);
}

void Engine::Light::SetType(int type)
{
	lightCB.type = type;
}

void Engine::Light::SetPosition(Vector3f position)
{
	lightCB.Position = RenderUtils::Vect3ToXMFloat3(position);
}

void Engine::Light::SetIntensity(float32 intensity)
{
	lightCB.intensity = intensity;
}

void Engine::Light::SetDirection(Vector3f direction)
{
	lightCB.direction = RenderUtils::Vect3ToXMFloat3(direction);
}

void Engine::Light::SetSpotAngle(float32 angle)
{
	lightCB.spotAngle = angle;
}
