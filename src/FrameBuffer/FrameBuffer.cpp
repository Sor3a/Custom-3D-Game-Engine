#include "FrameBuffer.h"
#include<iostream>

FrameBuffer::FrameBuffer()
{
	glGenFramebuffers(1, &m_RenderId);
}

void FrameBuffer::Bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_RenderId);
}
void FrameBuffer::UnBind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void FrameBuffer::AttachTexture(unsigned int texture) const
{
	Bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,texture, 0);
}
void FrameBuffer::AttachDepthTexture(unsigned int texture) const
{
	Bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
		texture, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


}
bool FrameBuffer::CheckIfComplete() const
{
	Bind();
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
		return true;
	std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return false;
}
void FrameBuffer::AttachRBO_Depth_Stencil(unsigned int rbo)
{
	Bind();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER, rbo);
}