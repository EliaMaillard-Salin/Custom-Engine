#include "pch.h"
#include "PrimitiveFactory.h"
#include <cmath>

#define PI 3.14159265358979323846
PrimitiveFactory* PrimitiveFactory::Get()
{
    static PrimitiveFactory instance;

    return &instance;
}

Geometry* PrimitiveFactory::GetPrimitiveGeometry(PrimitiveType primitiveType)
{
    return &PrimitiveFactory::Get()->m_geometries[primitiveType];
}

void PrimitiveFactory::InitPrimitiveGeometry()
{
    PrimitiveFactory* pInstance = PrimitiveFactory::Get();

    Geometry cube;
    Geometry sphere;

    // Cube positions
    cube.positions = {
        { -0.5f, -0.5f, -0.5f }, { 0.5f, -0.5f, -0.5f }, { 0.5f, 0.5f, -0.5f }, { -0.5f, 0.5f, -0.5f }, // Front face
        { 0.5f, -0.5f, -0.5f }, { 0.5f, -0.5f, 0.5f }, { 0.5f, 0.5f, 0.5f }, { 0.5f, 0.5f, -0.5f }, // Right face
        { 0.5f, -0.5f, 0.5f }, { -0.5f, -0.5f, 0.5f }, { -0.5f, 0.5f, 0.5f }, { 0.5f, 0.5f, 0.5f }, // Back face
        { -0.5f, -0.5f, 0.5f }, { -0.5f, -0.5f, -0.5f }, { -0.5f, 0.5f, -0.5f }, { -0.5f, 0.5f, 0.5f }, // Left face
        { -0.5f, 0.5f, -0.5f }, { 0.5f, 0.5f, -0.5f }, { 0.5f, 0.5f, 0.5f }, { -0.5f, 0.5f, 0.5f }, // Top face
        { -0.5f, -0.5f, 0.5f }, { 0.5f, -0.5f, 0.5f }, { 0.5f, -0.5f, -0.5f }, { -0.5f, -0.5f, -0.5f }  // Bottom face
    };

    // Cube indices
    cube.indexes = {
        0,  1,  2,  0,  2,  3,
        4,  5,  6,  4,  6,  7,
        8,  9, 10,  8, 10, 11,
       12, 13, 14, 12, 14, 15,
       16, 17, 18, 16, 18, 19,
       20, 21, 22, 20, 22, 23
    };

    // Cube UVs
    cube.UVs = {
        { 0.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f },
        { 0.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f },
        { 0.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f },
        { 0.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f },
        { 0.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f },
        { 0.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f }
    };

    cube.indiceNumber = 36;

    // Calculate normals for cube
    cube.normals = {
        { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, // Front face
        { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, // Right face
        { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f, -1.0f }, // Back face
        { -1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, // Left face
        { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, // Top face
        { 0.0f, -1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }  // Bottom face
    };

    pInstance->m_geometries.push_back(cube);

    // Sphere generation (positions, UVs, indices)
    float rayon = 0.5f;
    int segmentCount = 50;
    float phi = 0.f;
    float theta = 0.f;

    for (int i = 0; i <= segmentCount; ++i)
    {
        phi = PI * i / segmentCount;
        for (int j = 0; j <= segmentCount; ++j)
        {
            theta = 2 * PI * j / segmentCount;
            DirectX::XMFLOAT3 vertex;
            vertex.x = rayon * sin(phi) * cos(theta);
            vertex.y = rayon * cos(phi);
            vertex.z = rayon * sin(phi) * sin(theta);
            sphere.positions.push_back(vertex);

            float u = 1.0f - (j / (float)segmentCount);
            float v = 1.0f - (i / (float)segmentCount);

            sphere.UVs.push_back(DirectX::XMFLOAT2(u, v));

            // Normals for the sphere
            DirectX::XMFLOAT3 normal = { vertex.x, vertex.y, vertex.z };
            float length = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
            normal.x /= length;
            normal.y /= length;
            normal.z /= length;
            sphere.normals.push_back(normal);
        }
    }

    for (int i = 0; i < segmentCount; ++i)
    {
        for (int j = 0; j < segmentCount; ++j)
        {
            int index = i * (segmentCount + 1) + j;
            sphere.indexes.push_back(index);
            sphere.indexes.push_back(index + 1);
            sphere.indexes.push_back(index + segmentCount + 1);

            sphere.indexes.push_back(index + 1);
            sphere.indexes.push_back(index + segmentCount + 2);
            sphere.indexes.push_back(index + segmentCount + 1);
        }
    }
    sphere.indiceNumber = sphere.indexes.size();
    pInstance->m_geometries.push_back(sphere);
}

