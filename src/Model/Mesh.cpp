#include "Mesh.h"
#include<string>
#include "../Camera/Camera.h"
#include "../SpeeDEngine/GameObjectManager.h"
#include "../Renderer/Renderer.h"


Mesh::Mesh(const std::vector<Vertex>& vertices,const std::vector<unsigned int>& indices, const std::vector<Texture_>& textures)
{
	this->textures = textures;
	setupMesh(vertices,indices);
}

void Mesh::setupMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
		&vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() *
		sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)offsetof(Vertex, Normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)offsetof(Vertex, TexCoords));
	glBindVertexArray(0);
	size_ = indices.size();
}

void Mesh::Draw(Shader& shader)
{

	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;

	for (unsigned int i = 0; i < textures.size(); i++)
	{

		glActiveTexture(GL_TEXTURE0 + i); // activate texture unit first
		// retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name = textures[i].type;
		if (name != "")
		{
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);
			std::string textureN = "material." + name + number;
			
			shader.setUniform1i(textureN.c_str(), i);
			//std::cout << textures[i].id << std::endl;
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
	}
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, size_, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}