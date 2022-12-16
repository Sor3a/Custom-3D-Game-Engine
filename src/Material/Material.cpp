#include "Material.h"
#include<../Model/Model.h>

void Material::NormalizeAmbients()
{
	ambientStrength = 1;
	diffuseStrength = 1;
	specularStrength = 1;
}

Material::Material(const std::vector<Texture_>&texture, const glm::vec4& color,float s):
	shininess(s),Color(color),textureID(texture), texture()
{
	for (auto a : texture)
		std::cout << a.type << std::endl;
	NormalizeAmbients();
}

Material::Material(const Texture& texture, const glm::vec4& color, float shiness):
	Color(color), shininess(shiness), texture()
{
	std::string secondtype = texture.GetType() == "texture_diffuse" ? "texture_specular" : "texture_diffuse";
	textureID.emplace_back(texture.GetID(),texture.GetType(),"");
	textureID.emplace_back(this->texture.GetID(),secondtype,"");
	NormalizeAmbients();
}
Material::Material(const glm::vec4& color, float shiness) :
	Color(color), shininess(shiness), texture()
{
	textureID.emplace_back(texture.GetID(),texture.GetType(),"");
	textureID.emplace_back(this->texture.GetID(),"texture_specular","");
	NormalizeAmbients();
}
void Material::SetStrength(const float& amb, const float& diff, const float& speculat)
{
	ambientStrength = amb;
	diffuseStrength = diff;
	specularStrength = speculat;
}