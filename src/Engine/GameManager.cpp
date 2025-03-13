#include "pch.h"
#include "GameManager.h"

#include <windows.h>

#include "Keyboard.h"
#include "Mouse.h"
#include "Timer.h"
#include "Window.h"


#include "Systems/InputSystem.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/GameplaySystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/ScriptSystem.h"
#include "Systems/RenderSystem.h"

namespace Engine {


GameManager::GameManager( HINSTANCE const hInstance ):
    m_pTimer( new Timer() ),
    m_pWindow( new Window( hInstance, 1920, 1080, "NewGCEngine" ) ),
    m_pInputSystem( new InputSystem() ),
    m_pPhysicsSystem( new PhysicsSystem() ),
    m_pGameplaySystem( new GameplaySystem() ),
    m_pCollisionSystem( new CollisionSystem() ),
    m_pScriptSystem( new ScriptSystem() ),
    m_pRenderSystem( new RenderSystem() )
{
    m_pRenderSystem->m_pGraphics = m_pWindow->GetGraphics();
    m_pRenderSystem->CreateBasicsShaders();
    m_pRenderSystem->m_pRender = m_pWindow->GetGraphics()->GetRender();
}

GameManager::~GameManager()
{
    delete m_pTimer;
    delete m_pWindow;
    delete m_pInputSystem;
    delete m_pPhysicsSystem;
    delete m_pGameplaySystem;
    delete m_pCollisionSystem;
    delete m_pScriptSystem;
    delete m_pRenderSystem;
}


void GameManager::GameLoop()
{
    m_pGameplaySystem->Init();

    m_pTimer->Reset();
    while ( m_pWindow->IsOpen() )
    {
        // System
        m_pWindow->Update();
        m_pTimer->Tick();
        //m_elapsedTime += m_pTimer->GetDeltaTime();
        m_elapsedTime += m_fixedDeltaTime;

        // Creations / Deletions
        HandleCreations();
        HandleDeletions();

        // Inputs
        m_pInputSystem->Update();  

        // Systems
        while ( m_elapsedTime >= m_fixedDeltaTime )
        {
            m_pPhysicsSystem->HandlePhysics();
            m_pGameplaySystem->HandleCharacterControllers();
            m_pCollisionSystem->HandleCollisions();
            m_elapsedTime -= m_fixedDeltaTime;
        }

        m_pGameplaySystem->HandleShooting();

        // Scripts
        m_pScriptSystem->FixedUpdateScripts();
        m_pScriptSystem->UpdateScripts();
        m_pScriptSystem->LateUpdateScripts();

        // Updates
        m_pActiveScene->Update();

        // Rendering
        m_pRenderSystem->HandleRendering();
    }
}


void GameManager::HandleCreations()
{
    for ( Scene* const pScene : m_scenesToLoad )
    {
        if ( pScene->m_toBeUnloaded ) continue;

        pScene->m_toBeLoaded = false;
        pScene->m_loaded = true;
        m_loadedScenes.push_back( pScene );
        if ( pScene->m_active ) m_pNextActiveScene = pScene;
    }
    m_scenesToLoad.clear();

    for ( Scene* const pScene : m_loadedScenes )
        pScene->HandleCreations();

    if ( m_pNextActiveScene != nullptr )
    {
        m_pActiveScene = m_pNextActiveScene;
        m_pNextActiveScene = nullptr;
    }
}

void GameManager::HandleDeletions()
{
    for ( Scene* const pScene : m_loadedScenes )
        pScene->HandleDeletions();

    for ( uint8 i = 0; i < m_loadedScenes.size(); i++ )
    {
        Scene& scene = *m_loadedScenes[i];
        if ( scene.m_toBeUnloaded == false ) continue;

        if ( scene.m_toBeLoaded )
        {
            scene.m_toBeLoaded = false;
            scene.m_toBeUnloaded = false;
            continue;
        }

        scene.m_toBeUnloaded = false;
        scene.m_loaded = false;
        scene.m_gameObjects.clear();
        m_loadedScenes.erase( m_loadedScenes.begin() + i-- );
    }
}


}