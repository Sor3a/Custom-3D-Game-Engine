#pragma once
#include "../VertexBuffer_Layout/VertexBuffer.h"
#include "../VertexBuffer_Layout/VertexBufferLayout.h"
class VertexArray
{
private:
	unsigned int m_RendererID;
	unsigned int _NumberOfVertexs;
public:
	VertexArray();
	~VertexArray();
	void Bind() const;
	void UnBind() const;
	void AddBuffer(const VertexBuffer& vb ,const VertexBufferLayout& layout);
	inline unsigned int getNumberOfVertexs() const { return _NumberOfVertexs; }
	inline unsigned int getID() const { return m_RendererID; }
private:

};

