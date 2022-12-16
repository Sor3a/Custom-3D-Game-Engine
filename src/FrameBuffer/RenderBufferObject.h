#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class RenderBufferObject
{
public:
	RenderBufferObject();
	void Bind() const;
	void UnBind() const;
	void ColorRBO(unsigned int width = 1280, unsigned int height = 720);
	void DepthStencilRBO(unsigned int width = 1280, unsigned int height = 720);
	inline const unsigned int& getID()const { return m_RenderId; }
private:
	unsigned int m_RenderId;
};