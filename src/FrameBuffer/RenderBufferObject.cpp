#include "RenderBufferObject.h"

RenderBufferObject::RenderBufferObject()
{
	glGenRenderbuffers(1, &m_RenderId);
}

void RenderBufferObject::Bind() const
{
	glBindRenderbuffer(GL_RENDERBUFFER, m_RenderId);
}

void RenderBufferObject::UnBind() const
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void RenderBufferObject::DepthStencilRBO(unsigned int width , unsigned int height )
{
	Bind();
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	UnBind();
}
void RenderBufferObject::ColorRBO(unsigned int width, unsigned int height)
{
	Bind();
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width, height);
	UnBind();
}