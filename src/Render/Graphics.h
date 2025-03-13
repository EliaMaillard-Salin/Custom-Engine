#ifndef RENDER_GRAPHICS_H_INCLUDED
#define RENDER_GRAPHICS_H_INCLUDED
#include <DirectXMath.h>
#include "define.h"
#include "Render.h"
#include "RenderDefine.h"
#include "Math/Vector.hpp"
#include "Math/Vector3.hpp"
#include "Math/Matrix4x4.hpp"
#undef far
#undef near

class Window;
struct Geometry;
class Mesh;
class Texture;
class Material;
class Shader;
struct LightCB;
enum PrimitiveType : uint8;


class Graphics
{
public:
    explicit Graphics(Window* pWindow);
    ~Graphics();

    [[nodiscard]] Geometry* CreatePrimitiveGeometry(PrimitiveType primitiveType, Vector<float32, 4> const& color = Vector<float32, 4>( { 1.0f, 0.0f, 0.0f, 1.0f } ) ); // Create with PrimitiveFactory
    [[nodiscard]] Geometry* CreateGeometryFromFile( char const* filePath, Vector<float32, 4> const& color = Vector<float32, 4>({ 1.0f, 0.0f, 0.0f, 1.0f }));         // Create with file
    [[nodiscard]] Mesh*     CreateMesh( Geometry* pGeometry, int flag );            // Create Index & Vertex Buffer
    [[nodiscard]] Texture*  CreateTexture( char const* filePath );                  // Create Texture from Path
    [[nodiscard]] Shader*   CreateShader( char const* filePath, int flag, D3D12_CULL_MODE cullMode = D3D12_CULL_MODE_BACK, bool alpha = false);          // Create shader from path
    [[nodiscard]] Material* CreateMaterial( Shader* pShader );                      // Create Material from shader
    void AddLight(LightCB* pLight);

    void UpdateCamera(Matrix4x4 const& projectionMatrix, Matrix4x4 const& viewMatrix);

    void UpdateCameraAt(Vector3f const& position,
        Vector3f const& target,
        Vector3f const& up,
        float32 viewWidth,
        float32 viewHeight,
        float32 fov,
        float32 near,
        float32 far,
        Matrix4x4& projectionMatrix,
        Matrix4x4& viewMatrix);

    void UpdateCameraTo(Vector3f const& position,
        Vector3f const& direction,
        Vector3f const& up,
        float32 viewWidth,
        float32 viewHeight,
        float32 fov,
        float32 near,
        float32 far,
        Matrix4x4& projectionMatrix,
        Matrix4x4& viewMatrix);

    Render* GetRender();

    void Clear();
    void Display();

    void DrawObject(Mesh* pMesh, Material* pMaterial, Matrix4x4 const& objworldMatrix);

private:

    Render m_render;
    // UploadBuffer m_camera; // (view proj constant buffer)

    friend class Window;
};


#endif