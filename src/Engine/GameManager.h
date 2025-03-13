#ifndef ENGINE_GAMEMANAGER_H_INCLUDED
#define ENGINE_GAMEMANAGER_H_INCLUDED

#include <vector>

#include "define.h"

#include "Scene.h"


struct HINSTANCE__;
using HINSTANCE = HINSTANCE__*;

class Timer;
class Window;

namespace Engine { class InputSystem; }
namespace Engine { class PhysicsSystem; }
namespace Engine { class GameplaySystem; }
namespace Engine { class CollisionSystem; }
namespace Engine { class ScriptSystem; }
namespace Engine { class RenderSystem; }


namespace Engine { class GameManager; }
class Engine::GameManager
{
public:
    static void Init( HINSTANCE hInstance );
    static void Run();
    static void Release();

    [[nodiscard]] static Timer& GetTimer();
    [[nodiscard]] static Window& GetWindow();

    [[nodiscard]] static InputSystem& GetInputSystem();
    [[nodiscard]] static PhysicsSystem& GetPhysicsSystem();
    [[nodiscard]] static GameplaySystem& GetGameplaySystem();
    [[nodiscard]] static CollisionSystem& GetCollisionSystem();
    [[nodiscard]] static ScriptSystem& GetScriptSystem();
    [[nodiscard]] static RenderSystem& GetRenderSystem();

    [[nodiscard]] static std::vector<Scene>& GetScenes();
    [[nodiscard]] static Scene& GetActiveScene();
    [[nodiscard]] static float32& GetFixedDeltaTime();
    
private:
    inline static GameManager* s_pInstance = nullptr;

    explicit GameManager( HINSTANCE hInstance );
    ~GameManager();

    void GameLoop();

    void HandleCreations();
    void HandleDeletions();

    // System
    Timer*  m_pTimer  = nullptr; // Timer (pointer)
    Window* m_pWindow = nullptr; // Window (pointer)

    // Components Logic
    InputSystem*     m_pInputSystem     = nullptr; // Input System (pointer)
    PhysicsSystem*   m_pPhysicsSystem   = nullptr; // Physic System (pointer)
    GameplaySystem*  m_pGameplaySystem  = nullptr; // Gameplay System (pointer)
    CollisionSystem* m_pCollisionSystem = nullptr; // Collision System (pointer)
    ScriptSystem*    m_pScriptSystem    = nullptr; // Script System (pointer)
    RenderSystem*    m_pRenderSystem    = nullptr; // Render System (pointer)

    // Scenes
    std::vector<Scene>  m_scenes;                     // Vector of all Scenes in the Game
    std::vector<Scene*> m_loadedScenes;               // Vector of loaded Scenes (pointers)
    Scene*              m_pActiveScene     = nullptr; // Active Scene (pointer)
    Scene*              m_pNextActiveScene = nullptr; // Scene to be active (pointer)

    // Creations / Loads
    std::vector<Scene*> m_scenesToLoad;   // Vector of Scenes to be loaded (pointers)

    float32 m_fixedDeltaTime = 0.016f;
    float32 m_elapsedTime = 0.0f;

    friend class GameObject;
    friend class Scene;
};

#include "GameManager.inl"

#endif