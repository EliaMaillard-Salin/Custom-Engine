#include "pch.h"
#include "InputSystem.h"

#include "Math/Vector2.hpp"

#include <windows.h>

#include "Mouse.h"
#include "Keyboard.h"

namespace Engine {

InputSystem::States InputSystem::s_mouseStates[Mouse::AMOUNT] {};
InputSystem::States InputSystem::s_keyboardStates[Keyboard::AMOUNT] {};


InputSystem::InputSystem():
    m_keyboardMap{
        { Keyboard::Backspace, VK_BACK },
        { Keyboard::Tab, VK_TAB },
        { Keyboard::Return, VK_RETURN },
        { Keyboard::Pause, VK_PAUSE },
        { Keyboard::CapsLock, VK_CAPITAL },
        { Keyboard::Escape, VK_ESCAPE },
        { Keyboard::Space, VK_SPACE },
        { Keyboard::PageUp, VK_PRIOR },
        { Keyboard::PageDown, VK_NEXT },
        { Keyboard::End, VK_END },
        { Keyboard::Home, VK_HOME },
        { Keyboard::Left, VK_LEFT },
        { Keyboard::Up, VK_UP },
        { Keyboard::Right, VK_RIGHT },
        { Keyboard::Down, VK_DOWN },
        { Keyboard::Insert, VK_INSERT },
        { Keyboard::Delete, VK_DELETE },
        { Keyboard::LWindow, VK_LWIN },
        { Keyboard::RWindow, VK_RWIN },
        { Keyboard::Numpad0, VK_NUMPAD0 },
        { Keyboard::Numpad1, VK_NUMPAD1 },
        { Keyboard::Numpad2, VK_NUMPAD2 },
        { Keyboard::Numpad3, VK_NUMPAD3 },
        { Keyboard::Numpad4, VK_NUMPAD4 },
        { Keyboard::Numpad5, VK_NUMPAD5 },
        { Keyboard::Numpad6, VK_NUMPAD6 },
        { Keyboard::Numpad7, VK_NUMPAD7 },
        { Keyboard::Numpad8, VK_NUMPAD8 },
        { Keyboard::Numpad9, VK_NUMPAD9 },
        { Keyboard::NumpadMultiply, VK_MULTIPLY },
        { Keyboard::NumpadAdd, VK_ADD },
        { Keyboard::NumpadSubtract, VK_SUBTRACT },
        { Keyboard::NumpadDecimal, VK_DECIMAL },
        { Keyboard::NumpadDivide, VK_DIVIDE },
        { Keyboard::F1, VK_F1 },
        { Keyboard::F2, VK_F2 },
        { Keyboard::F3, VK_F3 },
        { Keyboard::F4, VK_F4 },
        { Keyboard::F5, VK_F5 },
        { Keyboard::F6, VK_F6 },
        { Keyboard::F7, VK_F7 },
        { Keyboard::F8, VK_F8 },
        { Keyboard::F9, VK_F9 },
        { Keyboard::F10, VK_F10 },
        { Keyboard::F11, VK_F11 },
        { Keyboard::F12, VK_F12 },
        { Keyboard::NumLock, VK_NUMLOCK },
        { Keyboard::ScrollLock, VK_SCROLL },
        { Keyboard::LShift, VK_LSHIFT },
        { Keyboard::RShift, VK_RSHIFT },
        { Keyboard::LControl, VK_LCONTROL },
        { Keyboard::RControl, VK_RCONTROL },
        { Keyboard::LAlt, VK_LMENU },
        { Keyboard::RAlt, VK_RMENU },
        { Keyboard::A, 'A' },
        { Keyboard::B, 'B' },
        { Keyboard::C, 'C' },
        { Keyboard::D, 'D' },
        { Keyboard::E, 'E' },
        { Keyboard::F, 'F' },
        { Keyboard::G, 'G' },
        { Keyboard::H, 'H' },
        { Keyboard::I, 'I' },
        { Keyboard::J, 'J' },
        { Keyboard::K, 'K' },
        { Keyboard::L, 'L' },
        { Keyboard::M, 'M' },
        { Keyboard::N, 'N' },
        { Keyboard::O, 'O' },
        { Keyboard::P, 'P' },
        { Keyboard::Q, 'Q' },
        { Keyboard::R, 'R' },
        { Keyboard::S, 'S' },
        { Keyboard::T, 'T' },
        { Keyboard::U, 'U' },
        { Keyboard::V, 'V' },
        { Keyboard::W, 'W' },
        { Keyboard::X, 'X' },
        { Keyboard::Y, 'Y' },
        { Keyboard::Z, 'Z' },
    },
    m_mouseMap{
        { Mouse::Left, VK_LBUTTON },
        { Mouse::Right, VK_RBUTTON },
        { Mouse::Middle, VK_MBUTTON },
        { Mouse::Extra1, VK_XBUTTON1 },
        { Mouse::Extra2, VK_XBUTTON2 },
    }
{
    assert( s_pInstance == nullptr );
    s_pInstance = this;
}


void InputSystem::Update()
{
    for ( uint8 i = 0; i < Keyboard::AMOUNT; i++ )
        s_keyboardStates[i] = GetAsyncKeyState( m_keyboardMap[i] ) ?
            ( s_keyboardStates[i] & Pressed ? Pressed : Down ) :
            ( s_keyboardStates[i] & Pressed ? Up : None );

    for ( uint8 i = 0; i < Mouse::AMOUNT; i++ )
        s_mouseStates[i] = GetAsyncKeyState( m_mouseMap[i] ) ?
            ( s_mouseStates[i] & Pressed ? Pressed : Down ) :
            ( s_mouseStates[i] & Pressed ? Up : None );
}

Vector2f InputSystem::GetMousePos()
{
    Vector2f mousePos;
    POINT lpMousePos;
    GetCursorPos( &lpMousePos );

    mousePos.x = lpMousePos.x;
    mousePos.y = lpMousePos.y;

    return mousePos;
}


}