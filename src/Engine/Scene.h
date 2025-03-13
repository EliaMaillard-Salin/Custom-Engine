#ifndef ENGINE_SCENE_H_INCLUDED
#define ENGINE_SCENE_H_INCLUDED

#include <vector>
#include "define.h"

#include "Components/MeshRenderer.h"
#include "Components/SphereCollider.h"
#include "Components/BoxCollider.h"
#include "Components/RigidBody.h"
#include "Components/CharacterController.h"
#include "Components/Camera.h"
#include "Components/Light.h"

namespace Engine { class Script; }

namespace Engine { class GameObject; }


namespace Engine { class Scene; }
class Engine::Scene
{
public:
    Scene() = default;
    ~Scene() = default;

    [[nodiscard]] static Scene& Create();
    void Load();
    void Unload();
    void SetActive();
    
    [[nodiscard]] bool IsActive() const;
    [[nodiscard]] bool IsLoaded() const;

    [[nodiscard]] GameObject const* GetMainCamera() const;

    [[nodiscard]] std::vector<GameObject*> const& GetGameObjects() const;
    [[nodiscard]] std::vector<MeshRenderer*> const& GetMeshRenderers() const;
    [[nodiscard]] std::vector<SphereCollider*> const& GetSphereColliders() const;
    [[nodiscard]] std::vector<BoxCollider*> const& GetBoxColliders() const;
    [[nodiscard]] std::vector<RigidBody*> const& GetRigidBodies() const;
    [[nodiscard]] std::vector<CharacterController*> const& GetCharacterControllers() const;
    [[nodiscard]] std::vector<Camera*> const& GetCameras() const;
    [[nodiscard]] std::vector<Light*> const& GetLight() const;

    [[nodiscard]] GameObject* GetMainCamera();

    [[nodiscard]] std::vector<GameObject*>& GetGameObjects();
    [[nodiscard]] std::vector<MeshRenderer*>& GetMeshRenderers();
    [[nodiscard]] std::vector<SphereCollider*>& GetSphereColliders();
    [[nodiscard]] std::vector<BoxCollider*>& GetBoxColliders();
    [[nodiscard]] std::vector<RigidBody*>& GetRigidBodies();
    [[nodiscard]] std::vector<CharacterController*>& GetCharacterControllers();
    [[nodiscard]] std::vector<Camera*>& GetCameras();
    [[nodiscard]] std::vector<Light*>& GetLight();

    void HandleCreations();
    void HandleDeletions();

private:
    void Update();
    
    // State
    bool m_active       = false; // Whether the Scene is the active one
    bool m_loaded       = false; // Whether the Scene was loaded
    bool m_toBeLoaded   = false; // Whether the Scene was queued to be loaded
    bool m_toBeUnloaded = false; // Whether the Scene was queued to be unloaded

    // Elements in the Scene
    GameObject* m_pMainCamera = nullptr;

    std::vector<GameObject*>          m_gameObjects;          // Vector of GameObjects in the Scene
    std::vector<uint32>               m_gameObjectsIDs;       // Vector of available GameObjects IDs in the Scene
    std::vector<MeshRenderer*>        m_meshRenderers;        // Vector of MeshRenderers in the Scene
    std::vector<SphereCollider*>      m_sphereColliders;      // Vector of SphereColliders in the Scene
    std::vector<BoxCollider*>         m_boxColliders;         // Vector of BoxColliders in the Scene
    std::vector<RigidBody*>           m_rigidBodies;          // Vector of RigidBodies in the Scene
    std::vector<CharacterController*> m_characterControllers; // Vector of CharacterControllers in the Scene
    std::vector<Camera*>              m_cameras;              // Vector of Cameras in the Scene
    std::vector<Light*>               m_lights;               // Vector of Light in the Scene
    std::vector<Script*>              m_scripts;              // Vector of Scripts in the Scene

    // Creations
    std::vector<GameObject*>          m_gameObjectsToCreate;          // Vector of GameObjects to be created
    std::vector<MeshRenderer*>        m_meshRenderersToCreate;        // Vector of MeshRenderers to be created
    std::vector<SphereCollider*>      m_sphereCollidersToCreate;      // Vector of SphereColliders to be created
    std::vector<BoxCollider*>         m_boxCollidersToCreate;         // Vector of BoxColliders to be created
    std::vector<RigidBody*>           m_rigidBodiesToCreate;          // Vector of RigidBodies to be created
    std::vector<CharacterController*> m_characterControllersToCreate; // Vector of CharacterControllers to be created
    std::vector<Camera*>              m_camerasToCreate;              // Vector of Cameras to be created
    std::vector<Light*>               m_lightsToCreate;               // Vector of Light to be created

    // Deletions
    std::vector<GameObject*> m_gameObjectsToDelete; // Vector of GameObjects to be deleted

    friend struct MeshRenderer;
    friend struct SphereCollider;
    friend struct BoxCollider;
    friend struct RigidBody;
    friend struct CharacterController;
    friend struct Camera;
    friend struct Light;
    friend class GameObject;
    friend class GameManager;
};


#include "Scene.inl"

#endif