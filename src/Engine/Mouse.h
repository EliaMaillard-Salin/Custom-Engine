#ifndef ENGINE_MOUSE_H_INCLUDED
#define ENGINE_MOUSE_H_INCLUDED

#include "define.h"

#include "Systems/InputSystem.h"


namespace Engine::Mouse {

enum Button: uint8 {
    Left,
    Right,
    Middle,
    Extra1,
    Extra2,
    AMOUNT
};

inline bool GetButton( Button const button ) { return InputSystem::s_mouseStates[button] & InputSystem::States::Pressed; }
inline bool GetButtonUp( Button const button ) { return InputSystem::s_mouseStates[button] == InputSystem::States::Up;  };
inline bool GetButtonDown( Button const button ) { return InputSystem::s_mouseStates[button] == InputSystem::States::Down;  };

}


#endif