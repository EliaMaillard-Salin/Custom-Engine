#ifndef RENDER_TEXTURE_H_INCLUDED
#define RENDER_TEXTURE_H_INCLUDED
#include <d3d12.h>
class Graphics;


class Texture
{
public:
    Texture( char const* filePath, Graphics* pGraphics );
    ~Texture() = default;

    CD3DX12_GPU_DESCRIPTOR_HANDLE GetTextureAddress();

private:

    ID3D12Resource* m_pTexture = nullptr;
    ID3D12Resource* m_pTextureUploadHeap = nullptr;

    D3D12_DESCRIPTOR_HEAP_DESC m_srvHeapDesc;

    CD3DX12_GPU_DESCRIPTOR_HANDLE m_textureAddress;

    int m_width,m_height = 0;
};


#endif