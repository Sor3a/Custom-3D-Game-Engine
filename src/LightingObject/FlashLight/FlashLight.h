#pragma once

#include "../LightingObject.h"

class FlashLight : private LightingObject
{
private:
	float InnerAngle;
	float OuterAngle;
public:

	glm::vec3 direction;
	FlashLight(float Innerangle = 10, float outerAngle = 13,const glm::vec3& direction=glm::vec3(0),const glm::vec3& amb = glm::vec3(1), const glm::vec3& diff = glm::vec3(1), const glm::vec3& spec = glm::vec3(1));
	inline void setPosition(const glm::vec3& pos) { position = pos; }
	inline const glm::vec3& getPosition ()const { return position; }
	inline glm::vec3& getAmbient() { return ambient; }
	inline glm::vec3& getDiffuse() { return diffuse; }
	inline glm::vec3& getSpecular() { return specular; }
	inline void setInnerAngle(float angle) { InnerAngle = glm::cos(glm::radians(angle)); }
	inline void setOutterAngle(float angle) { OuterAngle = glm::cos(glm::radians(angle)); }
	void setShaderVariables(Shader* s);
};
