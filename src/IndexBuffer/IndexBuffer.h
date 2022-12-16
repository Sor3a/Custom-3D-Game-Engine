#pragma once

class IndexBuffer
{
private:
	unsigned int m_RenderID;
	unsigned int _Count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();
	void Bind() const;
	void UnBind() const;
	inline unsigned int getCount()const { return _Count; };
	inline unsigned int getID() const { return m_RenderID; }
};