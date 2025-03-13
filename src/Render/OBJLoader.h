#ifndef RENDER_OBJLOADER_H_INCLUDED
#define RENDER_OBJLOADER_H_INCLUDED
struct Geometry;


class OBJLoader
{
public:

    static OBJLoader* Get();

    static Geometry* LoadAndTriangulateOBJ();  //
    static Geometry* LoadOBJ(const char* filePath, DirectX::XMFLOAT4 color);       // assuming obj file is triagulated


private:
    static std::vector<std::string> SplitString(std::string string, char separator);
};


#endif