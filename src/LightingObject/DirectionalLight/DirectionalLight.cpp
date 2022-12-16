#include "DirectionalLight.h"


DirectionalLight::DirectionalLight(const glm::vec3& direction, Shader* shader, const glm::vec3 ambient, const glm::vec3 diff, const glm::vec3 spec):
	LightingObject(glm::vec3(0),shader,nullptr,glm::vec3(0),ambient,diff,spec),direction(direction)
{}

void DirectionalLight::setShaderVariables(Shader* s)
{
	s->setUniformVec3f("Dir_Light.ambient", ambient);
	s->setUniformVec3f("Dir_Light.diffuse", diffuse);
	s->setUniformVec3f("Dir_Light.specular", specular);
	s->setUniformVec3f("Dir_Light.direction", direction);
}
