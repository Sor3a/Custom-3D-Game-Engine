#pragma once

#include "../LightingObject.h"

class PointLight :public LightingObject
{
public:
	float constant;
	float linear_;
	float quadratic;
	PointLight(Shader* shader,Primitive* primitive, const glm::vec3 pos = glm::vec3(0),
		const glm::vec3& ambient = glm::vec3(1), const glm::vec3 diff = glm::vec3(1),const glm::vec3 spec = glm::vec3(1),
		float quadratic = 0.0075f, float linear_ = 0.045f, float constant = 1.0f,const glm::vec3 & color = glm::vec3(1));

	inline void changePointLight(float c, float l, float q) { constant = c; linear_ = l; quadratic = q; };
	void assignVariablesToShader(Shader* shader);
	void assignVariablesToShader(Shader* shader,int i);
};