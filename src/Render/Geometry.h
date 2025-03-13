#ifndef RENDER_GEOMETRY_H_INCLUDED
#define RENDER_GEOMETRY_H_INCLUDED
#include <DirectXMath.h>
#include <vector>
#include "define.h"


struct Geometry
{
    std::vector<uint32> indexes {};

    uint32 indiceNumber;

    std::vector<DirectX::XMFLOAT3> positions {};
    std::vector<DirectX::XMFLOAT4> colors {};
    std::vector<DirectX::XMFLOAT2> UVs {};
    std::vector<DirectX::XMFLOAT3> normals {};
};


#endif