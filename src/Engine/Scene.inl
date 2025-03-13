#ifndef ENGINE_SCENE_INL_INCLUDED
#define ENGINE_SCENE_INL_INCLUDED

namespace Engine {


inline bool Scene::IsActive() const { return m_active; }
inline bool Scene::IsLoaded() const { return m_loaded; }


inline GameObject const* Scene::GetMainCamera() const { return m_pMainCamera; }

inline std::vector<GameObject*> const& Scene::GetGameObjects() const { return m_gameObjects; }
inline std::vector<MeshRenderer*> const& Scene::GetMeshRenderers() const { return m_meshRenderers; }
inline std::vector<SphereCollider*> const& Scene::GetSphereColliders() const { return m_sphereColliders; }
inline std::vector<BoxCollider*> const& Scene::GetBoxColliders() const { return m_boxColliders; }
inline std::vector<RigidBody*> const& Scene::GetRigidBodies() const { return m_rigidBodies; }
inline std::vector<CharacterController*> const& Scene::GetCharacterControllers() const { return m_characterControllers; }
inline std::vector<Camera*> const& Scene::GetCameras() const { return m_cameras; }
inline std::vector<Light*> const& Scene::GetLight() const { return m_lights; }


inline GameObject* Scene::GetMainCamera() { return m_pMainCamera; }

inline std::vector<GameObject*>& Scene::GetGameObjects() { return m_gameObjects; }
inline std::vector<MeshRenderer*>& Scene::GetMeshRenderers() { return m_meshRenderers; }
inline std::vector<SphereCollider*>& Scene::GetSphereColliders() { return m_sphereColliders; }
inline std::vector<BoxCollider*>& Scene::GetBoxColliders() { return m_boxColliders; }
inline std::vector<RigidBody*>& Scene::GetRigidBodies() { return m_rigidBodies; }
inline std::vector<CharacterController*>& Scene::GetCharacterControllers() { return m_characterControllers; }
inline std::vector<Camera*>& Scene::GetCameras() { return m_cameras; }
inline std::vector<Light*>& Scene::GetLight() { return m_lights; }


}

#endif
