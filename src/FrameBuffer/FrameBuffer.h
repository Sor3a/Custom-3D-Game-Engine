#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class FrameBuffer
{
public:
	
	FrameBuffer();
	void Bind() const;
	void UnBind() const;
	bool CheckIfComplete() const;
	void AttachDepthTexture(unsigned int texture) const;
	void AttachTexture(unsigned int texture) const; //only color texture works
	void AttachRBO_Depth_Stencil(unsigned int rbo);
	inline ~FrameBuffer() { glDeleteFramebuffers(1, &m_RenderId); }
private:
	unsigned int m_RenderId;
};
