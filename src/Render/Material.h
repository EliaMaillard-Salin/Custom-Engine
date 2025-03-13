#ifndef RENDER_MATERIAL_H_INCLUDED
#define RENDER_MATERIAL_H_INCLUDED
#include "BuffersStruct.h"
#include "Math/Vector.hpp"

class Texture;
class Shader;
class Render;

class Material
{
public:
    explicit Material( Shader* pShader, Render* pRender );
    ~Material() = default;

    void SetTexture( Texture* pTexture );

    bool UpdateTexture(int16 pos);

    void SetMaterialProperties( Vector<float32,4> lightColor, Vector<float32, 4> ambient, Vector<float32, 4> diffuse, Vector<float32, 4> specular, float32 shininess );

    [[nodiscard]] Texture* GetTexture();
    [[nodiscard]] Shader* GetShader();

    UploadBuffer<MaterialCB>* GetUploadBuffer();
    UploadBuffer<MaterialProperties>* GetLightUB();

    void UpdateWorldConstantBuffer(DirectX::XMMATRIX const& worldMatrix);

private:
    Texture* m_pTexture = nullptr;
    Shader* m_pShader = nullptr;

    Render* m_pRender = nullptr;

    UploadBuffer<MaterialCB> m_uploadBuffer;
    UploadBuffer<MaterialProperties> m_lightUB;

    MaterialProperties m_prop;
    int m_flags = 0;
};

#endif