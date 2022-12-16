
#include "../Renderer/Renderer.h"
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_RenderID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    _SizeOfBuffer = size;
}
void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
}
void VertexBuffer::UnBind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1,&m_RenderID));
}