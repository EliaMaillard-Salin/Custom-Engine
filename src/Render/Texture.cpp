#include "pch.h"
#include "Texture.h"
#include "DDSTextureLoader.h"
#include "Graphics.h"

Texture::Texture( char const* filePath,Graphics* pGraphics )
{
	HRESULT hr;

	std::string str = filePath;

	std::wstring wFilePath(str.begin(), str.end());

	hr = DirectX::CreateDDSTextureFromFile12(pGraphics->GetRender()->GetDevice(),pGraphics->GetRender()->GetCommandList(),
		wFilePath.c_str(),&m_pTexture,&m_pTextureUploadHeap,m_width,m_height);
	if (hr != S_OK)
	{}

	UINT size = pGraphics->GetRender()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	CD3DX12_CPU_DESCRIPTOR_HANDLE handleDescriptor(pGraphics->GetRender()->GetCbvSrvUavDescriptorHeap()->GetCPUDescriptorHandleForHeapStart());
	handleDescriptor.Offset(0, size);

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Format = m_pTexture->GetDesc().Format;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = m_pTexture->GetDesc().MipLevels;
	srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;

	pGraphics->GetRender()->GetDevice()->CreateShaderResourceView(m_pTexture,&srvDesc,handleDescriptor);


	m_textureAddress = CD3DX12_GPU_DESCRIPTOR_HANDLE(pGraphics->GetRender()->GetCbvSrvUavDescriptorHeap()->GetGPUDescriptorHandleForHeapStart());
	m_textureAddress.Offset(0, size);

}

CD3DX12_GPU_DESCRIPTOR_HANDLE Texture::GetTextureAddress()
{
	return m_textureAddress;
}
