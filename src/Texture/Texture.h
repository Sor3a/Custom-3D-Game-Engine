#pragma once

#include "../Renderer/Renderer.h"

class Texture
{
protected:
	unsigned int RendererID;

	unsigned char* _LocalBuffer;
	int _width, _height, _BPP;
	std::string type;
	virtual void Clamping_Texture(unsigned int ClampValue, float* borderColor);
	virtual void Texture_Filtre(unsigned int FilterMood);
	void MipMap_Filter(unsigned int filter);
public:
	
	static unsigned int TextureFromFile(const char* path);
	static void BindWithId(unsigned int slot, unsigned int id);

	std::string _FilePath;
	Texture(const std::string& path= "res/textures/default_Texture.jpg", const std::string& type="texture_diffuse", unsigned int TextureFilterType = GL_LINEAR, unsigned int ClampType = GL_CLAMP_TO_BORDER, float* borderColor = nullptr, unsigned int MipMapFilter = 0);
	Texture(const GLvoid* data,unsigned int width= 1280, unsigned int height = 720, unsigned int TextureFilterType = GL_LINEAR, unsigned int ClampType = GL_CLAMP_TO_BORDER, float* borderColor = nullptr);
	Texture(int a=0){};
	~Texture();
	void Bind(unsigned int slot=0) const;
	virtual void UnBind() const;
	virtual inline int getWidth() const { return _width;}
	virtual inline int getHeight() const { return _height; }
	inline unsigned int GetID() const { return RendererID; };
	inline const std::string& GetType() const { return type; };
	inline std::string SetType(const std::string& new_type) { type = new_type; }
};

class DepthTexture :public Texture
{
public:
	DepthTexture(unsigned int width= 1024,unsigned int height= 1024);
};