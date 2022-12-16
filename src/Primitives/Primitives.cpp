#include "Primitives.h"
#include "../Renderer/Renderer.h"



//declare paths here
std::string Cube_Path = "res/3dModels/Primtives/cube.blend";



Cube::Cube() :Primitive(Cube_Path) {}

Primitive::Primitive(const std::string& path)
    :model_(path.c_str()){}

void Primitive::Draw(Shader& shader)
{
    model_.Draw(shader);
}