#ifndef ENGINE_MESHRENDERER_H_INCLUDED
#define ENGINE_MESHRENDERER_H_INCLUDED

#include "define.h"

#include "ComponentBase.h"
#include "Math/Vector.hpp"

struct Geometry;
class Material;
class Mesh;
class Shader;

namespace Engine { struct Sprite; }


namespace Engine { struct MeshRenderer; }
struct Engine::MeshRenderer : Engine::ComponentBase<Component::MeshRenderer>
{
    uint8 renderLayer = 0; // MeshRenderer's render layer (used to determine the order in which sprites are rendered).

    static Shader* CreateShader(const char* path, int flags, int cullMod = 3);

    void SetSprite( Sprite const& sprite );

    void SetSphere();   // Create a red Sphere without Light
    void SetSphere(Vector<float32,4> color, bool hasLight = false); // Create a Sphere with or without Light and a custom color
    void SetSphere(const char* texturePath);    // Create a Sphere with texture no light
    void SetSphere(Shader* pShader, int flags, Vector<float32, 4> color = Vector<float32,4>({1.0f,0.0f,0.0f,0.0f}));    // Create a Sphere with custom shader no texture
    void SetSphere(Shader* pShader, int flags, const char* texturePath );    // Create a Sphere with custom shader and texture

    void SetCube();   // Create a red Cube without Light
    void SetCube(Vector<float32, 4> color, bool hasLight = false); // Create a Cube with or without Light and a custom color
    void SetCube(const char* texturePath);    // Create a Cube with texture no light
    void SetCube(Shader* pShader, int flags, Vector<float32, 4> color = Vector<float32, 4>({ 1.0f,0.0f,0.0f,0.0f }));    // Create a Cube with custom shader no texture
    void SetCube(Shader* pShader, int flags, const char* texturePath);    // Create a Cube with custom shader and texture

    void SetMaterialProperties(Vector<float32, 4> lightColor, Vector<float32, 4> ambient, Vector<float32, 4> diffuse, Vector<float32, 4> specular, float32 shininess);

    void SetCustomObject(const char* objPath, Vector<float32, 4> color, bool hasLight = false);
    void SetCustomObject(const char* objPath, const char* texturePath);
    void SetCustomObject(const char* objPath, Shader* pShader, int flag, Vector<float32,4> color = Vector<float32, 4>({ 1.0f,0.0f,0.0f,0.0f }));
    void SetCustomObject(const char* objPath, Shader* pShader, int flag, const char* texturePath);

    void Duplicate(MeshRenderer* pMesh);

    ~MeshRenderer() override;

private:
    void Free();

    bool      m_primitive = false;
    Geometry* m_pGeometry = nullptr;
    Material* m_pMaterial = nullptr;
    Mesh*     m_pMesh     = nullptr;
    Shader*   m_pShader   = nullptr;

    bool m_bloomingObject = false;

    friend class RenderSystem;
};


#include "MeshRenderer.inl"

#endif