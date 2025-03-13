#ifndef ENGINE_SPRITE_H_INCLUDED
#define ENGINE_SPRITE_H_INCLUDED

struct Geometry;
class Material;
class Mesh;
class Shader;


namespace Engine { struct Sprite; }
struct Engine::Sprite
{
    explicit Sprite( char const* path );
    
private:
    Geometry* m_pGeometry = nullptr;
    Material* m_pMaterial = nullptr;
    Mesh*     m_pMesh     = nullptr;
    Shader*   m_pShader   = nullptr;

    friend struct MeshRenderer;
    friend class RenderSystem;
};


#endif