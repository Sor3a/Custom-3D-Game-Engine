#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<iostream>
#include<vector>
#include "../Shader/Shader.h"
#include "../VertexAraay/VertexArray.h"
#include "../IndexBuffer/IndexBuffer.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture_ {
	unsigned int id;
	std::string type;
	std::string path;
	Texture_(unsigned int i,const std::string& t,const std::string& path):
		id(i),type(t),path(path){}
	Texture_(unsigned int i, const std::string& t) :
		id(i), type(t),path(""){}
	Texture_():id(0),type(""),path(""){}
};

class Mesh {
public:
	// mesh data

	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices,const std::vector<Texture_>& textures);
	void Draw(Shader& shader);
private:
	unsigned int size_;
	std::vector<Texture_> textures;
	unsigned int VAO, VBO, EBO;
	void setupMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
};