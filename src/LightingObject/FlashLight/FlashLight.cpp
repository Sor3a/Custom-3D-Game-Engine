#include "FlashLight.h"

FlashLight::FlashLight(float Innerangle, float outterAngle,const glm::vec3& direction, const glm::vec3& amb, const glm::vec3& diff, const glm::vec3& spec):
	LightingObject(glm::vec3(1),nullptr,nullptr,glm::vec3(0),amb,diff,spec),
	InnerAngle(glm::cos(glm::radians(Innerangle))),direction(direction),OuterAngle(glm::cos(glm::radians(outterAngle)))
	{}


void FlashLight::setShaderVariables(Shader* s)
{
	s->setUniformVec3f("flashLight.position", position);
	s->setUniformVec3f("flashLight.direction", direction);
	s->setUniform1f("flashLight.Innerangle", InnerAngle);
	s->setUniform1f("flashLight.Outerangle", OuterAngle);
	s->setUniformVec3f("flashLight.ambient", ambient);
	s->setUniformVec3f("flashLight.diffuse", diffuse);
	s->setUniformVec3f("flashLight.specular", specular);
}