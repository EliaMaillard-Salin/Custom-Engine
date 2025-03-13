#ifndef ENGINE_GAMEOBJECT_H_INCLUDED
#define ENGINE_GAMEOBJECT_H_INCLUDED

#include <unordered_map>
#include <vector>

#include "define.h"

#include "GameTransform.h"

namespace Engine { struct Component; }
namespace Engine { class Script; }

namespace Engine { class Scene; }


namespace Engine { class GameObject; }
class Engine::GameObject
{
public:
    explicit GameObject( Scene& scene );
    virtual ~GameObject() = default;

    void Destroy();

    template <class ComponentClass> [[nodiscard]] bool HasComponent() const;
    template <class ComponentClass> [[nodiscard]] ComponentClass const& GetComponent() const;
    template <class ComponentClass> [[nodiscard]] ComponentClass& GetComponent();
    template <class ComponentClass> ComponentClass& AddComponent();
    template <class ComponentClass> void RemoveComponent();

    // template <class ScriptClass>
    // [[nodiscard]] ScriptClass const* GetScript() const; // [CALL ME]
    // template <class ScriptClass>
    // [[nodiscard]] ScriptClass* GetScript(); // [CALL ME]
    // template <class ScriptClass>
    // ScriptClass* AddScript(); // [CALL ME]
    // template <class ScriptClass>
    // ScriptClass* RemoveScript(); // [CALL ME]

    [[nodiscard]] bool IsActive() const;
    void SetActive( bool active );
    void Activate();
    void Deactivate();

    [[nodiscard]] uint32 GetID() const;
    [[nodiscard]] char const* GetName() const;
    [[nodiscard]] Scene const& GetScene() const;
    [[nodiscard]] GameObject const* GetParent() const;
    [[nodiscard]] std::vector<GameObject*> const& GetChildren() const;

    [[nodiscard]] Scene& GetScene();
    [[nodiscard]] GameObject* GetParent();
    [[nodiscard]] std::vector<GameObject*>& GetChildren();

    void SetName( char const* name );

    GameTransform transform = GameTransform::Identity; // GameObject's transform.

private:
    // State
    bool m_created     = false; // Whether this GameObject was created
    bool m_toBeCreated = true;  // Whether this GameObject was queued to be created
    bool m_toBeDeleted = false; // Whether this GameObject was queued to be deleted
    bool m_active      = true;  // Whether this GameObject is active and should be processed

    // Identification
    uint32      m_id   = 0;       // GameObject's unique identifier
    char const* m_name = nullptr; // GameObject's name

    // Relationships
    Scene*                                 m_pScene            = nullptr; // Pointer to the GameObject's Scene
    GameObject*                            m_pParent           = nullptr; // Pointer to the GameObject's parent
    std::vector<GameObject*>               m_children;                    // Vector of pointers to the GameObject's children
    std::unordered_map<uint16, Component*> m_components;                  // Map of pointers to the GameObject's Components
    std::unordered_map<uint16, Script*>    m_scripts;                     // Map of pointers to the GameObject's Scripts
    uint64                                 m_componentsBitmask = 0;       // Bitmask showing Components that the GameObject has

    friend class GameTransform;
    friend class Scene;
};


#include "GameObject.inl"

#endif