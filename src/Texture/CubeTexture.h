#pragma once
#include "Texture.h"
#include <iostream>
class CubeTexture :public Texture
{
private:
	virtual void Clamping_Texture(unsigned int ClampValue, float* borderColor) override;
	void Texture_Filtre(unsigned int FilterMood) override;
public:
	int getWidth() = delete;
	int getHeight() = delete;
	//void Bind(unsigned int slot = 0) const = delete;
	void Bind(unsigned int slot =0) const;
	void UnBind() const;
	CubeTexture(const std::vector<std::string>&faces); 
	CubeTexture(unsigned int shadowWidth, unsigned int shadowHeight);
};
