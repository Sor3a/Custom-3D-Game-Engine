#include "../Renderer/Renderer.h"
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count):_Count(count)
{
    //ASSERT(sizeof(unsigned int)==sizeof(GLuint))
    glGenBuffers(1, &m_RenderID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
}
void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID));
}
void IndexBuffer::UnBind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1,&m_RenderID));
}