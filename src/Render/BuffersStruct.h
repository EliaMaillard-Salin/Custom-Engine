#ifndef RENDER_BUFFERSTRUCT_H_INCLUDED
#define RENDER_BUFFERSTRUCT_H_INCLUDED

#include <DirectXMath.h>
#include <d3dx12.h>


struct ConstantBuffer
{};

struct CameraCB : ConstantBuffer
{
    DirectX::XMFLOAT4X4 projectionMatrix;
    DirectX::XMFLOAT4X4 viewMatrix;
};

struct MaterialCB : ConstantBuffer
{
    DirectX::XMFLOAT4X4 worldMatrix;
};

struct MaterialProperties : ConstantBuffer
{
    DirectX::XMFLOAT4 ambientLightColor;
    DirectX::XMFLOAT4 ambient;
    DirectX::XMFLOAT4 diffuse;
    DirectX::XMFLOAT4 specular;
    float shininess;
    float padding[3];
};

struct LightCB : ConstantBuffer
{
    DirectX::XMFLOAT3 color;
    int type;

    DirectX::XMFLOAT3 direction;
    float intensity;

    DirectX::XMFLOAT3 Position;
    float spotAngle;

    float padding[4];
};

template <typename T>
struct UploadBuffer
{
    UploadBuffer(ID3D12Device* device, UINT elementCount, bool isConstantBuffer);
    ~UploadBuffer() = default;
    ID3D12Resource* GetResource();

    void CopyData(int elementIndex, const void* data, int dataAmount);

private:
    ID3D12Resource* m_pResource;
    BYTE* m_mappedData = nullptr;
    UINT m_elementByteSize = 0;
    bool m_isConstantBuffer = false;

    UINT CalcConstantBufferByteSize(UINT byteSize)
    {
        return (byteSize + 255) & ~255;
    }
};

template<typename T>
inline UploadBuffer<T>::UploadBuffer(ID3D12Device* pDevice, UINT elementCount, bool isConstantBuffer) :
    m_isConstantBuffer(isConstantBuffer)
{
    m_elementByteSize = sizeof(T);

    if (m_isConstantBuffer)
        m_elementByteSize = CalcConstantBufferByteSize(sizeof(T));


    CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(m_elementByteSize * elementCount);
    CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);

    HRESULT hr = pDevice->CreateCommittedResource(
        &heapProps,
        D3D12_HEAP_FLAG_NONE,   
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ, 
        nullptr,    
        IID_PPV_ARGS(&m_pResource) );

    m_pResource->Map(0, nullptr, reinterpret_cast<void**>(&m_mappedData) );
}

template<typename T>
inline ID3D12Resource* UploadBuffer<T>::GetResource()
{
    return m_pResource;
}

template<typename T>
inline void UploadBuffer<T>::CopyData(int elementIndex, const void* data, int dataAmount)
{
    std::memcpy(&m_mappedData[elementIndex * m_elementByteSize], data, sizeof(T) * dataAmount);
}

#endif