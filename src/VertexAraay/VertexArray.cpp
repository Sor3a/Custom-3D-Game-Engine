#include "VertexArray.h"
#include "../Renderer/Renderer.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
	_NumberOfVertexs = 0;
	Bind();
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}
void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}
void VertexArray::UnBind() const
{
	GLCall(glBindVertexArray(0));
}
void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{

	Bind();
	vb.Bind();
	const auto& elemnts = layout.getElements();
	_NumberOfVertexs = vb.getBufferSize() / layout.GetStride();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elemnts.size(); i++)
	{
		const auto& element = elemnts[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void *)offset));
		offset += element.count * VetexBufferElement::GetSizeOfType(element.type);

	}
}