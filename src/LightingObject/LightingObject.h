#pragma once

#include"../GameObject/GameObject.h"

class LightingObject :public GameObject
{
private:
	glm::vec3 Color;

public:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	LightingObject(const glm::vec3& color, Shader* shader,Primitive* primitive=nullptr,const glm::vec3& position=glm::vec3(0),const glm::vec3 ambient=glm::vec3(1), const glm::vec3 diff = glm::vec3(1), const glm::vec3 spec = glm::vec3(1));
	void Draw(Shader* s = nullptr, glm::mat4 proj = glm::mat4(1), glm::mat4 view = glm::mat4(1)) override;
	inline const glm::vec3& getPosition() const { return position;}
};
