#ifndef RENDER_PRIMITIVEFACTORY_H_INCLUDED
#define RENDER_PRIMITIVEFACTORY_H_INCLUDED
#include <vector>
#include "Geometry.h"
class Graphics;

enum PrimitiveType : uint8 {
    CUBE,
    SPHERE,

    PRIMITIVE_COUNT
};


class PrimitiveFactory
{
    friend Graphics;
public:

    static PrimitiveFactory* Get();
    static Geometry* GetPrimitiveGeometry( PrimitiveType primitiveType );

private:
    static void InitPrimitiveGeometry();

private:
    std::vector<Geometry> m_geometries;

};


#endif