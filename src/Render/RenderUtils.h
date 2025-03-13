#pragma once
#include "Math/Matrix4x4.hpp"
#include "Math/Vector.hpp"

namespace RenderUtils
{
    ID3D12Resource* CreateDefaultBuffer(
        ID3D12Device* const device,
        ID3D12GraphicsCommandList* cmdList, 
        const void* initData, UINT64 byteSize, 
        ID3D12Resource*& uploadBuffer);

    CD3DX12_STATIC_SAMPLER_DESC GetStaticSamplerClamp();


    DirectX::XMMATRIX MatrixToXMMatrix(Matrix4x4 const& matrix);

    DirectX::XMFLOAT4X4 MatrixToXMFloat4x4(Matrix4x4 const& matrix);

    DirectX::XMFLOAT4 Vect4ToXMFloat4(Vector<float32, 4> const& vector);

    Matrix4x4 XMMatrixToMatrix4x4(DirectX::XMMATRIX const& matrix);

    Matrix4x4 XMFloat4x4ToMatrix4x4(DirectX::XMFLOAT4X4 const& float4x4);

    DirectX::XMFLOAT3 Vect3ToXMFloat3(Vector3f const& vector);
};

