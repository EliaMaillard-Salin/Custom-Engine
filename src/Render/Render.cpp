#include "pch.h"
#include "Render.h"
#include "Window.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "BuffersStruct.h"
#include "RenderUtils.h"


Render::Render( Window* const pWindow, uint32 const renderWidth, uint32 const renderHeight ):
	m_pWindow( pWindow ),
    m_renderWidth( renderWidth ),
    m_renderHeight( renderHeight ),
	m_pCbCurrentViewProjInstance(nullptr)
{
	InitRenderPipeline();
	m_pCbCurrentViewProjInstance = new UploadBuffer<CameraCB>(m_pDevice, 1, 1);
	m_pCbCurrentLightInstance = new UploadBuffer<LightCB>(m_pDevice, 100, 1);
}

Render::~Render()
{
	m_pRtvHeap->Release();
	m_pDsvHeap->Release();
	m_pCbvSrvUavDescriptorHeap->Release();

	for ( int i = 0; i < m_swapChainBufferCount; ++i )
		m_pSwapChainBuffer[i]->Release();

	m_pCommandList->Release();
	m_pDirectCmdListAlloc->Release();
	
	m_pCommandQueue->Release();
	
	m_pFence->Release();
	
	m_pDevice->Release();
	m_pFactory->Release();
}

void Render::InitRenderPipeline()
{
	HRESULT creationResult;

	#if defined(DEBUG) || defined(_DEBUG) 
		{
			D3D12GetDebugInterface(IID_PPV_ARGS(&m_pDebugController));
			m_pDebugController->EnableDebugLayer();
		}
	#endif

	CreateDXGIFactory1(IID_PPV_ARGS(&m_pFactory));
	// // 9 Steps : 
	// 1 Create Device

	creationResult = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_pDevice));

	//Check if succesfully create Device
	if (FAILED(creationResult))
	{
		IDXGIAdapter* pWarpAdapter;
		m_pFactory->EnumWarpAdapter(IID_PPV_ARGS(&pWarpAdapter));
		D3D12CreateDevice(pWarpAdapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_pDevice));
		std::cout << "Failed To create Device WarpAdapter Used." << std::endl;
	}

	// 2 Create Fence

	creationResult = m_pDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_pFence));
	
	if (FAILED(creationResult))
	{
		std::cout << "Failed creating Fence." << std::endl;
	}
	// 3 Check MSAA
	
	// Get Descriptor Size
	m_rtvDescriptorSize = m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	m_dsvDescriptorSize = m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	m_cbvSrvUavDescriptorSize = m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	
	D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS msQualityLevels;
	msQualityLevels.Format = m_backBufferFormat;
	msQualityLevels.SampleCount = 4;
	msQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
	msQualityLevels.NumQualityLevels = 0;

	creationResult = m_pDevice->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &msQualityLevels, sizeof(msQualityLevels));
	if (FAILED(creationResult)) {} // Todo Return error

	m_4xMsaaQuality = msQualityLevels.NumQualityLevels;
	assert(m_4xMsaaQuality > 0 && "Unexpected MSAA quality level.");

	// 4 Create Command List, Queue, Allocator 

	CreateCommandObjects();

	// 5 Swap Chain
	
	creationResult = CreateSwapChain();
	if (FAILED(creationResult)) {} // Todo Return error
	
	// 6 Descriptor Heaps
	CreateDescHeap(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, m_swapChainBufferCount, D3D12_DESCRIPTOR_HEAP_FLAG_NONE, m_pRtvHeap);
	if (FAILED(creationResult)) {} // Todo Return error

	CreateDescHeap(D3D12_DESCRIPTOR_HEAP_TYPE_DSV, 1, D3D12_DESCRIPTOR_HEAP_FLAG_NONE, m_pDsvHeap);
	if (FAILED(creationResult)) {} // Todo Return error

	CreateDescHeap(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 1000, D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE, m_pCbvSrvUavDescriptorHeap);
	if (FAILED(creationResult)) {} // Todo Return error

	Resize();

}


void Render::CreateCommandObjects()
{
	HRESULT creationResult;

	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

	creationResult = m_pDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_pCommandQueue));
	if (creationResult != S_OK)
		return;

	//Command Allocator creation 
	creationResult = m_pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_pDirectCmdListAlloc));
	if (FAILED(creationResult))
		return;

	//Command List creation
	creationResult = m_pDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_pDirectCmdListAlloc, nullptr, IID_PPV_ARGS(&m_pCommandList));
	if (FAILED(creationResult))
		return;
	
	// Close because need to be reset at first frame and need to be closed when reseted
	CloseCommandList();

}

HRESULT Render::CreateSwapChain()
{
	if (m_pSwapChain != nullptr)
	{
		m_pSwapChain->Release();
	}

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChainDesc.Width = m_renderWidth;  // Width of the back buffer
	swapChainDesc.Height = m_renderHeight; // Height of the back buffer
	swapChainDesc.Format = m_backBufferFormat; // Back buffer format (e.g., DXGI_FORMAT_R8G8B8A8_UNORM)
	swapChainDesc.Stereo = FALSE;  // Stereo 3D disabled
	swapChainDesc.SampleDesc.Count = 1;  // No MSAA for swap chain buffers
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // Back buffer is a render target
	swapChainDesc.BufferCount = 2;  // Use triple buffering for smooth performance
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // Best for DX12
	swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // Allows fullscreen switching

	IDXGISwapChain1* swapChain;
	HRESULT hr = m_pFactory->CreateSwapChainForHwnd(m_pCommandQueue, m_pWindow->GetHWND(), &swapChainDesc, nullptr, nullptr, &swapChain);

	hr = swapChain->QueryInterface(__uuidof(IDXGISwapChain3), (void**)&m_pSwapChain);

	return hr;
}


void Render::UpdateViewPort()
{
	m_screenViewport = { 0.0f, 0.0f, static_cast<float>(m_renderWidth), static_cast<float>(m_renderHeight), 0.0f, 1.0f };
	m_scissorRect = { 0, 0, m_renderWidth, m_renderHeight };
}


bool Render::ResetCommandList()
{
	HRESULT hr;
	hr = m_pDirectCmdListAlloc->Reset();
	if (hr != S_OK)
		return false;
	hr = m_pCommandList->Reset(m_pDirectCmdListAlloc,nullptr); // m_pipelineState ? 
	if (hr != S_OK)
		return false;
	return true;
}

void Render::ExecuteCommandList()
{
	ID3D12CommandList* ppCommandLists[] = { m_pCommandList };
	m_pCommandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
}

void Render::CloseCommandList()
{
	HRESULT res = m_pCommandList->Close();
	if (FAILED(res)) {} // TODO return error
}


bool Render::FlushCommandQueue(bool isGpuIdle)
{
	m_currentFence++;
	HRESULT hr;
	hr = m_pCommandQueue->Signal(m_pFence, m_currentFence);
	if (hr != S_OK)
		return false;
	// Wait until the GPU has completed commands up to this fence point.

	if (m_pFence->GetCompletedValue() < m_currentFence && isGpuIdle == true)
	{
		HANDLE eventHandle = CreateEventEx(nullptr, nullptr, false, EVENT_ALL_ACCESS);

		hr = m_pFence->SetEventOnCompletion(m_currentFence, eventHandle);
		if (hr != S_OK)
			return false;


		WaitForSingleObject(eventHandle, INFINITE);
		CloseHandle(eventHandle);
	}
	return true;
}


bool Render::PrepareDraw()
{
	// Reset CommandList and Alloc

	if (!ResetCommandList())
		return false;

	CD3DX12_RESOURCE_BARRIER const resourceBarrier = CD3DX12_RESOURCE_BARRIER::Transition( m_pSwapChainBuffer[m_currBackBuffer], D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET );
	m_pCommandList->ResourceBarrier( 1, &resourceBarrier );

	m_pCommandList->RSSetViewports(1, &m_screenViewport);
	m_pCommandList->RSSetScissorRects(1, &m_scissorRect);
	
	// Clear the back buffer and depth buffer.
	
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = m_pRtvHeap->GetCPUDescriptorHandleForHeapStart();
	rtvHandle.ptr += m_currBackBuffer * m_rtvDescriptorSize;

	m_pCommandList->ClearRenderTargetView(rtvHandle, DirectX::Colors::Black, 1, &m_scissorRect);
	m_pCommandList->ClearDepthStencilView(m_depthStencilBufferAddress,D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL,1.0f, 0, 1, &m_scissorRect);

	m_pCommandList->OMSetRenderTargets(1, &rtvHandle, true, &m_depthStencilBufferAddress);

	m_pCommandList->SetDescriptorHeaps(1,&m_pCbvSrvUavDescriptorHeap);
	
	return true;
}

bool Render::DrawObject(Mesh* pMesh, Material* pMaterial, Matrix4x4 const& objWorldMatrix)
{
	assert(pMaterial != nullptr);
	assert(pMesh != nullptr);

	Shader* pShader = pMaterial->GetShader();
	assert(pShader != nullptr);

	UpdateLights();
	pMaterial->UpdateWorldConstantBuffer( RenderUtils::MatrixToXMMatrix(objWorldMatrix) );

	m_pCommandList->SetPipelineState(pShader->GetPso());
	m_pCommandList->SetGraphicsRootSignature(pShader->GetRootSign());

	m_pCommandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	D3D12_VERTEX_BUFFER_VIEW pVertexBufferView = pMesh->GetVertexBuffer();
	m_pCommandList->IASetVertexBuffers(0, 1, &pVertexBufferView);
	D3D12_INDEX_BUFFER_VIEW pIndexBufferView = pMesh->GetIndexBuffer();
	m_pCommandList->IASetIndexBuffer(&pIndexBufferView);

	pMaterial->UpdateTexture(pShader->GetTexturePosition());

	m_pCommandList->SetGraphicsRootConstantBufferView(0, pMaterial->GetUploadBuffer()->GetResource()->GetGPUVirtualAddress()); // Object Matrix
	
	m_pCommandList->SetGraphicsRootConstantBufferView(1, m_pCbCurrentViewProjInstance->GetResource()->GetGPUVirtualAddress()); //Camera

	if (HAS_FLAG(pShader->GetFlag(), VERTEX_NORMAL))
	{
		m_pCommandList->SetGraphicsRootConstantBufferView(2, pMaterial->GetLightUB()->GetResource()->GetGPUVirtualAddress()); // MAterial properties

		m_pCommandList->SetGraphicsRootConstantBufferView(3, m_pCbCurrentLightInstance->GetResource()->GetGPUVirtualAddress()); // Lights
	}
	m_pCommandList->DrawIndexedInstanced(pMesh->GetIndexCount(), 1, 0, 0, 0);
	return true;
}

bool Render::CompleteDraw()
{

	CD3DX12_RESOURCE_BARRIER desc = CD3DX12_RESOURCE_BARRIER::Transition(m_pSwapChainBuffer[m_currBackBuffer], D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	m_pCommandList->ResourceBarrier(1,&desc);
	
	CloseCommandList();

	ExecuteCommandList();

	// swap the back and front buffers
	HRESULT hr = m_pSwapChain->Present(1, 0);
	if (hr != S_OK)
		return false;

	m_currBackBuffer = (m_currBackBuffer + 1) % m_swapChainBufferCount;

	if (!FlushCommandQueue(true))
		return false;
	
	return true;
}

void Render::UpdateLights()
{
	int size = m_lightSources.size();
	m_pCbCurrentLightInstance->CopyData(0, m_lightSources.data(), size);
}

ID3D12DescriptorHeap* Render::GetCbvSrvUavDescriptorHeap()
{
	return m_pCbvSrvUavDescriptorHeap;
}

void Render::Resize()
{
	assert( m_pDevice != nullptr );
	assert( m_pSwapChain != nullptr );

	ResetCommandList();

	ReleasePreviousResources();
	ResizeSwapChainBuffers();

	CreateRenderTargetView();
	CreateDepthStencilBufferAndView();

	CloseCommandList();
	ExecuteCommandList();
	FlushCommandQueue(true);

	UpdateViewPort();
}

void Render::ReleasePreviousResources()
{
	for ( uint32 i = 0; i < m_swapChainBufferCount; i++ )
		if ( m_pSwapChainBuffer[i] != nullptr ) m_pSwapChainBuffer[i]->Release();
	if ( m_pDepthStencilBuffer != nullptr ) m_pDepthStencilBuffer->Release();
}

void Render::ResizeSwapChainBuffers()
{
	m_pSwapChain->ResizeBuffers(
		m_swapChainBufferCount,
		m_renderWidth,
		m_renderHeight,
		m_backBufferFormat,
		DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
	);
	m_currBackBuffer = 0;
}

HRESULT Render::CreatePsoDesc(Shader* pShader, ID3D12PipelineState*& pPso)
{
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;

	ID3DBlob* pVsByteShader = pShader->GetVsByte();
	ID3DBlob* pPsByteShader = pShader->GetPsByte();
	std::vector<D3D12_INPUT_ELEMENT_DESC>* pInputLayout = pShader->GetInputLayout();
	ID3D12RootSignature* pRootSign = pShader->GetRootSign();

	ZeroMemory(&psoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	psoDesc.InputLayout = { pInputLayout->data(), (UINT)pInputLayout->size()};
	psoDesc.pRootSignature = pRootSign;
	psoDesc.VS = { reinterpret_cast<BYTE*>(pVsByteShader->GetBufferPointer()), pVsByteShader->GetBufferSize() };

	psoDesc.PS = { reinterpret_cast<BYTE*>(pPsByteShader->GetBufferPointer()), pPsByteShader->GetBufferSize() };

	CD3DX12_BLEND_DESC blendDesc(D3D12_DEFAULT);
	if (pShader->GetAlpha() == true)
	{
		blendDesc.RenderTarget[0].BlendEnable = TRUE;
		blendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
	}
	else
	{
		blendDesc.RenderTarget[0].BlendEnable = FALSE;
		blendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
	}

	blendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	psoDesc.RasterizerState.CullMode = pShader->GetCullMode();
	psoDesc.BlendState = blendDesc;
	psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	psoDesc.SampleMask = UINT_MAX;
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.NumRenderTargets = 1;
	psoDesc.RTVFormats[0] = m_backBufferFormat;
	psoDesc.SampleDesc.Count = m_4xMsaaState ? 4 : 1;
	psoDesc.SampleDesc.Quality = m_4xMsaaState ? (m_4xMsaaQuality - 1) : 0;
	psoDesc.DSVFormat = m_depthStencilFormat;

	HRESULT hr = m_pDevice->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pPso));

	return hr;
}


bool Render::CreateDescHeap(D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors, D3D12_DESCRIPTOR_HEAP_FLAGS flag, ID3D12DescriptorHeap*& pDescriptorHeap)
{
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;
	rtvHeapDesc.NumDescriptors = numDescriptors;
	rtvHeapDesc.Type = type;
	rtvHeapDesc.Flags = flag;
	rtvHeapDesc.NodeMask = 0;
	HRESULT res = m_pDevice->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&pDescriptorHeap));
	return true;
}

void Render::CreateRenderTargetView()
{
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle(m_pRtvHeap->GetCPUDescriptorHandleForHeapStart());

	for (UINT i = 0; i < m_swapChainBufferCount; i++)
	{
		m_pSwapChain->GetBuffer(i, IID_PPV_ARGS(&m_pSwapChainBuffer[i]));
		m_pDevice->CreateRenderTargetView(m_pSwapChainBuffer[i], nullptr, rtvHeapHandle);
		rtvHeapHandle.Offset(1, m_rtvDescriptorSize);

		// Add Post Precessing ?
	}

}

HRESULT Render::CreateDepthStencilBufferAndView()
{
	return CreateDepthStencilBufferAndView(D3D12_RESOURCE_STATE_DEPTH_WRITE);
	
	// m_pPixelIdMappingDepthStencilBuffer ?
}

HRESULT Render::CreateDepthStencilBufferAndView(D3D12_RESOURCE_STATES resourceFlags)
{
	HRESULT res;

	D3D12_RESOURCE_DESC depthStencilDesc;
	depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthStencilDesc.Alignment = 0;
	depthStencilDesc.Width = m_renderWidth;
	depthStencilDesc.Height = m_renderHeight;		
	depthStencilDesc.DepthOrArraySize = 1;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.Format = m_depthStencilFormat;
	depthStencilDesc.SampleDesc.Count = m_4xMsaaState ? 4 : 1;
	depthStencilDesc.SampleDesc.Quality = m_4xMsaaState ? (m_4xMsaaQuality - 1) : 0;
	depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_CLEAR_VALUE optClear = {};
	optClear.Format = m_depthStencilFormat;
	optClear.DepthStencil.Depth = 1.0f;
	optClear.DepthStencil.Stencil = 0;

	CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_DEFAULT);
	
	res = m_pDevice->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &depthStencilDesc, resourceFlags, &optClear, IID_PPV_ARGS(&m_pDepthStencilBuffer));

	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
	dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	m_depthStencilBufferAddress = m_pDsvHeap->GetCPUDescriptorHandleForHeapStart();
	m_depthStencilBufferAddress.Offset(m_dsvOffsetCount, m_dsvDescriptorSize);

	m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, &dsvDesc, m_depthStencilBufferAddress);

	return res;
}

ID3D12Device* Render::GetDevice()
{
	return m_pDevice;
}

ID3D12GraphicsCommandList* const Render::GetCommandList()
{
	return m_pCommandList;
}

