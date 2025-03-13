#include "pch.h"
#include "RenderUtils.h"

ID3D12Resource* RenderUtils::CreateDefaultBuffer(
    ID3D12Device* const device, 
    ID3D12GraphicsCommandList* cmdList, 
    const void* initData, UINT64 byteSize,
    ID3D12Resource*& uploadBuffer)
{
    ID3D12Resource* defaultBuffer;

    // Create the default buffer in COPY_DEST state
    CD3DX12_HEAP_PROPERTIES defaultHeapProps(D3D12_HEAP_TYPE_DEFAULT);
    CD3DX12_RESOURCE_DESC bufferDesc = CD3DX12_RESOURCE_DESC::Buffer(byteSize);

    device->CreateCommittedResource(
        &defaultHeapProps,
        D3D12_HEAP_FLAG_NONE,
        &bufferDesc,
        D3D12_RESOURCE_STATE_COMMON, 
        nullptr,
        IID_PPV_ARGS(&defaultBuffer));

    // Create an upload buffer in GENERIC_READ state
    CD3DX12_HEAP_PROPERTIES uploadHeapProps(D3D12_HEAP_TYPE_UPLOAD);

    device->CreateCommittedResource(
        &uploadHeapProps,
        D3D12_HEAP_FLAG_NONE,
        &bufferDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&uploadBuffer));

    // Explicitly transition the buffer to COPY_DEST before copying data
    CD3DX12_RESOURCE_BARRIER transitionToCopyDest = CD3DX12_RESOURCE_BARRIER::Transition(
        defaultBuffer,
        D3D12_RESOURCE_STATE_COMMON,        // Initial state
        D3D12_RESOURCE_STATE_COPY_DEST);    // Target state

    cmdList->ResourceBarrier(1, &transitionToCopyDest);

    // Describe the data to copy
    D3D12_SUBRESOURCE_DATA subResourceData = {};
    subResourceData.pData = initData;
    subResourceData.RowPitch = byteSize;
    subResourceData.SlicePitch = subResourceData.RowPitch;

    // **Manually Copy Data to Upload Buffer**
    void* mappedData = nullptr;
    uploadBuffer->Map(0, nullptr, &mappedData);
    memcpy(mappedData, initData, byteSize);
    uploadBuffer->Unmap(0, nullptr);

    // **Copy Upload Buffer to Default Buffer**
    cmdList->CopyBufferRegion(defaultBuffer, 0, uploadBuffer, 0, byteSize);

    // Transition to VERTEX_AND_CONSTANT_BUFFER state for rendering
    CD3DX12_RESOURCE_BARRIER transitionBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
        defaultBuffer,
        D3D12_RESOURCE_STATE_COPY_DEST,
        D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
    cmdList->ResourceBarrier(1, &transitionBarrier);

    return defaultBuffer;
}

CD3DX12_STATIC_SAMPLER_DESC RenderUtils::GetStaticSamplerClamp()
{
    return CD3DX12_STATIC_SAMPLER_DESC(
        3, // shaderRegister
        D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
        D3D12_TEXTURE_ADDRESS_MODE_CLAMP, // addressU
        D3D12_TEXTURE_ADDRESS_MODE_CLAMP, // addressV
        D3D12_TEXTURE_ADDRESS_MODE_CLAMP);
}

DirectX::XMMATRIX RenderUtils::MatrixToXMMatrix(Matrix4x4 const& matrix)
{

    DirectX::XMFLOAT4X4 float4x4;

    float4x4._11 = matrix.values[0][0];
    float4x4._12 = matrix.values[0][1];
    float4x4._13 = matrix.values[0][2];
    float4x4._14 = matrix.values[0][3];

    float4x4._21 = matrix.values[1][0];
    float4x4._22 = matrix.values[1][1];
    float4x4._23 = matrix.values[1][2];
    float4x4._24 = matrix.values[1][3];
    
    float4x4._31 = matrix.values[2][0];
    float4x4._32 = matrix.values[2][1];
    float4x4._33 = matrix.values[2][2];
    float4x4._34 = matrix.values[2][3];
    
    float4x4._41 = matrix.values[3][0];
    float4x4._42 = matrix.values[3][1];
    float4x4._43 = matrix.values[3][2];
    float4x4._44 = matrix.values[3][3];

    return DirectX::XMLoadFloat4x4(&float4x4);
}

DirectX::XMFLOAT4X4 RenderUtils::MatrixToXMFloat4x4(Matrix4x4 const& matrix)
{
    DirectX::XMFLOAT4X4 float4x4;

    float4x4._11 = matrix.values[0][0];
    float4x4._12 = matrix.values[0][1];
    float4x4._13 = matrix.values[0][2];
    float4x4._14 = matrix.values[0][3];

    float4x4._21 = matrix.values[1][0];
    float4x4._22 = matrix.values[1][1];
    float4x4._23 = matrix.values[1][2];
    float4x4._24 = matrix.values[1][3];

    float4x4._31 = matrix.values[2][0];
    float4x4._32 = matrix.values[2][1];
    float4x4._33 = matrix.values[2][2];
    float4x4._34 = matrix.values[2][3];

    float4x4._41 = matrix.values[3][0];
    float4x4._42 = matrix.values[3][1];
    float4x4._43 = matrix.values[3][2];
    float4x4._44 = matrix.values[3][3];

    return float4x4;
}

DirectX::XMFLOAT4 RenderUtils::Vect4ToXMFloat4(Vector<float32, 4> const& vector)
{
    DirectX::XMFLOAT4 res;
    res.x = vector.values[0];
    res.y = vector.values[1];
    res.z = vector.values[2];
    res.w = vector.values[3];

    return res;
}

Matrix4x4 RenderUtils::XMMatrixToMatrix4x4(DirectX::XMMATRIX const& matrix)
{
    Matrix4x4 res;
    DirectX::XMFLOAT4X4 temp;

    DirectX::XMStoreFloat4x4(&temp, matrix);

    res.values[0][0] = temp._11;
    res.values[0][1] = temp._12;
    res.values[0][2] = temp._13;
    res.values[0][3] = temp._14;

    res.values[1][0] = temp._21;
    res.values[1][1] = temp._22;
    res.values[1][2] = temp._23;
    res.values[1][3] = temp._24;

    res.values[2][0] = temp._31;
    res.values[2][1] = temp._32;
    res.values[2][2] = temp._33;
    res.values[2][3] = temp._34;

    res.values[3][0] = temp._41;
    res.values[3][1] = temp._42;
    res.values[3][2] = temp._43;
    res.values[3][3] = temp._44;

    return res;
}

Matrix4x4 RenderUtils::XMFloat4x4ToMatrix4x4(DirectX::XMFLOAT4X4 const& float4x4)
{
    Matrix4x4 res;

    res.values[0][0] = float4x4._11;
    res.values[0][1] = float4x4._12;
    res.values[0][2] = float4x4._13;
    res.values[0][3] = float4x4._14;
    
    res.values[1][0] = float4x4._21;
    res.values[1][1] = float4x4._22;
    res.values[1][2] = float4x4._23;
    res.values[1][3] = float4x4._24;
        
    res.values[2][0] = float4x4._31;
    res.values[2][1] = float4x4._32;
    res.values[2][2] = float4x4._33;
    res.values[2][3] = float4x4._34;
        
    res.values[3][0] = float4x4._41;
    res.values[3][1] = float4x4._42;
    res.values[3][2] = float4x4._43;
    res.values[3][3] = float4x4._44;

    return res;
}

DirectX::XMFLOAT3 RenderUtils::Vect3ToXMFloat3(Vector3f const& vector)
{
    DirectX::XMFLOAT3 res;

    res.x = vector.x;
    res.y = vector.y;
    res.z = vector.z;

    return res;
}
