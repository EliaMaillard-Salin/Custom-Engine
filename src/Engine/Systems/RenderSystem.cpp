#include "pch.h"
#include "RenderSystem.h"

#include "Render.h"
#include "Graphics.h"

#include "Sprite.h"

#include "Components/Camera.h"

#include "GameObject.h"

#include "GameManager.h"

namespace Engine {


void RenderSystem::HandleRendering()
{
    m_pGraphics->Clear();

    GameObject* const pMainCamera = GameManager::GetActiveScene().GetMainCamera();
    Camera& mainCameraComponent = pMainCamera->GetComponent<Camera>();
    m_pGraphics->UpdateCameraTo(
        pMainCamera->transform.GetPosition(),
        pMainCamera->transform.GetForward(),
        pMainCamera->transform.GetUp(),
        mainCameraComponent.viewWidth,
        mainCameraComponent.viewHeight,
        mainCameraComponent.fov,
        mainCameraComponent.nearZ,
        mainCameraComponent.farZ,
        mainCameraComponent.projectionMatrix,
        mainCameraComponent.viewMatrix
    );

    for (std::vector<MeshRenderer const*> const& meshRendererLayer : m_meshRenderers)
    {
        for ( MeshRenderer const* const pMeshRenderer : meshRendererLayer )
        {
            if ( pMeshRenderer->m_active )
                m_pGraphics->DrawObject( pMeshRenderer->m_pMesh, pMeshRenderer->m_pMaterial, pMeshRenderer->m_pOwner->transform.GetWorldMatrix() );
        }
    }
    m_pGraphics->Display();
}

void RenderSystem::CreateBasicsShaders()
{
    int flagLightColor;
    SET_FLAG(flagLightColor, VERTEX_COLOR);
    SET_FLAG(flagLightColor, VERTEX_NORMAL);
    m_basicShaders[SHADER_COLOR] = m_pGraphics->CreateShader("../../res/Render/Color.hlsl", VERTEX_COLOR);
    m_basicShaders[SHADER_LIGHTCOLOR] = m_pGraphics->CreateShader("../../res/Render/LightColor.hlsl", flagLightColor);
    m_basicShaders[SHADER_TEXTURE] = m_pGraphics->CreateShader("../../res/Render/texture.hlsl", VERTEX_UV);
}

Shader* RenderSystem::GetShader(uint8 shaderType)
{
    return m_basicShaders[shaderType];
}


}