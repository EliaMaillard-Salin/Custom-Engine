#include "pch.h"
#include "Shader.h"
#include "Render.h"
#include "RenderUtils.h"

Shader::Shader(Render* pRender, char const* filePath,  int flag, D3D12_CULL_MODE cullMode, bool alpha) :
    m_pRender(pRender),
    m_filePath(filePath),
    m_alpha(alpha),
    m_flag(flag),
    m_cullMode(cullMode)
{
    Compile();
    CreateRootSign();
    CreatePso();
}

Shader::~Shader()
{
}

void Shader::Compile()
{
    std::string str = m_filePath;

    std::wstring wFilePath(str.begin(), str.end());

    UINT compileFlags = 0;
    #if defined(DEBUG) || defined(_DEBUG)  
        compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
    #endif


    ID3DBlob* errors;
    D3DCompileFromFile(wFilePath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS", "vs_5_0", compileFlags, 0, &m_pVsByte, &errors);
    if (errors != nullptr)
    {
        OutputDebugStringA((char*)errors->GetBufferPointer());
    }
    D3DCompileFromFile(wFilePath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS", "ps_5_0", compileFlags, 0, &m_pPsByte, &errors);
    if (errors != nullptr)
    {
        OutputDebugStringA((char*)errors->GetBufferPointer());
    }
    
    m_inputLayout.clear();

    UINT offset = 0;
        
    m_inputLayout.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offset, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
    offset += sizeof(DirectX::XMFLOAT3); 

    if (HAS_FLAG(m_flag,VERTEX_COLOR ))
    {
        m_inputLayout.push_back({ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offset, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
        offset += sizeof(DirectX::XMFLOAT4); 
    }

    if (HAS_FLAG(m_flag,VERTEX_UV ))
    {
        m_inputLayout.push_back({ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offset, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
        offset += sizeof(DirectX::XMFLOAT2); 
    }
    
    if (HAS_FLAG(m_flag,VERTEX_NORMAL ))
    {
        m_inputLayout.push_back({ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offset, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
        offset += sizeof(DirectX::XMFLOAT3); 
    }

}

void Shader::CreateRootSign()
{   
    CD3DX12_ROOT_PARAMETER slotRootParameter[MAX_ROOT_PARAM];
    int size = 0;
    slotRootParameter[size++].InitAsConstantBufferView(0); //Object Position
    slotRootParameter[size++].InitAsConstantBufferView(1); //Camera

    if (HAS_FLAG(m_flag, VERTEX_NORMAL))
    {
        slotRootParameter[size++].InitAsConstantBufferView(2); //Material Properties
        slotRootParameter[size++].InitAsConstantBufferView(3); //Lights
    }
    
    CD3DX12_STATIC_SAMPLER_DESC staticSample = CD3DX12_STATIC_SAMPLER_DESC(
        0, // shaderRegister
        D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
        D3D12_TEXTURE_ADDRESS_MODE_CLAMP, // addressU
        D3D12_TEXTURE_ADDRESS_MODE_CLAMP, // addressV
        D3D12_TEXTURE_ADDRESS_MODE_CLAMP, // addressW
        0.0f, // mipLODBias
        16, // maxAnisotropy
        D3D12_COMPARISON_FUNC_ALWAYS, // comparisonFunc
        D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK, // borderColor
        0.0f, // minLOD
        D3D12_FLOAT32_MAX // maxLOD
    );

    if (HAS_FLAG(m_flag, VERTEX_UV))
    {
        CD3DX12_DESCRIPTOR_RANGE texTable; 
        texTable.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV,1,0);
        m_texturePos = size;
        slotRootParameter[size++].InitAsDescriptorTable(1, &texTable);
    }
    CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc = CD3DX12_ROOT_SIGNATURE_DESC(size,slotRootParameter,1, &staticSample,D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    ID3DBlob* serializedRootSig = nullptr;
    ID3DBlob* errorBlob = nullptr;
    HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &serializedRootSig, &errorBlob);
    if (errorBlob != nullptr)
    {
        OutputDebugStringA((char*)errorBlob->GetBufferPointer());
    }
    HRESULT creationresult = m_pRender->GetDevice()->CreateRootSignature(0, serializedRootSig->GetBufferPointer(), serializedRootSig->GetBufferSize(), IID_PPV_ARGS(&m_pRootSignature));

    if (serializedRootSig != nullptr)
    {
        serializedRootSig->Release();
    }

}

void Shader::CreatePso()
{
    m_pRender->CreatePsoDesc(this, m_pPso);
}

ID3DBlob* Shader::GetVsByte()
{
    return m_pVsByte;
}

ID3DBlob* Shader::GetPsByte()
{
    return m_pPsByte;
}

std::vector<D3D12_INPUT_ELEMENT_DESC>* Shader::GetInputLayout()
{
    return &m_inputLayout;
}

ID3D12PipelineState* Shader::GetPso()
{
    return m_pPso;
}

ID3D12RootSignature* Shader::GetRootSign()
{
    return m_pRootSignature;
}

int Shader::GetFlag()
{
    return m_flag;
}

int Shader::GetTexturePosition()
{
    return m_texturePos;
}

D3D12_CULL_MODE Shader::GetCullMode()
{
    return m_cullMode;
}

bool Shader::GetAlpha()
{
    return m_alpha;
}
