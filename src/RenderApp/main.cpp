#include <windows.h>
// #include "main.h"
// #include "Window.h"
// #include "Graphics.h"
// #include "Render.h"
// #include "Material.h"
// #include "PrimitiveFactory.h"
// #include "RenderUtils.h"
// #include "BuffersStruct.h"
//
// // Link necessary DirectX libraries
// #pragma comment(lib, "d3d12.lib")
// #pragma comment(lib, "dxgi.lib")
// #pragma comment(lib, "d3dcompiler.lib")
// #pragma comment(lib, "d3d11.lib")
//
//
// using namespace DirectX;
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow)
{
//     Window window = Window(hInstance);
//
//     Graphics* pGraphics = window.GetGraphics();
//
//     //Geometry* pCube = pGraphics->CreateGeometryFromFile("../../res/Render/cubetest.obj");
//     Geometry* pCube = new Geometry(pGraphics->CreatePrimitiveGeometry(CUBE));
//
//     int flag = 0;
//     SET_FLAG( flag,VERTEX_UV);
//
//     int flag1 = 0;
//     SET_FLAG(flag1, VERTEX_COLOR);
//     Render* pRender = pGraphics->GetRender();
//
//     int flag2 = 0;
//     SET_FLAG(flag2, VERTEX_COLOR);
//     SET_FLAG(flag2, VERTEX_NORMAL);
//
//     Shader* pShader1 = pGraphics->CreateShader("../../res/Render/Color.hlsl", flag1);
//     Mesh* pMesh1 = pGraphics->CreateMesh(pCube, flag1);
//     Material* pMaterial1 = pGraphics->CreateMaterial(pShader1);
//
//     Shader* pShader2 = pGraphics->CreateShader("../../res/Render/LightColor.hlsl", flag2);
//     Mesh* pMesh2 = pGraphics->CreateMesh(pCube, flag2);
//     Material* pMaterial2 = pGraphics->CreateMaterial(pShader2);
//
//     Shader* pShader = pGraphics->CreateShader("../../res/Render/texture.hlsl", flag);
//     Mesh* pMesh = pGraphics->CreateMesh(pCube, flag);
//
//     Material* pMaterial = pGraphics->CreateMaterial(pShader);
//     
//     Matrix4x4 matrix = RenderUtils::XMMatrixToMatrix4x4( XMMatrixScaling(1, 1, 1) * XMMatrixTranslation(0, 0, 0) );
//     Matrix4x4 matrix1 = RenderUtils::XMMatrixToMatrix4x4( XMMatrixScaling(1, 1, 1) * XMMatrixTranslation(10, 0, 0) );
//
//     Light directionalLight = {};
//     directionalLight.color = { 1.0f, 1.0f, 1.0f };       // White light
//     directionalLight.type = LIGHT_TYPE_DIRECTIONAL;      // 0 = Directional light
//     directionalLight.direction = { 0.0f, -1.0f, 0.0f };  // Light coming from above, along negative Y
//     directionalLight.intensity = 1.0f;                   // Full intensity
//     directionalLight.Position = { 0.0f, 0.0f, 0.0f };    // Not used, can be zero
//     directionalLight.spotAngle = 0.0f;                  // Not used
//
//     Light pointLight = {};
//     pointLight.color = { 1.0f, 1.0f, 1.0f };           // Red light
//     pointLight.type = LIGHT_TYPE_POINT;                               // 1 = Point light
//     pointLight.Position = { 0.5f, 0.25f, 1.5f };        // 1 unit above the sphere
//     pointLight.intensity = 1.0f;                       // Full intensity
//     pointLight.direction = { 0.0f, 0.0f, 0.0f };       // Not used
//     pointLight.spotAngle = 0.0f;                       // Not used
//
//     Light spotLight = {};
//     spotLight.color = { 1.0f, 1.0f, 1.0f };            // Green light
//     spotLight.type = LIGHT_TYPE_SPOT;                                // 2 = Spot light
//     spotLight.Position = { 0.0f, 2.0f, 0.0f };         // 2 units above the sphere
//     spotLight.direction = { 0.0f, -1.0f, 0.0f };       // Pointing downward at the sphere
//     spotLight.intensity = 0.5f;                        // Full intensity
//     spotLight.spotAngle = 45.0f;                       // 45-degree cone
//
//     //pGraphics->AddLight(&directionalLight);
//     pGraphics->AddLight(&pointLight);
//     //pGraphics->AddLight(&spotLight);
//
//     Vector3f cameraUp(0,1,0);
//     Vector3f cameraPos(10, 0, 10);
//     Vector3f cameraTarget(0, 0, 0);
//
//     Matrix4x4 proj;
//     Matrix4x4 view;
//     pGraphics->UpdateCameraAt(cameraPos, cameraTarget, cameraUp, 1920.0f, 1080.0f, 0.25f * 3.1415, 1.0f, 1000.0f, proj, view);
//
//     while ( window.IsOpen() )
//     {
//         window.Update();
//
//
//         pGraphics->Clear(); // startFrame
//         //200 dessins
//         pGraphics->UpdateCamera(proj, view);
//         
//         pGraphics->DrawObject(pMesh2, pMaterial2, matrix);
//         //pRender->DrawObject(pMesh1, pMaterial, matrix1);
//     
//         pGraphics->Display();
//
//     }

     return 0;
}