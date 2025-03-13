#ifndef RENDER_SHADER_H_INCLUDED
#define RENDER_SHADER_H_INCLUDED
#include <d3d12.h>
#include <vector>
#include "RenderDefine.h"
#define MAX_ROOT_PARAM 64

class Render;


class Shader
{
public:
    Shader( Render* pRender, char const* filePath, int flag, D3D12_CULL_MODE cullMode, bool alphablend);
    ~Shader();

    void Compile();
    void CreateRootSign();
    void CreatePso();

    ID3DBlob* GetVsByte();
    ID3DBlob* GetPsByte();
    std::vector<D3D12_INPUT_ELEMENT_DESC>* GetInputLayout();

    ID3D12PipelineState* GetPso();

    [[nodiscard]] ID3D12RootSignature* GetRootSign();
    int GetFlag();
    int GetTexturePosition();
    D3D12_CULL_MODE GetCullMode();
    bool GetAlpha();
private:
    ID3DBlob* m_pVsByte = nullptr;
    ID3DBlob* m_pPsByte = nullptr;
    D3D12_CULL_MODE m_cullMode;

    const char* m_filePath;

    Render* m_pRender;

    ID3D12PipelineState* m_pPso = nullptr;

    ID3D12RootSignature* m_pRootSignature = nullptr;

    std::vector<D3D12_INPUT_ELEMENT_DESC> m_inputLayout {};

    int m_flag;
    int m_texturePos;
    bool m_alpha;
};


#endif