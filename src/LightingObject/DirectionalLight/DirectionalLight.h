#pragma once

#include"../LightingObject.h"

class DirectionalLight :private LightingObject
{

public:
	glm::vec3 direction;
	DirectionalLight(const glm::vec3& direction, Shader* shader=nullptr,const glm::vec3 ambient = glm::vec3(1), const glm::vec3 diff = glm::vec3(1), const glm::vec3 spec = glm::vec3(1));
	//void Draw() override;
	inline glm::vec3& getAmbient(){ return ambient;}
	inline glm::vec3& getDiffuse() { return diffuse;}
	inline glm::vec3& getSpecular() { return specular;}
	void setShaderVariables(Shader* s);
};
