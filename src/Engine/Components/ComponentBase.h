#ifndef ENGINE_COMPONENTBASE_H_INCLUDED
#define ENGINE_COMPONENTBASE_H_INCLUDED

#include "define.h"

#include "Component.h"


namespace Engine { template <uint16 T> struct ComponentBase; }
template <uint16 T>
struct Engine::ComponentBase : Component
{
    static inline uint16 const Tag = T;
};


#endif