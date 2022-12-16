#include "UniformBufferObject.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Renderer/Renderer.h"

UniformBufferObject::UniformBufferObject(unsigned int size, int bindingPoint)
{
	glGenBuffers(1, &Renderer_ID);
	glBindBuffer(GL_UNIFORM_BUFFER, Renderer_ID);
	(glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW));
	(glBindBufferRange(GL_UNIFORM_BUFFER, bindingPoint, Renderer_ID, 0,size));
}

void UniformBufferObject::Bind() const
{
	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, Renderer_ID));
}
void UniformBufferObject::UnBind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBufferObject::BufferData(unsigned int offset, unsigned int size, float* data)
{
	Bind();
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	UnBind();

}