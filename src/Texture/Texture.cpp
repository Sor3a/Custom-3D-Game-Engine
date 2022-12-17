#include "Texture.h"
#include"../vendor/stb_Image/stb_Image.h"
#include <iostream>
void Texture::Clamping_Texture(unsigned int ClampType, float *borderColor)
{
	GLCall(glBindTexture(GL_TEXTURE_2D, RendererID));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ClampType));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ClampType));

	if (ClampType == GL_CLAMP_TO_BORDER)
	{
		if(borderColor != nullptr)
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		else
		{
			float borderColor_[] = { 0,0,0,0 };
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor_);
		}	
	}
}
void Texture::Texture_Filtre(unsigned int FilterMood)
{
	GLCall(glBindTexture(GL_TEXTURE_2D, RendererID));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilterMood));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilterMood));
}
void Texture::MipMap_Filter(unsigned int filter)
{
	Bind();
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glGenerateMipmap(GL_TEXTURE_2D);
	UnBind();
}
Texture::Texture(const GLvoid* data,unsigned int width, unsigned int height, unsigned int TextureFilterType , unsigned int ClampType , float* borderColor ):
	_width(width),_height(height)
{
	GLCall(glGenTextures(1, &RendererID));
	Texture_Filtre(TextureFilterType);
	Clamping_Texture(ClampType, borderColor);
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

}
Texture::Texture(const std::string& path,const std::string& type,unsigned int TextureFilterType,unsigned int ClampType,float * borderColor,unsigned int MipMapFilter) :
	_FilePath(path),RendererID(0), _LocalBuffer(nullptr), _width(0),_height(0), _BPP(0),type(type){
	stbi_set_flip_vertically_on_load(1);
	_LocalBuffer = stbi_load(_FilePath.c_str(), &_width, &_height, &_BPP, 4);
	GLCall(glGenTextures(1, &RendererID));
	Texture_Filtre(TextureFilterType);
	//float borderColor[4] = {1.0f,0.0f,0.0f,1}; // when we use BoardType
	Clamping_Texture(ClampType, borderColor);
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA8, _width, _height,0, GL_RGBA,GL_UNSIGNED_BYTE, _LocalBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (_LocalBuffer)
		stbi_image_free(_LocalBuffer);

	if (MipMapFilter != 0)
		MipMap_Filter(MipMapFilter);
}
Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &RendererID));
}
Texture::Texture(int a,int b) { std::cout << "depth texture created" << std::endl; }
void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, RendererID));
}
void Texture::UnBind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
void Texture::BindWithId(unsigned int slot, unsigned int id)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, id));
}

unsigned int Texture::TextureFromFile(const char* path)
{
	std::string filename = std::string(path);
	//filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		//GLenum format;
		//if (nrComponents == 1)
		//	format = GL_RED;
		//else if (nrComponents == 3)
		//	format = GL_RGB;
		//else if (nrComponents == 4)
		//	format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

DepthTexture::DepthTexture(unsigned int width, unsigned int height):
	Texture(3,7)
{
	_width = width;
	_height = height;
	type = "Depth texture";
	glGenTextures(1, &RendererID);
	glBindTexture(GL_TEXTURE_2D, RendererID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width,
		height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

}