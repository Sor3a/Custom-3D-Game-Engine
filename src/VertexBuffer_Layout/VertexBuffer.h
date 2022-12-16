#pragma once

class VertexBuffer
{
private:
	unsigned int m_RenderID;
	unsigned int _SizeOfBuffer;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();
	void Bind() const;
	void UnBind() const;
	inline unsigned int getBufferSize() const { return _SizeOfBuffer; }

};