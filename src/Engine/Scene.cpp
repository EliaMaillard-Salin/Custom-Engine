#include "pch.h"
#include "Scene.h"

#include "Window.h"

#include "Scripts/Script.h"

#include "GameObject.h"

#include "GameManager.h"
#include "Systems/CollisionSystem.h"
#include "Systems/GameplaySystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/PhysicsSystem.h"

namespace Engine {


Scene& Scene::Create()
{
    std::vector<Scene>& scenes = GameManager::GetScenes();
    scenes.push_back( Scene() );
    return scenes.back();
}


void Scene::Load()
{
    if ( m_toBeLoaded || m_loaded ) return;

    m_toBeLoaded = true;

    GameManager::s_pInstance->m_scenesToLoad.push_back( this );
}

void Scene::Unload()
{
    if ( IsActive() || m_toBeUnloaded ) return;

    m_toBeUnloaded = true;

    for ( GameObject* const pGameObject : m_gameObjects )
        pGameObject->Destroy();
}

void Scene::SetActive()
{
    GameManager& gameManager = *GameManager::s_pInstance;
    if ( gameManager.m_pActiveScene == this || gameManager.m_pNextActiveScene == this ) return;
    if ( m_loaded == false ) { m_active = true; return; }
    // Maybe do it at the end of the frame
    gameManager.m_pNextActiveScene = this;
}


void Scene::HandleCreations()
{
    for ( GameObject* const pGameObject : m_gameObjectsToCreate )
    {
        // if ( pGameObject->m_toBeDeleted ) continue;

        pGameObject->m_toBeCreated = false;
        pGameObject->m_created = true;
    }
    m_gameObjectsToCreate.clear();

    for ( MeshRenderer* const pMeshRenderer : m_meshRenderersToCreate )
    {
        // if ( pMeshRenderer->m_toBeDeleted ) continue;
        
        pMeshRenderer->m_toBeCreated = false;
        pMeshRenderer->m_created = true;

        GameManager::GetRenderSystem().m_meshRenderers[pMeshRenderer->renderLayer].push_back( pMeshRenderer );
    }
    m_meshRenderersToCreate.clear();

    for ( SphereCollider* const pSphereCollider : m_sphereCollidersToCreate )
    {
        // if ( pSphereCollider->m_toBeDeleted ) continue;
        
        pSphereCollider->m_toBeCreated = false;
        pSphereCollider->m_created = true;

        GameManager::GetCollisionSystem().m_sphereColliders.push_back( pSphereCollider );
    }
    m_sphereCollidersToCreate.clear();

    for ( BoxCollider* const pBoxCollider : m_boxCollidersToCreate )
    {
        // if ( pBoxCollider->m_toBeDeleted ) continue;
        
        pBoxCollider->m_toBeCreated = false;
        pBoxCollider->m_created = true;

        GameManager::GetCollisionSystem().m_boxColliders.push_back( pBoxCollider );
    }
    m_boxCollidersToCreate.clear();

    for ( RigidBody* const pRigidBody : m_rigidBodiesToCreate )
    {
        // if ( pRigidBody->m_toBeDeleted ) continue;

        pRigidBody->m_toBeCreated = false;
        pRigidBody->m_created = true;

        GameManager::GetPhysicsSystem().m_pRigidBodys->push_back( pRigidBody );
        GameManager::GetPhysicsSystem().m_objectWithGravity.push_back( pRigidBody );
    }
    m_rigidBodiesToCreate.clear();

    for ( CharacterController* const pCharacterController : m_characterControllersToCreate )
    {
        // if ( pCharacterController->m_toBeDeleted ) continue;

        pCharacterController->m_toBeCreated = false;
        pCharacterController->m_created = true;

        GameManager::GetGameplaySystem().m_characterControllers.push_back( pCharacterController );
    }
    m_characterControllersToCreate.clear();

    for ( Camera* const pCamera : m_camerasToCreate )
    {
        // if ( pCamera->m_toBeDeleted ) continue;
        
        pCamera->m_toBeCreated = false;
        pCamera->m_created = true;
    }
    m_camerasToCreate.clear();

    for ( Light* const pLight : m_lightsToCreate )
    {
        // if ( pLight->m_toBeDeleted ) continue;

        pLight->m_toBeCreated = false;
        pLight->m_created = true;

        GameManager::GetWindow().GetGraphics()->AddLight( &pLight->lightCB );
    }
    m_lightsToCreate.clear();

}

void Scene::HandleDeletions()
{
    for ( uint16 i = 0; i < m_lights.size(); i++ )
    {
        Light* const pLight = m_lights[i];
        if ( pLight->m_toBeDeleted == false ) continue;

        m_lights.erase( m_lights.begin() + i );
        delete pLight;
    }

    for ( uint16 i = 0; i < m_cameras.size(); i++ )
    {
        Camera* const pCamera = m_cameras[i];
        if ( pCamera->m_toBeDeleted == false ) continue;

        m_cameras.erase( m_cameras.begin() + i );
        delete pCamera;
    }

    for ( uint16 i = 0; i < m_characterControllers.size(); i++ )
    {
        CharacterController* const pCharacterController = m_characterControllers[i];
        if ( pCharacterController->m_toBeDeleted == false ) continue;

        m_characterControllers.erase( m_characterControllers.begin() + i );
        delete pCharacterController;
    }

    for ( uint16 i = 0; i < m_rigidBodies.size(); i++ )
    {
        RigidBody* const pRigidBody = m_rigidBodies[i];
        if ( pRigidBody->m_toBeDeleted == false ) continue;

        m_rigidBodies.erase( m_rigidBodies.begin() + i );
        delete pRigidBody;
    }

    for ( uint16 i = 0; i < m_boxColliders.size(); i++ )
    {
        BoxCollider* const pBoxCollider = m_boxColliders[i];
        if ( pBoxCollider->m_toBeDeleted == false ) continue;

        m_boxColliders.erase( m_boxColliders.begin() + i );
        delete pBoxCollider;
    }

    for ( uint16 i = 0; i < m_sphereColliders.size(); i++ )
    {
        SphereCollider* const pSphereCollider = m_sphereColliders[i];
        if ( pSphereCollider->m_toBeDeleted == false ) continue;

        m_sphereColliders.erase( m_sphereColliders.begin() + i );
        delete pSphereCollider;
    }

    for ( uint16 i = 0; i < m_meshRenderers.size(); i++ )
    {
        MeshRenderer* const pMeshRenderer = m_meshRenderers[i];
        if ( pMeshRenderer->m_toBeDeleted == false ) continue;

        m_meshRenderers.erase( m_meshRenderers.begin() + i );
        delete pMeshRenderer;
    }
    
    for ( GameObject* const pGameObject : m_gameObjectsToDelete )
    {
        m_gameObjectsIDs.push_back( pGameObject->m_id );
        m_gameObjects.erase( m_gameObjects.begin() + pGameObject->m_id );
        delete pGameObject;
    }
    m_gameObjectsToDelete.clear();
}


void Scene::Update()
{
    for ( GameObject* const pGameObject : m_gameObjects )
    {
        if ( pGameObject->transform.m_dirty == false ) continue;
        pGameObject->transform.UpdateLocalMatrices();
        pGameObject->transform.UpdateWorldMatrices();
        pGameObject->transform.UpdateWorldMatrixFromMatrices();
    }
}


}
