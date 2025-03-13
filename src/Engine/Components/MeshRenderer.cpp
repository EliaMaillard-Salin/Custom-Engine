#include "pch.h"
#include "MeshRenderer.h"
#include "Systems/RenderSystem.h"

#include "PrimitiveFactory.h"
#include "Geometry.h"
#include "Material.h"
#include "Mesh.h"
#include "Shader.h"
#include "Graphics.h"

#include "Sprite.h"

#include "Window.h"
#include "GameManager.h"

namespace Engine {

    Shader* MeshRenderer::CreateShader(const char* path, int flags, int cullMod)
    {
        Graphics& graphics = *GameManager::GetWindow().GetGraphics();
        return graphics.CreateShader(path,flags,(D3D12_CULL_MODE)cullMod);
    }


    void MeshRenderer::SetSprite( Sprite const& sprite )
{
    Free();
    m_pGeometry = sprite.m_pGeometry;
    m_pMaterial = sprite.m_pMaterial;
    m_pMesh     = sprite.m_pMesh;
    m_pShader   = sprite.m_pShader;
}

    void Engine::MeshRenderer::Duplicate(MeshRenderer* pMesh)
    {
        pMesh->m_pGeometry = m_pGeometry;
        pMesh->m_pMesh = m_pMesh;

        pMesh->m_pShader = m_pShader;

        pMesh->m_pMaterial = GameManager::GetWindow().GetGraphics()->CreateMaterial( m_pShader );
    }



void MeshRenderer::SetSphere()
{
    Free();
    Graphics& graphics = *GameManager::GetWindow().GetGraphics();
    
    m_pGeometry = graphics.CreatePrimitiveGeometry( SPHERE );
    
    int flag = 0;
    SET_FLAG( flag,VERTEX_COLOR );

    m_pShader = GameManager::GetRenderSystem().GetShader(RenderSystem::SHADER_COLOR);

    m_pMesh = graphics.CreateMesh( m_pGeometry, flag );
    m_pMaterial = graphics.CreateMaterial( m_pShader );

    m_primitive = true;
}

void MeshRenderer::SetSphere(Vector<float32, 4> color, bool hasLight)
{
    Free();
    Graphics& graphics = *GameManager::GetWindow().GetGraphics();

    m_pGeometry = graphics.CreatePrimitiveGeometry(SPHERE, color);

    int flag = 0;
    SET_FLAG(flag, VERTEX_COLOR);
    if (hasLight)
    {
        SET_FLAG(flag, VERTEX_NORMAL);
        m_pShader = GameManager::GetRenderSystem().GetShader(RenderSystem::SHADER_LIGHTCOLOR);
    }
    else
        m_pShader = GameManager::GetRenderSystem().GetShader(RenderSystem::SHADER_COLOR);

    m_pMesh = graphics.CreateMesh(m_pGeometry, flag);
    m_pMaterial = graphics.CreateMaterial(m_pShader);

    m_primitive = true;
}

void MeshRenderer::SetSphere(const char* texturePath)
{
    Free();
    Graphics& graphics = *GameManager::GetWindow().GetGraphics();

    m_pGeometry = graphics.CreatePrimitiveGeometry(SPHERE);

    int flag = 0;
    SET_FLAG(flag, VERTEX_UV);

    m_pShader = GameManager::GetRenderSystem().GetShader(RenderSystem::SHADER_TEXTURE);

    m_pMesh = graphics.CreateMesh(m_pGeometry, flag);
    Texture* pTexture = graphics.CreateTexture(texturePath);
    
    m_pMaterial = graphics.CreateMaterial(m_pShader);
    m_pMaterial->SetTexture(pTexture);

    m_primitive = true;
}

void MeshRenderer::SetSphere(Shader* pShader, int flags, Vector<float32,4> color)
{
    Free();
    Graphics& graphics = *GameManager::GetWindow().GetGraphics();

    m_pGeometry = graphics.CreatePrimitiveGeometry(SPHERE, color);

    m_pShader = pShader;

    m_pMesh = graphics.CreateMesh(m_pGeometry, flags);
    m_pMaterial = graphics.CreateMaterial(m_pShader);

    m_primitive = true;
}

void MeshRenderer::SetSphere(Shader* pShader, int flags, const char* texturePath)
{
    Free();
    Graphics& graphics = *GameManager::GetWindow().GetGraphics();

    m_pGeometry = graphics.CreatePrimitiveGeometry(SPHERE);

    m_pShader = pShader;

    m_pMesh = graphics.CreateMesh(m_pGeometry, flags);

    m_pMaterial = graphics.CreateMaterial(m_pShader);
    
    Texture* pTexture = graphics.CreateTexture(texturePath);
    m_pMaterial->SetTexture(pTexture);
    
    m_primitive = true;
}




void MeshRenderer::SetCube()
{
    Free();
    Graphics& graphics = *GameManager::GetWindow().GetGraphics();
    
    m_pGeometry = graphics.CreatePrimitiveGeometry( CUBE );
    
    int flag = 0;
    SET_FLAG( flag,VERTEX_COLOR );

    m_pShader = GameManager::GetRenderSystem().GetShader(RenderSystem::SHADER_COLOR);

    m_pMesh = graphics.CreateMesh( m_pGeometry, flag );
    m_pMaterial = graphics.CreateMaterial( m_pShader );

    m_primitive = true;
}

void MeshRenderer::SetCube(Vector<float32, 4> color, bool hasLight)
{
    Free();
    Graphics& graphics = *GameManager::GetWindow().GetGraphics();

    m_pGeometry = graphics.CreatePrimitiveGeometry(CUBE, color);

    int flag = 0;
    SET_FLAG(flag, VERTEX_COLOR);
    if (hasLight)
    {
        SET_FLAG(flag, VERTEX_NORMAL);
        m_pShader = GameManager::GetRenderSystem().GetShader(RenderSystem::SHADER_LIGHTCOLOR);
    }
    else
        m_pShader = GameManager::GetRenderSystem().GetShader(RenderSystem::SHADER_COLOR);

    m_pMesh = graphics.CreateMesh(m_pGeometry, flag);
    m_pMaterial = graphics.CreateMaterial(m_pShader);

    m_primitive = true;
}

void MeshRenderer::SetCube(const char* texturePath)
{
    Free();
    Graphics& graphics = *GameManager::GetWindow().GetGraphics();

    m_pGeometry = graphics.CreatePrimitiveGeometry(CUBE);

    int flag = 0;
    SET_FLAG(flag, VERTEX_UV);

    m_pShader = GameManager::GetRenderSystem().GetShader(RenderSystem::SHADER_TEXTURE);

    m_pMesh = graphics.CreateMesh(m_pGeometry, flag);
    Texture* pTexture = graphics.CreateTexture(texturePath);

    m_pMaterial = graphics.CreateMaterial(m_pShader);
    m_pMaterial->SetTexture(pTexture);

    m_primitive = true;
}

void MeshRenderer::SetCube(Shader* pShader, int flags, Vector<float32, 4> color)
{
    Free();
    Graphics& graphics = *GameManager::GetWindow().GetGraphics();

    m_pGeometry = graphics.CreatePrimitiveGeometry(CUBE, color);

    m_pShader = pShader;

    m_pMesh = graphics.CreateMesh(m_pGeometry, flags);
    m_pMaterial = graphics.CreateMaterial(m_pShader);

    m_primitive = true;
}

void MeshRenderer::SetCube(Shader* pShader, int flags, const char* texturePath)
{
    Free();
    Graphics& graphics = *GameManager::GetWindow().GetGraphics();

    m_pGeometry = graphics.CreatePrimitiveGeometry(CUBE);

    m_pShader = pShader;

    m_pMesh = graphics.CreateMesh(m_pGeometry, flags);

    m_pMaterial = graphics.CreateMaterial(m_pShader);

    Texture* pTexture = graphics.CreateTexture(texturePath);
    m_pMaterial->SetTexture(pTexture);

    m_primitive = true;
}

void MeshRenderer::Free()
{
    if ( m_primitive == false ) return;
    delete m_pGeometry;
    delete m_pMaterial;
    delete m_pMesh;
    delete m_pShader;
    m_pGeometry = nullptr;
    m_pMaterial = nullptr;
    m_pMesh     = nullptr;
    m_pShader   = nullptr;
    m_primitive = false;
}


void MeshRenderer::SetMaterialProperties(Vector<float32, 4> lightColor, Vector<float32, 4> ambient, Vector<float32, 4> diffuse, Vector<float32, 4> specular, float32 shininess)
{
    m_pMaterial->SetMaterialProperties(lightColor, ambient, diffuse, specular, shininess);
}

void MeshRenderer::SetCustomObject( const char* objPath,Vector<float32,4> color,bool hasLight )
{
    Free();
    Graphics& graphics = *GameManager::GetWindow().GetGraphics();

    m_pGeometry = graphics.CreateGeometryFromFile( objPath, color );

    int flag = 0;
    SET_FLAG( flag,VERTEX_COLOR );
    if ( hasLight )
    {
        SET_FLAG( flag,VERTEX_NORMAL );
        m_pShader = GameManager::GetRenderSystem().GetShader(RenderSystem::SHADER_LIGHTCOLOR);
    }
    else
        m_pShader = GameManager::GetRenderSystem().GetShader(RenderSystem::SHADER_COLOR);


    m_pMesh = graphics.CreateMesh( m_pGeometry, flag );
    m_pMaterial = graphics.CreateMaterial( m_pShader );

    m_primitive = true;
}

void MeshRenderer::SetCustomObject( const char* objPath,const char* texturePath )
{
    Free();
    Graphics& graphics = *GameManager::GetWindow().GetGraphics();

    m_pGeometry = graphics.CreateGeometryFromFile(objPath);

    int flag = 0;
    SET_FLAG(flag, VERTEX_UV);

    m_pShader = GameManager::GetRenderSystem().GetShader(RenderSystem::SHADER_TEXTURE);

    m_pMesh = graphics.CreateMesh(m_pGeometry, flag);
    Texture* pTexture = graphics.CreateTexture(texturePath);

    m_pMaterial = graphics.CreateMaterial(m_pShader);
    m_pMaterial->SetTexture(pTexture);

    m_primitive = true;
}

void MeshRenderer::SetCustomObject( const char* objPath,Shader* pShader,int flag,Vector<float32,4> color )
{
    Free();
    Graphics& graphics = *GameManager::GetWindow().GetGraphics();

    m_pGeometry = graphics.CreateGeometryFromFile(objPath, color);

    m_pShader = pShader;

    m_pMesh = graphics.CreateMesh(m_pGeometry, flag);
    m_pMaterial = graphics.CreateMaterial(m_pShader);

    m_primitive = true;
}

void MeshRenderer::SetCustomObject( const char* objPath,Shader* pShader,int flag,const char* texturePath )
{
    Free();
    Graphics& graphics = *GameManager::GetWindow().GetGraphics();

    m_pGeometry = graphics.CreateGeometryFromFile(objPath);

    m_pShader = pShader;

    m_pMesh = graphics.CreateMesh(m_pGeometry, flag);

    m_pMaterial = graphics.CreateMaterial(m_pShader);

    Texture* pTexture = graphics.CreateTexture(texturePath);
    m_pMaterial->SetTexture(pTexture);

    m_primitive = true;
}

}