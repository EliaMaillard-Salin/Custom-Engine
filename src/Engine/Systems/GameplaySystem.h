#ifndef ENGINE_GAMEPLAYSYSTEM_H_INCLUDED
#define ENGINE_GAMEPLAYSYSTEM_H_INCLUDED

#include <vector>

#include "define.h"

namespace Engine { struct MeshRenderer; }
namespace Engine { struct CharacterController; }


namespace Engine { class GameplaySystem; }
class Engine::GameplaySystem
{
    GameplaySystem();
    ~GameplaySystem() = default;

    void Init();

    void HandleCharacterControllers();
    void HandleShooting();

    void Shoot();

    float32 m_shootingRate = 0.0f;
    float32 m_elapsedTime  = 0.0f;
    MeshRenderer* m_pBulletTemplate = nullptr;

    std::vector<CharacterController*> m_characterControllers;
    
    friend class Scene;
    friend class GameManager;
};


#endif