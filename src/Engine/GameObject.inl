#ifndef ENGINE_GAMEOBJECT_INL_INCLUDED
#define ENGINE_GAMEOBJECT_INL_INCLUDED

#include "Scene.h"
namespace Engine {


template <class ComponentClass>
bool GameObject::HasComponent() const { return m_componentsBitmask & ( 1 << ( ComponentClass::Tag - 1 ) ); }

template <class ComponentClass>
ComponentClass const& GameObject::GetComponent() const
{
    assert( HasComponent<ComponentClass>() );
    return *static_cast<ComponentClass const*>( m_components[ComponentClass::Tag] );
}

template <class ComponentClass>
ComponentClass& GameObject::GetComponent()
{
    assert( HasComponent<ComponentClass>() );
    return *static_cast<ComponentClass*>( m_components[ComponentClass::Tag] );
}


inline void GameObject::SetActive( bool const active ) { m_active = active; }
inline void GameObject::Activate() { m_active = true; }
inline void GameObject::Deactivate() { m_active = false; }

inline uint32 GameObject::GetID() const { return m_id; }
inline char const* GameObject::GetName() const { return m_name; }
inline Scene const& GameObject::GetScene() const { return *m_pScene; }
inline GameObject const* GameObject::GetParent() const { return m_pParent; }
inline std::vector<GameObject*> const& GameObject::GetChildren() const { return m_children; }

inline Scene& GameObject::GetScene() { return *m_pScene; }
inline GameObject* GameObject::GetParent() { return m_pParent; }
inline std::vector<GameObject*>& GameObject::GetChildren() { return m_children; }

inline void GameObject::SetName(char const* name) { m_name = name; }


}

#endif