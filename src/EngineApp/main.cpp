#include <Windows.h>

#include "define.h"

#include "Sprite.h"
#include "RenderDefine.h"

#include "Components/MeshRenderer.h"
#include "Components/SphereCollider.h"
#include "Components/BoxCollider.h"
#include "Components/RigidBody.h"
#include "Components/CharacterController.h"
#include "Components/Camera.h"
#include "Components/Light.h"

#include "GameObject.h"
#include "Scene.h"

#include "GameManager.h"

using Engine::Sprite;

using Engine::MeshRenderer;
using Engine::SphereCollider;
using Engine::BoxCollider;
using Engine::RigidBody;
using Engine::CharacterController;
using Engine::Camera;
using Engine::Light;

using Engine::GameObject;
using Engine::Scene;

using Engine::GameManager;


int WinMain( HINSTANCE const hInstance, HINSTANCE hPrevInstance, PSTR const cmdLine, int const cmdShow )
{
    int flag = 0;
    SET_FLAG(flag, VERTEX_COLOR);
    SET_FLAG(flag, VERTEX_NORMAL);

    GameManager::Init( hInstance );

    Scene& scene = Scene::Create();
    scene.Load();
    scene.SetActive();
    
    GameObject* const pMainCamera = new GameObject( scene );
    pMainCamera->transform.Translate( Vector3f{ 0.0f, 0.0f, -100'000.0f } );
    Camera& cameraComponent = pMainCamera->AddComponent<Camera>();
    CharacterController& characterController = pMainCamera->AddComponent<CharacterController>();
    characterController.speed = 3'000.0f;
    characterController.sprintSpeed = 20'000.0f;

    Shader* pShaderPlanet = MeshRenderer::CreateShader("../../res/Render/Planet.hlsl", flag);
    Shader* pShaderStar = MeshRenderer::CreateShader("../../res/Render/Star.hlsl", VERTEX_COLOR,2);

    GameObject* const pWorld = new GameObject(scene);
    pWorld->transform.SetScale(Vector3f(10000000.0f, 10000000.0f, 10000000.0f));
    MeshRenderer& meshWorld = pWorld->AddComponent<MeshRenderer>();
    meshWorld.SetSphere(pShaderStar, VERTEX_COLOR, Vector<float32, 4>({ 1.0f,1.0f,1.0f,1.0f }));

    GameObject* const pSun = new GameObject( scene );
    pSun->transform.SetScale(Vector3f(10000, 10000, 10000));
    MeshRenderer& meshRendererSun = pSun->AddComponent<MeshRenderer>();
    meshRendererSun.SetCustomObject("../../res/Render/SUN.obj", "../../res/Render/SunImage.dds");
    meshRendererSun.SetMaterialProperties(Vector<float32, 4>({ 1.0f,1.0f,1.0f,1.0f }), Vector<float32, 4>({ 1.0f,1.0f,1.0f,1.0f }), Vector<float32, 4>({ 1.0f,1.0f,1.0f,1.0f }), Vector<float32, 4>({ 0.8f,0.8f,0.8,1.0f }), 10.0f);
    RigidBody& rigidBodySun = pSun->AddComponent<RigidBody>();
    Light& sunLight = pSun->AddComponent<Light>();
    pSun->AddComponent<SphereCollider>();

    GameObject* const pMercury = new GameObject( scene );
    pMercury->transform.SetScale(Vector3f(550, 550, 550));
    MeshRenderer& meshRendererMercury = pMercury->AddComponent<MeshRenderer>();
    meshRendererMercury.SetSphere(pShaderPlanet, flag, Vector<float32, 4>({ 1.0f,0.0f,0.0f,1.0f }));
    RigidBody& rigidBodyMercury = pMercury->AddComponent<RigidBody>();
    pMercury->AddComponent<SphereCollider>();

    GameObject* const pVenus = new GameObject( scene );
    pVenus->transform.SetScale(Vector3f(600, 600, 600));
    MeshRenderer& meshRendererVenus = pVenus->AddComponent<MeshRenderer>();
    meshRendererVenus.SetSphere(pShaderPlanet, flag, Vector<float32, 4>({ 1.0f,0.5f,0.0f,1.0f }));
    RigidBody& rigidBodyVenus = pVenus->AddComponent<RigidBody>();
    pVenus->AddComponent<SphereCollider>();

    GameObject* const pEarth = new GameObject( scene );
    pEarth->transform.SetScale(Vector3f(700, 700, 700));
    MeshRenderer& meshRendererEarth = pEarth->AddComponent<MeshRenderer>();
    meshRendererEarth.SetSphere(pShaderPlanet, flag, Vector<float32, 4>({ 0.0f,0.0f,1.0f,1.0f }));
    RigidBody& rigidBodyEarth = pEarth->AddComponent<RigidBody>();
    pEarth->AddComponent<SphereCollider>();

    GameObject* const pMoon = new GameObject( scene );
    pMoon->transform.SetScale(Vector3f(250, 250, 250));
    MeshRenderer& meshRendererMoon = pMoon->AddComponent<MeshRenderer>();
    meshRendererMoon.SetSphere(pShaderPlanet, flag, Vector<float32, 4>({ 0.8f,0.8f,0.8f,1.0f }));
    RigidBody& rigidBodyMoon = pMoon->AddComponent<RigidBody>();
    pMoon->AddComponent<SphereCollider>();

    pSun->transform.SetPosition(Vector3f({ 0.0f, 0.0f, 0.0f }));
    //pMoon->transform.SetPosition(Vector3f({ 0.0f, 61'640.0f, 0.0f }));
    //pEarth->transform.SetPosition(Vector3f({ 0.0f, 61'000.0f, 0.0f }));
    pMercury->transform.SetPosition(Vector3f({ 0.0f, -10'000.0f,0.0f }));
    pVenus->transform.SetPosition(Vector3f({ -20'000.0f, 0.0f,0.0f }));


    rigidBodySun.centerOfMass = Vector3f({ 0.0f, 0.0f, 0.0f });
    //rigidBodyMoon.centerOfMass = Vector3f({ 0.0f, 61'640.0f, 0.0f });
    //rigidBodyEarth.centerOfMass = Vector3f({ 0.0f, 61'000.0f, 0.0f });
    rigidBodyMercury.centerOfMass = Vector3f({ 0.0f, -10'000.0f,0.0f });
    rigidBodyVenus.centerOfMass = Vector3f({ -20'000.0f, 0.0f,0.0f });


    pMoon->transform.SetPosition(Vector3f({ 0.0f, 51'000.0f, 0.0f }));
    pEarth->transform.SetPosition(Vector3f({ 0.0f, 50'000.0f, 0.0f }));
    
    rigidBodyMoon.centerOfMass = Vector3f({ 0.0f, 51'000.0f, 0.0f });
    rigidBodyEarth.centerOfMass = Vector3f({ 0.0f, 50'000.0f, 0.0f });

    //rigidBodySun.mass = 2'000'000'000'000'000.0f;
    //rigidBodyEarth.mass = 600'000'000'000'0.0f;
    //rigidBodyMoon.mass = 310'00;
    //rigidBodyMercury.mass = 400'000'000.0f;
    //rigidBodyVenus.mass = 400'000'000'00.0f;

    //rigidBodyMoon.velocity = Vector3f(415.0f, 0.0f, 0.0f);
    //rigidBodyEarth.velocity = Vector3f(400.0f, 0.0f, 0.f);
    //rigidBodyMercury.velocity = Vector3f(420.0f, 0.0f, 0.0f);
    //rigidBodyVenus.velocity = Vector3f(0.0f, -400.0f, 0.0f);
    rigidBodySun.takesGravity = false;

    rigidBodySun.mass = 2'000'000'000'000'000.0f;
    rigidBodyEarth.mass = 600'000'000'000'00.0f;
    rigidBodyMoon.mass = 31'00;
    rigidBodyMercury.mass = 400'000'00.0f;
    rigidBodyVenus.mass = 400'000'000'00.0f;

    rigidBodyMoon.velocity = Vector3f(3500.0f, 0.0f, 0.0f);
    rigidBodyEarth.velocity = Vector3f(3000.0f, 0.0f, 0.f);
    rigidBodyMercury.velocity = Vector3f(3000.0f, 0.0f, 0.0f);
    rigidBodyVenus.velocity = Vector3f(0.0f, -3000.0f, 0.0f);


    sunLight.SetColor(Vector3f({ 1.0f,1.0f,1.0f }));
    sunLight.SetType(LIGHT_TYPE_POINT);
    sunLight.SetPosition(Vector3f({ 0.0f,0.0f,0.0f }));
    sunLight.SetIntensity(20.0f);
    sunLight.SetDirection(Vector3f({ 0.0f,0.0f,0.0f }));
    sunLight.SetSpotAngle(0.0f);

    characterController.followObject = pEarth;

    GameManager::Run();

    GameManager::Release();

    for (uint8 i = 0; i < 0b10000000; i++);
    return 0;
}