#include "pch.h"
#include "Graphics.h"
#include "PrimitiveFactory.h"
#include "OBJLoader.h"
#include "Geometry.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "Texture.h"
#include "Window.h"
#include "RenderUtils.h"

Graphics::Graphics( Window* pWindow ):
    m_render( pWindow, pWindow->GetWidth(), pWindow->GetHeight() )
{
    PrimitiveFactory::InitPrimitiveGeometry();
}

Graphics::~Graphics()
{
}

Geometry* Graphics::CreatePrimitiveGeometry(PrimitiveType primitiveType, Vector<float32, 4> const& color)
{
    Geometry const* const pGeo = PrimitiveFactory::GetPrimitiveGeometry(primitiveType);

    Geometry* pResult = new Geometry();
    *pResult = *pGeo;

    for (int i = 0; i < pResult->indexes.size(); i++)
        pResult->colors.push_back(RenderUtils::Vect4ToXMFloat4(color));

    return pResult;
}

Geometry* Graphics::CreateGeometryFromFile(char const* filePath, Vector<float32, 4> const& color)
{
    return OBJLoader::LoadOBJ(filePath, RenderUtils::Vect4ToXMFloat4(color) );
}

Mesh* Graphics::CreateMesh(Geometry* pGeometry, int flag  )
{
    m_render.ResetCommandList();
    Mesh* pMesh = new Mesh( pGeometry,&m_render, flag);
    m_render.CloseCommandList();
    m_render.ExecuteCommandList();
    m_render.FlushCommandQueue(true);
    pMesh->ReleaseUploadBuffers();
    return pMesh;
}

Texture* Graphics::CreateTexture(char const* filePath)
{
    m_render.ResetCommandList();
    Texture* pTexture = new Texture( filePath,this );
    m_render.CloseCommandList();
    m_render.ExecuteCommandList();
    m_render.FlushCommandQueue(true);
    return pTexture;
}

Shader* Graphics::CreateShader(char const* filePath, int flag, D3D12_CULL_MODE cullMode, bool alpha)
{
    Shader* pShader = new Shader(&m_render, filePath, flag, cullMode, alpha);
    return pShader;
}

Material* Graphics::CreateMaterial(Shader* pShader)
{
    Material* pMat = new Material(pShader, &m_render);
    return pMat;
}


void Graphics::UpdateCamera( Matrix4x4 const& projectionMatrix, Matrix4x4 const& viewMatrix )
{
    CameraCB cameraData = {};

    cameraData.viewMatrix = RenderUtils::MatrixToXMFloat4x4(viewMatrix);
    cameraData.projectionMatrix = RenderUtils::MatrixToXMFloat4x4(projectionMatrix);

    m_render.m_pCbCurrentViewProjInstance->CopyData(0, &cameraData, 1);
}

void Graphics::AddLight(LightCB* pLight)
{
    m_render.m_lightSources.push_back(*pLight);
}

void Graphics::UpdateCameraAt(Vector3f const& position, Vector3f const& target, Vector3f const& up, float32 viewWidth, float32 viewHeight, float32 fov, float32 near, float32 far, Matrix4x4& projectionMatrix, Matrix4x4& viewMatrix)
{
    
    DirectX::XMFLOAT3 d12Position = RenderUtils::Vect3ToXMFloat3(position);
    DirectX::XMFLOAT3 d12Target = RenderUtils::Vect3ToXMFloat3(target);
    DirectX::XMFLOAT3 d12Up = RenderUtils::Vect3ToXMFloat3(up);

    DirectX::XMVECTOR camPos = XMLoadFloat3(&d12Position);
    DirectX::XMVECTOR camTarget = XMLoadFloat3(&d12Target);
    DirectX::XMVECTOR camUp = XMLoadFloat3(&d12Up);

    DirectX::XMMATRIX tempProj = DirectX::XMMatrixPerspectiveFovLH(fov, viewWidth / viewHeight, near, far);
    DirectX::XMMATRIX tempView = DirectX::XMMatrixLookAtLH(camPos, camTarget, camUp);

    projectionMatrix = RenderUtils::XMMatrixToMatrix4x4(DirectX::XMMatrixTranspose(tempProj));
    viewMatrix = RenderUtils::XMMatrixToMatrix4x4(DirectX::XMMatrixTranspose(tempView));

    CameraCB camera = {};
    camera.projectionMatrix = RenderUtils::MatrixToXMFloat4x4(projectionMatrix);
    camera.viewMatrix = RenderUtils::MatrixToXMFloat4x4(viewMatrix);

    m_render.m_pCbCurrentViewProjInstance->CopyData(0, &camera, 1);
}

void Graphics::UpdateCameraTo(Vector3f const& position, Vector3f const& target, Vector3f const& up, float32 viewWidth, float32 viewHeight, float32 fov, float32 near, float32 far, Matrix4x4& projectionMatrix, Matrix4x4& viewMatrix)
{
    DirectX::XMFLOAT3 d12Position = RenderUtils::Vect3ToXMFloat3(position);
    DirectX::XMFLOAT3 d12Target = RenderUtils::Vect3ToXMFloat3(target);
    DirectX::XMFLOAT3 d12Up = RenderUtils::Vect3ToXMFloat3(up);

    DirectX::XMVECTOR camPos = XMLoadFloat3(&d12Position);
    DirectX::XMVECTOR camTarget = XMLoadFloat3(&d12Target);
    DirectX::XMVECTOR camUp = XMLoadFloat3(&d12Up);

    DirectX::XMMATRIX tempProj = DirectX::XMMatrixPerspectiveFovLH(fov, viewWidth / viewHeight, near, far);
    DirectX::XMMATRIX tempView = DirectX::XMMatrixLookToLH(camPos, camTarget, camUp);

    projectionMatrix = RenderUtils::XMMatrixToMatrix4x4(DirectX::XMMatrixTranspose(tempProj));
    viewMatrix = RenderUtils::XMMatrixToMatrix4x4(DirectX::XMMatrixTranspose(tempView));

    CameraCB camera = {};
    camera.projectionMatrix = RenderUtils::MatrixToXMFloat4x4(projectionMatrix);
    camera.viewMatrix = RenderUtils::MatrixToXMFloat4x4(viewMatrix);

    m_render.m_pCbCurrentViewProjInstance->CopyData(0, &camera, 1);
}


Render* Graphics::GetRender()
{
    return &m_render;
}

void Graphics::Clear()
{
    m_render.PrepareDraw();
}

void Graphics::Display()
{
    m_render.CompleteDraw();
}

void Graphics::DrawObject(Mesh* pMesh, Material* pMaterial, Matrix4x4 const& objworldMatrix)
{
    m_render.DrawObject(pMesh, pMaterial, objworldMatrix);
}
