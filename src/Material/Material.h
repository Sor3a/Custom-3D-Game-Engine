#pragma once
#include"glm/glm.hpp"
#include"../Texture/Texture.h"
#include<iostream>
#include<../Model/Mesh.h>

class Material
{
private:
	Texture texture;
	void NormalizeAmbients();

public:
	glm::vec4 Color;
	float ambientStrength, diffuseStrength, specularStrength;
	std::vector<Texture_> textureID;
	float shininess;
	Material(const std::vector<Texture_>& texture, const glm::vec4& color = glm::vec4(1, 1, 1, 0), float shiness = 32);
	Material(const Texture& texture, const glm::vec4& color = glm::vec4(1, 1, 1, 0), float shiness = 32);
	Material(const glm::vec4& color = glm::vec4(1, 1, 1, 0), float shiness = 32);
	void SetStrength(const float& amb, const float& diff, const float& speculat);
	//void setMaterial(const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& speculat);
	inline void changeShines(float s) { shininess = s; }
	inline void AssigneTextures(const std::vector<Texture_>& vecs) { textureID.clear(); for (int i = 0; i < vecs.size(); i++)textureID.emplace_back(vecs[i].id, vecs[i].type); }
	// i should add material add texture

};
// to do do a variable that gets the ambient * strength once it changes and not every time