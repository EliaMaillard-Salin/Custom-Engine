#include "pch.h"
#include "Sprite.h"

#include "Geometry.h"
#include "Material.h"
#include "Mesh.h"
#include "Shader.h"
#include "PrimitiveFactory.h"

#include "Window.h"

#include "GameManager.h"

namespace Engine {


Sprite::Sprite( char const* path )
{
    Graphics& graphics = *GameManager::GetWindow().GetGraphics();
    
    m_pGeometry = graphics.CreateGeometryFromFile( path );
    
    int flag = 0;
    SET_FLAG( flag,VERTEX_COLOR );

    m_pShader = graphics.CreateShader( "../../res/Render/Color.hlsl", flag );

    m_pMesh = graphics.CreateMesh( m_pGeometry, flag );
    m_pMaterial = graphics.CreateMaterial( m_pShader );
}


}
