#pragma once

class UniformBufferObject
{
private:
	unsigned int Renderer_ID;
public:
	UniformBufferObject(unsigned int sizeOfData, int bindingPointIndice=0);
	void Bind() const;
	void UnBind() const;
	void BufferData(unsigned int offset, unsigned int size, float* data);
};