#ifndef ENGINE_RENDERSYSTEM_H_INCLUDED
#define ENGINE_RENDERSYSTEM_H_INCLUDED

#include <array>
#include <vector>

#include "define.h"

class Render;
class Graphics;
class Shader;

namespace Engine { struct MeshRenderer; }


namespace Engine { class RenderSystem; }
class Engine::RenderSystem
{
    RenderSystem() = default;
    ~RenderSystem() = default;

    void HandleRendering();

    void CreateBasicsShaders();

    Graphics* m_pGraphics = nullptr;
    Render* m_pRender = nullptr;

    std::array<std::vector<MeshRenderer const*>, RENDER_LAYER_COUNT> m_meshRenderers {}; // List of list of MeshRenderer Components based on their render layers. 


    std::vector<Shader*> m_basicShaders = std::vector<Shader*>(SHADER_AMMOUNT);

public:
    enum ShaderType : uint8
    {
        SHADER_COLOR,
        SHADER_LIGHTCOLOR,
        SHADER_TEXTURE,
        SHADER_AMMOUNT
    };

    Shader* GetShader(uint8 shaderType);

    friend class Scene;
    friend class GameManager;
};


#endif