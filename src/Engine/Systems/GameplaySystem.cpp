#include "pch.h"
#include "GameplaySystem.h"

#include "Mouse.h"
#include "Keyboard.h"
#include "Window.h"

#include "Components/MeshRenderer.h"
#include "Components/CharacterController.h"

#include "GameObject.h"

#include "GameManager.h"

namespace Engine {


GameplaySystem::GameplaySystem():
    m_pBulletTemplate( new MeshRenderer() )
{}


void GameplaySystem::Init()
{
    m_pBulletTemplate->SetSphere();
}


void GameplaySystem::HandleCharacterControllers()
{
    for ( CharacterController* const pCharacterController : m_characterControllers )
    {
        if ( pCharacterController->IsActive() == false ) continue;

        GameObject& owner = *pCharacterController->m_pOwner;

        // Keyboard Movement

        if ( Keyboard::GetKeyDown( pCharacterController->keys.switchView ) )
            pCharacterController->isFollowing ^= true;

        if ( pCharacterController->isFollowing == false )
        {
            Vector3f movement;

            if ( Keyboard::GetKey( pCharacterController->keys.left ) )     movement -= owner.transform.GetRight();
            if ( Keyboard::GetKey( pCharacterController->keys.right ) )    movement += owner.transform.GetRight();
            if ( Keyboard::GetKey( pCharacterController->keys.forward ) )  movement += owner.transform.GetForward();
            if ( Keyboard::GetKey( pCharacterController->keys.backward ) ) movement -= owner.transform.GetForward();
            if ( Keyboard::GetKey( pCharacterController->keys.up ) )       movement += owner.transform.GetUp();
            if ( Keyboard::GetKey( pCharacterController->keys.down ) )     movement -= owner.transform.GetUp();
        
            movement *= Keyboard::GetKey( pCharacterController->keys.sprint ) ? pCharacterController->sprintSpeed : pCharacterController->speed;
            movement *= GameManager::GetFixedDeltaTime();

            owner.transform.Translate( movement );
        }
        else if ( pCharacterController->followObject != nullptr ) owner.transform.SetPosition( pCharacterController->followObject->transform.GetPosition() );

        // Mouse Movement

        if ( Mouse::GetButton( Mouse::Right ) == false ) continue;

        POINT screenCenter( GameManager::GetWindow().GetWidth() * 0.5f, GameManager::GetWindow().GetHeight() * 0.5f );

        POINT mousePosition;
        GetCursorPos( &mousePosition );
        ScreenToClient( GameManager::GetWindow().GetHWND(), &mousePosition );

        if ( Mouse::GetButtonDown( Mouse::Right ) == false )
        {
            float32 xMovement = screenCenter.x - mousePosition.x;
            float32 yMovement = mousePosition.y - screenCenter.y;

            // float32 const deltaTime = GameManager::GetTimer().GetDeltaTime();
            float32 const deltaTime = GameManager::GetFixedDeltaTime();
            xMovement *= pCharacterController->sensitivity * deltaTime;
            yMovement *= pCharacterController->sensitivity * deltaTime;

            owner.transform.Rotate( xMovement, 0.0f, yMovement );
        }

        ClientToScreen( GameManager::GetWindow().GetHWND(), &screenCenter );
        SetCursorPos( screenCenter.x, screenCenter.y );
        
    }
}

void GameplaySystem::HandleShooting()
{
    Vector2f mousePos = InputSystem::GetMousePos();
    mousePos.x -= GameManager::GetWindow().GetWidth() * 0.5f;
    mousePos.y -= GameManager::GetWindow().GetHeight() * 0.5f;

    // GameManager::GetActiveScene().GetMainCamera()->transform.Rotate( Quaternion( mousePos.y,mousePos.x,0.0f,0.0f ) );

    if ( Mouse::GetButtonDown( Mouse::Button::Left ) )
        if ( m_elapsedTime >= m_shootingRate )
            Shoot();
}


void GameplaySystem::Shoot()
{
    GameObject* const pNewBullet = new GameObject( GameManager::GetActiveScene() );
    MeshRenderer& meshrendererBullet = pNewBullet->AddComponent<MeshRenderer>();
    SphereCollider& sphereColliderBullet = pNewBullet->AddComponent<SphereCollider>();
    RigidBody& rigidbodyBullet = pNewBullet->AddComponent<RigidBody>();

    m_pBulletTemplate->Duplicate( &meshrendererBullet );

    Vector3f bulletStartPos;
    bulletStartPos = GameManager::GetActiveScene().GetMainCamera()->transform.GetPosition();

    pNewBullet->transform.SetPosition( bulletStartPos );
    pNewBullet->transform.SetScale( Vector3f( 0.5f,0.5f,4.0f ) );

    rigidbodyBullet.ApplyForces( GameManager::GetActiveScene().GetMainCamera()->transform.GetForward() * 100.0f );
    rigidbodyBullet.centerOfMass = pNewBullet->transform.GetPosition();
}


}