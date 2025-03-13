#ifndef ENGINE_INPUTSYSTEM_H_INCLUDED
#define ENGINE_INPUTSYSTEM_H_INCLUDED

#include <unordered_map>

#include "define.h"

namespace Engine::Mouse { enum Button: uint8; }
namespace Engine::Mouse { bool GetButton( Button button ); }
namespace Engine::Mouse { bool GetButtonUp( Button button ); }
namespace Engine::Mouse { bool GetButtonDown( Button button ); }
namespace Engine::Keyboard { enum Key: uint8; }
namespace Engine::Keyboard { bool GetKey( Key key ); }
namespace Engine::Keyboard { bool GetKeyUp( Key key ); }
namespace Engine::Keyboard { bool GetKeyDown( Key key ); }


namespace Engine { struct InputSystem; }
struct Engine::InputSystem final
{
    static Vector2f GetMousePos();
private:
    inline static InputSystem* s_pInstance = nullptr;

    InputSystem();
    ~InputSystem() = default;

    void Update();


    std::unordered_map<uint8, int32> m_keyboardMap;
    std::unordered_map<uint8, int32> m_mouseMap;

    enum States: uint8 {
        None    = 0b000,
        Pressed = 0b011,
        Up      = 0b100,
        Down    = 0b001,
    };

    static States s_mouseStates[];
    static States s_keyboardStates[];

    friend bool Mouse::GetButton( Mouse::Button button );
    friend bool Mouse::GetButtonUp( Mouse::Button button );
    friend bool Mouse::GetButtonDown( Mouse::Button button );
    friend bool Keyboard::GetKey( Keyboard::Key key );
    friend bool Keyboard::GetKeyUp( Keyboard::Key key );
    friend bool Keyboard::GetKeyDown( Keyboard::Key key );
    friend class GameManager;
};


#endif