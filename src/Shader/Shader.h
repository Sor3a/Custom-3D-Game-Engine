#pragma once
#include <iostream>
#include<tuple>
#include<math.h>
#include<unordered_map>
#include<glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class Shader
{
private:
	unsigned int m_RenderID;
	std::string filePath;
	std::unordered_map <std::string, int> UniformLocations;
public:
	Shader(const std::string& fileName="res/shaders/Basic.shader");
	~Shader();
	void Bind()const;
	void UnBind()const;
	void setUniform4f(const std::string& Name,float v1, float v2, float v3, float v4);
	void setUniform1f(const std::string& Name, float value);
	void setUniform1i(const std::string& Name, int value);
	void setUniformMat4f(const std::string& Name,const glm::mat4 & matrix);
	void setUniformMat3f(const std::string& Name, const glm::mat3& matrix,unsigned int Transpose = GL_FALSE);
	void setUniformVec4f(const std::string& Name, const glm::vec4& v);
	void setUniformVec3f(const std::string& Name, const glm::vec3& v);
private:
	int getUniformLocation(const std::string& Name);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader,const std::string& geometryShader);
	std::tuple<std::string, std::string, std::string> ParseShader(const std::string& filePath);
};

