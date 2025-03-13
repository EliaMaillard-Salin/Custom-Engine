#ifndef ENGINE_SCRIPTSYSTEM_H_INCLUDED
#define ENGINE_SCRIPTSYSTEM_H_INCLUDED

#include <vector>

namespace Engine { class Script; }


namespace Engine { class ScriptSystem; }
class Engine::ScriptSystem
{
    ScriptSystem() = default;
    ~ScriptSystem() = default;

    void UpdateScripts() {};
    void FixedUpdateScripts() {};
    void LateUpdateScripts() {};

    std::vector<Script*>* m_scripts = nullptr; // Pointer the list of Scripts in the active Scene.

    friend class GameManager;
};


#endif