#ifndef RENDER_RENDER_H_INCLUDED
#define RENDER_RENDER_H_INCLUDED
#include <list>
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <vector>
#include "d3dx12.h"
#include "define.h"
#include "BuffersStruct.h"
#include "Math/Matrix4x4.hpp"
#undef far
#undef near

class Window;
class Mesh;
class Material;
class Shader;
class Graphics;

class Render
{
    friend class Window;
    friend class Graphics;

    explicit Render( Window* pWindow, uint32 renderWidth = 1920, uint32 renderHeight = 1080 );
    ~Render();

    void InitRenderPipeline();   //book

    void CreateCommandObjects(); //book
    HRESULT CreateSwapChain();   //book

	void CreateRenderTargetView();
	HRESULT CreateDepthStencilBufferAndView();

	void UpdateViewPort();

    bool ResetCommandList();     //book
    void ExecuteCommandList();   //book
    void CloseCommandList();     //book

	bool FlushCommandQueue(bool isGpuIdle);    //book

	void Resize();
	void ReleasePreviousResources();
	void ResizeSwapChainBuffers();

    //Descriptor Heap Creation
    bool CreateDescHeap( D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors, D3D12_DESCRIPTOR_HEAP_FLAGS flag, ID3D12DescriptorHeap*& pDescriptorHeap );

    //Dsv Manager
	HRESULT CreateDepthStencilBufferAndView( D3D12_RESOURCE_STATES resourceFlags );

    bool PrepareDraw();
    bool DrawObject(Mesh* pMesh, Material* pMaterial, Matrix4x4 const& ObjworldMatrix);
    bool CompleteDraw();

public:
    ID3D12Device* GetDevice();

    ID3D12GraphicsCommandList* const GetCommandList();

    // Create PSO_DESC
    HRESULT CreatePsoDesc(Shader* pShader, ID3D12PipelineState*& pPso);

    ID3D12DescriptorHeap* GetCbvSrvUavDescriptorHeap();

private:
    void UpdateLights();
private:
    Window* m_pWindow = nullptr;
    uint16 m_renderWidth = 1920;
    uint16 m_renderHeight = 1080;

    static const uint32 m_swapChainBufferCount = 2;

    // Scene properties
    UploadBuffer<CameraCB>* m_pCbCurrentViewProjInstance;

    UploadBuffer<LightCB>* m_pCbCurrentLightInstance;
    std::vector<LightCB> m_lightSources;

    //Fence
    ID3D12Fence* m_pFence = nullptr;
    uint64 m_currentFence = 0;

    //Debug Controller
    ID3D12Debug* m_pDebugController = nullptr;

    // DirectX12 3D Instances
    IDXGIFactory4* m_pFactory = nullptr;
    ID3D12Device* m_pDevice = nullptr;
	
    ID3D12GraphicsCommandList* m_pCommandList = nullptr;
    ID3D12CommandQueue* m_pCommandQueue = nullptr;
    ID3D12CommandAllocator* m_pDirectCmdListAlloc = nullptr;

    IDXGISwapChain3* m_pSwapChain = nullptr;
    ID3D12Resource* m_pSwapChainBuffer[m_swapChainBufferCount] {};

    ID3D12Resource* m_pDepthStencilBuffer = nullptr;
    CD3DX12_CPU_DESCRIPTOR_HANDLE m_depthStencilBufferAddress;

    //Descriptor heaps
    ID3D12DescriptorHeap* m_pRtvHeap = nullptr;
    ID3D12DescriptorHeap* m_pDsvHeap = nullptr;
    ID3D12DescriptorHeap* m_pCbvSrvUavDescriptorHeap = nullptr;

    //Descriptors size
    uint32 m_rtvDescriptorSize = 0;
    uint32 m_dsvDescriptorSize = 0;
    uint32 m_cbvSrvUavDescriptorSize = 0;

    //State var
    bool m_canResize = true;
    uint32 m_currBackBuffer = 0;

    //Format
    DXGI_FORMAT m_depthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT; 
    DXGI_FORMAT m_backBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
    DXGI_FORMAT m_rgbaFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

    //Msaa
    bool m_4xMsaaState = false; // 4X MSAA enabled
    uint32 m_4xMsaaQuality = 0; // quality level of 4X MSAA

    //Screen
    D3D12_VIEWPORT m_screenViewport {};
    D3D12_RECT m_scissorRect {};

    CD3DX12_STATIC_SAMPLER_DESC m_staticSample;

    //Rtv Manager
    uint32 m_rtvOffsetCount = 2;
    std::list<ID3D12Resource*> m_lRenderTargets;

    //Srv Manager
    uint32 m_srvStaticOffsetCount = 300;
    uint32 m_srvDynamicOffsetCount = 320;
    std::list<CD3DX12_GPU_DESCRIPTOR_HANDLE> m_lShaderResourceView;

    //Uav Manager
    uint32 m_uavOffsetCount = 400;
    std::list<CD3DX12_CPU_DESCRIPTOR_HANDLE> m_lUnorderedAccessView;

    //Dsv Manager
    uint32 m_dsvOffsetCount = 0;
    std::list<ID3D12Resource*> m_lDepthStencilView;

    std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> m_rtvs;
    std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> m_dsvs;

    UINT m_rtvCount;
};


#endif