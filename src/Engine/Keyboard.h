#ifndef ENGINE_KEYBOARD_H_INCLUDED
#define ENGINE_KEYBOARD_H_INCLUDED

#include "define.h"

#include "Systems/InputSystem.h"


namespace Engine::Keyboard {

enum Key: uint8 {
    Escape, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

    
                                                   Backspace,
    Tab,                                           Return,
    CapsLock,
    LShift,                                        RShift,
    LControl, LWindow, LAlt, Space, RAlt, RWindow, RControl,

    
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

    
    ScrollLock, Pause,
    Insert,     Home,  PageUp,
    Delete,     End,   PageDown,
    
                Up,
    Left,       Down,  Right,

    
    NumLock, NumpadDivide, NumpadMultiply, NumpadSubtract,
    Numpad7, Numpad8,      Numpad9,        NumpadAdd,
    Numpad4, Numpad5,      Numpad6,
    Numpad1, Numpad2,      Numpad3,        NumpadReturn,
    Numpad0,               NumpadDecimal,

    AMOUNT,

    // Aliases

    LeftShift  = LShift,
    RightShift = RShift,

    LeftControl  = LControl,
    RightControl = RControl,

    LeftAlt  = LAlt,
    RightAlt = RAlt,
    AltGr    = RAlt,

    LeftWindow  = LWindow,
    RightWindow = RWindow,

    UpArrow    = Up,
    LeftArrow  = Left,
    DownArrow  = Down,
    RightArrow = Right,

    Enter       = Return,
    NumpadEnter = NumpadReturn,

    Spacebar = Space,
};

inline bool GetKey( Key const key ) { return InputSystem::s_keyboardStates[key] & InputSystem::States::Pressed; }
inline bool GetKeyUp( Key const key ) { return InputSystem::s_keyboardStates[key] == InputSystem::States::Up; };
inline bool GetKeyDown( Key const key ) { return InputSystem::s_keyboardStates[key] == InputSystem::States::Down;  };

}


#endif