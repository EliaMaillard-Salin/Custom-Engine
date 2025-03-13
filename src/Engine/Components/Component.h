#ifndef ENGINE_COMPONENT_H_INCLUDED
#define ENGINE_COMPONENT_H_INCLUDED

#include "define.h"

namespace Engine { class GameObject; }


namespace Engine { struct Component; }
struct Engine::Component
{
    enum Tag : uint16 {
        None,
        MeshRenderer,
        SphereCollider,
        BoxCollider,
        RigidBody,
        CharacterController,
        Camera,
        Light,
        Shot,
    };

    void Destroy();

    [[nodiscard]] bool IsActive() const;
    void SetActive( bool active );
    void Activate();
    void Deactivate();

    [[nodiscard]] GameObject const& GetOwner() const;

    [[nodiscard]] GameObject& GetOwner();

protected:
    Component() = default;
    virtual ~Component() = default;
    
    bool m_active      = true;  // Whether this Component is active and should be processed
    bool m_created     = false; // Whether this Component was created
    bool m_toBeCreated = true;  // Whether this Component was queued to be created
    bool m_toBeDeleted = false; // Whether this Component was queued to be deleted
    
    GameObject* m_pOwner = nullptr;

    friend class GameObject;
    friend class Scene;
};


#include "Component.inl"

#endif