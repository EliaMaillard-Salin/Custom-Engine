// #include <windows.h>
// #include "main.h"
// #include "Window.h"
// #include "Graphics.h"
// #include "Render.h"
// #include "Material.h"
// #include "PrimitiveFactory.h"
// #include "RenderUtils.h"
// // Link necessary DirectX libraries
// #pragma comment(lib, "d3d12.lib")
// #pragma comment(lib, "dxgi.lib")
// #pragma comment(lib, "d3dcompiler.lib")
// #pragma comment(lib, "d3d11.lib")
//
int main()
{
//     Window window = Window(hInstance);
//
//     Graphics* pGraphics = window.GetGraphics();
//
//     Geometry* pCube = pGraphics->CreateGeometryFromFile("../../res/Render/cubetest.obj", Vector<float32, 4>({ 1.f,0.f,1.f,1.f }));
//     Geometry* pCube2 = pGraphics->CreateGeometryFromFile("../../res/Render/cubetest.obj", Vector<float32, 4>({ 0.f,0.f,1.f,1.f }));
//
//     int flag = 0;
//     SET_FLAG(flag, VERTEX_COLOR);
//     Render* pRender = pGraphics->GetRender();
//     Shader* pShader = pGraphics->CreateShader("../../res/Render/Color.hlsl", flag);
//
//     Mesh* pMesh = pGraphics->CreateMesh(pCube, flag);
//     Mesh* pMesh1 = pGraphics->CreateMesh(pCube2, flag);
//
//     Material* pMaterial = pGraphics->CreateMaterial(pShader);
//     Material* pMaterial1 = pGraphics->CreateMaterial(pShader);
//
//     Matrix4x4 matrix = RenderUtils::XMMatrixToMatrix4x4(XMMatrixScaling(1, 1, 1) * XMMatrixTranslation(-10, 0, 0));
//     Matrix4x4 matrix1 = RenderUtils::XMMatrixToMatrix4x4(XMMatrixScaling(1, 1, 1) * XMMatrixTranslation(10, 0, 0));
//
//
//     Vector3f cameraUp(0, 1, 0);
//     Vector3f cameraPos(0, 0, -10);
//     Vector3f cameraTarget(0, 0, 0);
//
//     Matrix4x4 projMatrix;
//     Matrix4x4 viewMatrix;
//
//     pGraphics->UpdateCameraAt(cameraPos, cameraTarget, cameraUp, 1920.f, 1080.f, 0.25f * 3.1415, 1.f, 1000.f, projMatrix, viewMatrix);
//
//
//     while (window.IsOpen())
//     {
//         window.Update();
//
//
//
//
//
//
//
//         pGraphics->Clear(); // startFrame
//         pGraphics->UpdateViewProjConstantBuffer(projMatrix, viewMatrix);
//         //200 dessins
//
//         pGraphics->DrawObject(pMesh, pMaterial, matrix);
//         pGraphics->DrawObject(pMesh1, pMaterial1, matrix1);
//
//         pGraphics->Display(); // end frame
//
//     }
}