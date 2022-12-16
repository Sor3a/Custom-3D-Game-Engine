#pragma once
#include "../Texture/CubeTexture.h"
//#include "../VertexAraay/VertexArray.h"
#include "../Shader/Shader.h"
class SkyBox
{
private:
	
	CubeTexture* cubeTexture;
	//VertexArray va;
	//IndexBuffer ib;
	unsigned int VAO,EBO;
	Shader skyShader;
public:
	SkyBox(CubeTexture& cubeTexture);
	void Draw();
};