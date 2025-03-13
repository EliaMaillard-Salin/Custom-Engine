#include "pch.h"

#include "Components/Component.h"
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
#include "Window.h"

namespace Engine {


GameObject::GameObject( Scene& scene ):
    m_pScene( &scene )
{
    transform.m_pOwner = this;
    if ( m_pScene->m_gameObjectsIDs.empty() )
    {
        m_id = m_pScene->m_gameObjectsIDs.size();
        m_pScene->m_gameObjects.push_back( this );
    }
    else
    {
        m_id = m_pScene->m_gameObjectsIDs.back();
        m_pScene->m_gameObjectsIDs.pop_back();
        m_pScene->m_gameObjects[m_id] = this;
    }
    m_pScene->m_gameObjectsToCreate.push_back( this );
}


void GameObject::Destroy()
{
    if ( m_toBeDeleted ) return;

    m_toBeDeleted = true;
    
    for ( GameObject* const pChild : m_children )
        pChild->Destroy();

    for ( auto const& [ tag, pComponent ] : m_components )
        pComponent->Destroy();

    GameManager::GetActiveScene().m_gameObjectsToDelete.push_back( this );
}


template <>
MeshRenderer& GameObject::AddComponent<MeshRenderer>()
{
    assert( ( HasComponent<MeshRenderer>() == false ) );
    
    MeshRenderer* const pMeshRenderer = new MeshRenderer();
    m_pScene->m_meshRenderers.push_back( pMeshRenderer );
    pMeshRenderer->m_pOwner = this;
    m_pScene->m_meshRenderersToCreate.push_back( pMeshRenderer );

    m_components[ MeshRenderer::Tag ] = pMeshRenderer;
    m_componentsBitmask |= 1 << ( MeshRenderer::Tag - 1 );

    return *pMeshRenderer;
}

template <>
SphereCollider& GameObject::AddComponent<SphereCollider>()
{
    assert( ( HasComponent<SphereCollider>() == false ) );
    
    SphereCollider* const pSphereCollider = new SphereCollider();
    m_pScene->m_sphereColliders.push_back( pSphereCollider );
    pSphereCollider->m_pOwner = this;
    m_pScene->m_sphereCollidersToCreate.push_back( pSphereCollider );

    m_components[ SphereCollider::Tag ] = pSphereCollider;
    m_componentsBitmask |= 1 << ( SphereCollider::Tag - 1 );

    return *pSphereCollider;
}

template <>
BoxCollider& GameObject::AddComponent<BoxCollider>()
{
    assert( ( HasComponent<BoxCollider>() == false ) );
    
    BoxCollider* const pBoxCollider = new BoxCollider();
    m_pScene->m_boxColliders.push_back( pBoxCollider );
    pBoxCollider->m_pOwner = this;
    m_pScene->m_boxCollidersToCreate.push_back( pBoxCollider );

    m_components[ BoxCollider::Tag ] = pBoxCollider;
    m_componentsBitmask |= 1 << ( BoxCollider::Tag - 1 );

    return *pBoxCollider;
}

template <>
RigidBody& GameObject::AddComponent<RigidBody>()
{
    assert((HasComponent<RigidBody>() == false));

    RigidBody* const pRigidBody = new RigidBody();
    m_pScene->m_rigidBodies.push_back( pRigidBody );
    pRigidBody->m_pOwner = this;
    m_pScene->m_rigidBodiesToCreate.push_back( pRigidBody );

    m_components[ RigidBody::Tag ] = pRigidBody;
    m_componentsBitmask |= 1 << ( RigidBody::Tag - 1 );

    return *pRigidBody;
}

template <>
CharacterController& GameObject::AddComponent<CharacterController>()
{
    assert( ( HasComponent<CharacterController>() == false ) );

    CharacterController* const pCharacterController = new CharacterController();
    m_pScene->m_characterControllers.push_back( pCharacterController );
    pCharacterController->m_pOwner = this;
    m_pScene->m_characterControllersToCreate.push_back( pCharacterController );

    m_components[ CharacterController::Tag ] = pCharacterController;
    m_componentsBitmask |= 1 << ( CharacterController::Tag - 1 );

    return *pCharacterController;
}

template <>
Camera& GameObject::AddComponent<Camera>()
{
    assert( ( HasComponent<Camera>() == false ) );

    Camera* const pCamera = new Camera();
    m_pScene->m_cameras.push_back( pCamera );
    pCamera->m_pOwner = this;
    m_pScene->m_camerasToCreate.push_back( pCamera );
    if ( m_pScene->m_pMainCamera == nullptr ) m_pScene->m_pMainCamera = pCamera->m_pOwner;

    m_components[ Camera::Tag ] = pCamera;
    m_componentsBitmask |= 1 << ( Camera::Tag - 1 );

    return *pCamera;
}

template <>
Light& GameObject::AddComponent<Light>()
{
    assert((HasComponent<Light>() == false));

    Light* const pLight = new Light();
    m_pScene->m_lights.push_back( pLight );
    pLight->m_pOwner = this;
    m_pScene->m_lightsToCreate.push_back( pLight );

    m_components[ Light::Tag ] = pLight;
    m_componentsBitmask |= 1 << ( Light::Tag - 1 );

    return *pLight;
}

template <>
void GameObject::RemoveComponent<MeshRenderer>()
{
    assert( HasComponent<MeshRenderer>() );
    m_components[ MeshRenderer::Tag ]->Destroy();
}

template <>
void GameObject::RemoveComponent<SphereCollider>()
{
    assert( HasComponent<SphereCollider>() );
    m_components[ SphereCollider::Tag ]->Destroy();
}

template <>
void GameObject::RemoveComponent<BoxCollider>()
{
    assert( HasComponent<BoxCollider>() );
    m_components[ BoxCollider::Tag ]->Destroy();
}

template <>
void GameObject::RemoveComponent<RigidBody>()
{
    assert( HasComponent<RigidBody>() );
    m_components[ RigidBody::Tag ]->Destroy();
}

template <>
void GameObject::RemoveComponent<CharacterController>()
{
    assert( HasComponent<CharacterController>() );
    m_components[ CharacterController::Tag ]->Destroy();
}

template <>
void GameObject::RemoveComponent<Camera>()
{
    assert( HasComponent<Camera>() );
    m_components[ Camera::Tag ]->Destroy();
}

template <>
void GameObject::RemoveComponent<Light>()
{
    assert( HasComponent<Light>() );
    m_components[ Light::Tag ]->Destroy();
}


bool GameObject::IsActive() const
{
    if ( m_pParent != nullptr ) return m_active && m_pParent->IsActive();
    return m_active && m_pScene->IsActive();
}


}