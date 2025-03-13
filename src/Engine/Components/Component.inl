#ifndef ENGINE_COMPONENT_INL_INCLUDED
#define ENGINE_COMPONENT_INL_INCLUDED

namespace Engine {


inline void Component::SetActive( bool const active ) { m_active = active; }
inline void Component::Activate() { m_active = true; }
inline void Component::Deactivate() { m_active = false; }

inline GameObject const& Component::GetOwner() const { return *m_pOwner; }

inline GameObject& Component::GetOwner() { return *m_pOwner; }


}

#endif