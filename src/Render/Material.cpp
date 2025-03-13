#include "pch.h"
#include "Material.h"
#include "Render.h"
#include "Shader.h"
#include "Texture.h"
#include "RenderUtils.h"

Material::Material(Shader* pShader, Render* pRender) :
    m_pShader(pShader),
    m_pRender(pRender),
    m_uploadBuffer(pRender->GetDevice(), 1, 1),
    m_flags(pShader->GetFlag()),
    m_lightUB(pRender->GetDevice(), 1, 1)
{

    m_prop.ambientLightColor = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    m_prop.ambient = DirectX::XMFLOAT4(0.55f, 0.55f, 0.55f, 1.0f);
    m_prop.diffuse = DirectX::XMFLOAT4(0.25f, 0.25f, 0.25f, 1.0f);
    m_prop.specular = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    m_prop.shininess = 5.0f;

    m_lightUB.CopyData(0, &m_prop, 1);

}

void Material::SetTexture(Texture* pTexture)
{
    if (HAS_FLAG(m_flags, VERTEX_UV) == false) return;
    m_pTexture = pTexture;
}

bool Material::UpdateTexture(int16 pos)
{
    if (m_pTexture != nullptr )
    {
        m_pRender->GetCommandList()->SetGraphicsRootDescriptorTable(pos, m_pTexture->GetTextureAddress());
    }
    return true;
}

void Material::SetMaterialProperties(Vector<float32, 4> lightColor, Vector<float32, 4> ambient, Vector<float32, 4> diffuse, Vector<float32, 4> specular, float32 shininess)
{
    m_prop.ambientLightColor = RenderUtils::Vect4ToXMFloat4(lightColor);
    m_prop.ambient = RenderUtils::Vect4ToXMFloat4(ambient);
    m_prop.diffuse = RenderUtils::Vect4ToXMFloat4(diffuse);
    m_prop.specular = RenderUtils::Vect4ToXMFloat4(specular);
    m_prop.shininess = shininess;

    m_lightUB.CopyData(0, &m_prop, 1);
}

Texture* Material::GetTexture()
{
    return m_pTexture;
}

Shader* Material::GetShader()
{
    return m_pShader;
}

UploadBuffer<MaterialCB>* Material::GetUploadBuffer()
{
    return &m_uploadBuffer;
}

UploadBuffer<MaterialProperties>* Material::GetLightUB()
{
    return &m_lightUB;
}

void Material::UpdateWorldConstantBuffer(DirectX::XMMATRIX const& worldMatrix)
{
    MaterialCB materialCB;
    DirectX::XMStoreFloat4x4(&materialCB.worldMatrix, DirectX::XMMatrixTranspose(worldMatrix));

    m_uploadBuffer.CopyData(0, &materialCB, 1);
}
