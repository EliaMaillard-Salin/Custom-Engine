#ifndef RENDER_MESH_H_INCLUDED
#define RENDER_MESH_H_INCLUDED
#include <d3d12.h>
#include "RenderDefine.h"
struct Geometry;
class Render;

class Mesh
{
public:
    Mesh( Geometry* pGeometry, Render* pRender, int flag  );
    ~Mesh() = default;

    void UpdateGeometry(); //Updates geometry in upload buffers
    [[nodiscard]] D3D12_INDEX_BUFFER_VIEW GetIndexBuffer();
    [[nodiscard]] D3D12_VERTEX_BUFFER_VIEW GetVertexBuffer();
    [[nodiscard]] UINT GetIndexCount();
    void ReleaseUploadBuffers();

private:
    void UploadGeometry(); //Puts geometry in upload buffers

    Geometry* m_pGeometry = nullptr;
    Render* m_pRender = nullptr;

    D3D12_INDEX_BUFFER_VIEW* m_pIndexBuffer = nullptr;
    D3D12_VERTEX_BUFFER_VIEW* m_pVertexBuffer = nullptr;

    ID3D12Resource* m_pVertexBufferGPU = nullptr;
    ID3D12Resource* m_pIndexBufferGPU = nullptr;

    ID3D12Resource* m_pVertexBufferUploader = nullptr;
    ID3D12Resource* m_pIndexBufferUploader = nullptr;

    ID3DBlob* m_pVertexBufferCPU = nullptr;
    ID3DBlob* m_pIndexBufferCPU = nullptr;

    uint8 m_vertexByteStride = 0;
    uint32 m_vertexBufferByteSize = 0;
    DXGI_FORMAT m_indexFormat = DXGI_FORMAT_R16_UINT;
    uint32 m_indexBufferByteSize = 0;

    int m_flag;
};


#endif