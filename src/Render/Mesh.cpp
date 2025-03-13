#include "pch.h"
#include "Mesh.h"
#include "Geometry.h"
#include "Render.h"
#include "RenderUtils.h"
#include "BuffersStruct.h"
#include <vector>

Mesh::Mesh(Geometry* pGeometry, Render* pRender, int flag ) :
    m_pGeometry(pGeometry),
    m_pRender(pRender)
{
    m_flag = flag;

    UploadGeometry();
}

void Mesh::UpdateGeometry()
{
    //
}

D3D12_INDEX_BUFFER_VIEW Mesh::GetIndexBuffer()
{
    return *m_pIndexBuffer;
}

D3D12_VERTEX_BUFFER_VIEW Mesh::GetVertexBuffer()
{
    return *m_pVertexBuffer;
}

UINT Mesh::GetIndexCount()
{
    return static_cast<UINT>(m_pGeometry->indiceNumber);
}

void Mesh::ReleaseUploadBuffers()
{
    m_pIndexBufferUploader->Release();
    m_pVertexBufferUploader->Release();
}

void Mesh::UploadGeometry()
{
    // Contains all vertex datas
    std::vector<float> geometryData;

    int size = 3;
    if ( HAS_FLAG( m_flag,VERTEX_COLOR ) ) size += 4;
    if ( HAS_FLAG( m_flag,VERTEX_UV ) ) size += 2;
    if ( HAS_FLAG( m_flag,VERTEX_NORMAL ) ) size += 3;
    geometryData.reserve(m_pGeometry->positions.size() * size);

    for (int i = 0; i < m_pGeometry->positions.size(); i++)
    {
        geometryData.push_back(m_pGeometry->positions[i].x);
        geometryData.push_back(m_pGeometry->positions[i].y);
        geometryData.push_back(m_pGeometry->positions[i].z);
                         
        if ( HAS_FLAG( m_flag,VERTEX_COLOR ) )
        {
            geometryData.push_back( m_pGeometry->colors[ i ].x );
            geometryData.push_back( m_pGeometry->colors[ i ].y );
            geometryData.push_back( m_pGeometry->colors[ i ].z );
            geometryData.push_back( m_pGeometry->colors[ i ].w);
        }

        if ( HAS_FLAG(m_flag, VERTEX_UV) )
        {
            geometryData.push_back( m_pGeometry->UVs[ i ].x );
            geometryData.push_back( m_pGeometry->UVs[ i ].y );
        }

        if ( HAS_FLAG(m_flag, VERTEX_NORMAL) )
        {
            geometryData.push_back( m_pGeometry->normals[ i ].x );
            geometryData.push_back( m_pGeometry->normals[ i ].y );
            geometryData.push_back( m_pGeometry->normals[ i ].z );
        }
    }

    UINT vertexBuffByteSize = static_cast<UINT>(geometryData.size() * sizeof(float));
    UINT indexBufferByteSize = static_cast<UINT>(m_pGeometry->indexes.size() * sizeof(uint32));

    D3DCreateBlob(vertexBuffByteSize, &m_pVertexBufferCPU);
    CopyMemory(m_pVertexBufferCPU->GetBufferPointer(),geometryData.data(),vertexBuffByteSize);
    D3DCreateBlob(indexBufferByteSize, &m_pIndexBufferCPU);
    CopyMemory(m_pIndexBufferCPU->GetBufferPointer(),m_pGeometry->indexes.data(),indexBufferByteSize);

    m_pVertexBufferGPU = RenderUtils::CreateDefaultBuffer(m_pRender->GetDevice(), m_pRender->GetCommandList(), geometryData.data(), vertexBuffByteSize, m_pVertexBufferUploader);
    m_pIndexBufferGPU = RenderUtils::CreateDefaultBuffer(m_pRender->GetDevice(), m_pRender->GetCommandList(), m_pGeometry->indexes.data(), indexBufferByteSize,m_pIndexBufferUploader);
    
    m_vertexByteStride = static_cast<uint8>(sizeof(float) * size);
    m_vertexBufferByteSize = static_cast<uint32>(vertexBuffByteSize);
    m_indexFormat = DXGI_FORMAT_R32_UINT;
    m_indexBufferByteSize = static_cast<uint32>(indexBufferByteSize);

    D3D12_VERTEX_BUFFER_VIEW vertexBuffer;
    m_pVertexBufferUploader->SetName(L"vBufferUploader");
    m_pIndexBufferUploader->SetName(L"iBufferUploader"); 
    vertexBuffer.BufferLocation = m_pVertexBufferGPU->GetGPUVirtualAddress();
    vertexBuffer.StrideInBytes = static_cast<UINT>(m_vertexByteStride);
    vertexBuffer.SizeInBytes = static_cast<UINT>(m_vertexBufferByteSize);

    D3D12_INDEX_BUFFER_VIEW indexBuffer;

    indexBuffer.BufferLocation = m_pIndexBufferGPU->GetGPUVirtualAddress();
    indexBuffer.Format = m_indexFormat;
    indexBuffer.SizeInBytes = static_cast<UINT>(m_indexBufferByteSize);

    m_pVertexBuffer = new D3D12_VERTEX_BUFFER_VIEW(vertexBuffer);
    m_pIndexBuffer = new D3D12_INDEX_BUFFER_VIEW(indexBuffer);
}
