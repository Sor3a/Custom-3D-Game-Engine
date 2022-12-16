#pragma once

#include <vector>
#include <GL/glew.h>
struct VetexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	VetexBufferElement(unsigned int type, unsigned int count, unsigned int normalized):
		type(type),count(count),normalized(normalized)
	{
		
	}
	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return sizeof(GLfloat);
		case GL_UNSIGNED_BYTE: return sizeof(GLbyte);
		case GL_UNSIGNED_INT :return sizeof(GLuint); 
		}
		return 0;
	}
};


class VertexBufferLayout
{

private:
	std::vector<VetexBufferElement> m_Elements;
	unsigned int _Stride{ 0 };
public:


	template<typename T>
	void push(unsigned int count)
	{

	}
	template<>
	void push<float>(unsigned int count)
	{
		//VetexBufferElement a{ GL_FLOAT,count,GL_FALSE };
		m_Elements.emplace_back(GL_FLOAT, count, GL_FALSE);
		_Stride += sizeof(GLfloat)*count;
	}
	//void push< unsigned int >(unsigned int count)
	//{
	//	
	//	VetexBufferElement a{ GL_UNSIGNED_INT,count,GL_FALSE };
	//	m_Elements.emplace_back(a);
	//	_Stride += sizeof(GLuint);
	//}
	//void push<unsigned char>(unsigned int count)
	//{
	//	VetexBufferElement a{ GL_UNSIGNED_BYTE,count,GL_TRUE };
	//	m_Elements.emplace_back(a);
	//	_Stride += sizeof(GLbyte);
	//}
	inline const std::vector<VetexBufferElement>& getElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return _Stride; }

};


