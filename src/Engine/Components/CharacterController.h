#ifndef ENGINE_CHARACTERCONTROLLER_H_INCLUDED
#define ENGINE_CHARACTERCONTROLLER_H_INCLUDED

#include "define.h"

#include "Keyboard.h"

#include "ComponentBase.h"

namespace Engine { class GameObject; }


namespace Engine { struct CharacterController; }
struct Engine::CharacterController final : ComponentBase<Component::CharacterController>
{
    float32 speed = 1.0f;
    float32 sprintSpeed = 2.0f;
    float32 sensitivity = 0.2f;

    bool isFollowing = false;
    GameObject* followObject = nullptr;

    struct {
        Keyboard::Key forward  = Keyboard::Key::Z;
        Keyboard::Key left     = Keyboard::Key::Q;
        Keyboard::Key backward = Keyboard::Key::S;
        Keyboard::Key right    = Keyboard::Key::D;
        Keyboard::Key up       = Keyboard::Key::Space;
        Keyboard::Key down     = Keyboard::Key::LControl;
        Keyboard::Key sprint   = Keyboard::Key::LShift;

        Keyboard::Key switchView = Keyboard::Key::Tab;
    } keys;

    friend class GameplaySystem;
};


#endif