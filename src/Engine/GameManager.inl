#ifndef ENGINE_GAMEMANAGER_INL_INCLUDED
#define ENGINE_GAMEMANAGER_INL_INCLUDED

namespace Engine {


inline void GameManager::Init( HINSTANCE const hInstance ) { assert( ( s_pInstance == nullptr ) ); s_pInstance = new GameManager( hInstance ); }
inline void GameManager::Run() { s_pInstance->GameLoop(); }
inline void GameManager::Release() { assert( ( s_pInstance != nullptr ) ); delete s_pInstance; }


inline Timer& GameManager::GetTimer() { return *s_pInstance->m_pTimer; }
inline Window& GameManager::GetWindow() { return *s_pInstance->m_pWindow; }

inline InputSystem& GameManager::GetInputSystem() { return *s_pInstance->m_pInputSystem; }
inline PhysicsSystem& GameManager::GetPhysicsSystem() { return *s_pInstance->m_pPhysicsSystem; }
inline GameplaySystem& GameManager::GetGameplaySystem() { return *s_pInstance->m_pGameplaySystem; }
inline CollisionSystem& GameManager::GetCollisionSystem() { return *s_pInstance->m_pCollisionSystem; }
inline ScriptSystem& GameManager::GetScriptSystem() { return *s_pInstance->m_pScriptSystem; }
inline RenderSystem& GameManager::GetRenderSystem() { return *s_pInstance->m_pRenderSystem; }

inline std::vector<Scene>& GameManager::GetScenes() { return s_pInstance->m_scenes; }
inline Scene& GameManager::GetActiveScene() { return *s_pInstance->m_pActiveScene; }

inline float32& GameManager::GetFixedDeltaTime() { return s_pInstance->m_fixedDeltaTime;  }


}

#endif
