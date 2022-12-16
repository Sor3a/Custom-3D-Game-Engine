#include "PointLight.h"
#include <string>

PointLight::PointLight(Shader* shader, Primitive* primitive, const glm::vec3 pos, const glm::vec3& ambient, const glm::vec3 diff,
	const glm::vec3 spec, float quadratic,float linear_,float constant,const glm::vec3& color):
	LightingObject(color,shader,primitive,pos,ambient,diff,spec),
	constant(constant),linear_(linear_),quadratic(quadratic) {}

void PointLight::assignVariablesToShader(Shader* s)
{
	s->setUniformVec3f("lightPoint.position", position);

	//change them when work with mutiple stuff
	// 
	s->setUniformVec3f("lightPoint.ambient", ambient);
	s->setUniformVec3f("lightPoint.diffuse", diffuse);
	s->setUniformVec3f("lightPoint.specular", specular);


	s->setUniform1f("lightPoint.constant", constant);
	s->setUniform1f("lightPoint.linear_", linear_);
	s->setUniform1f("lightPoint.quadratic", quadratic);
}
void PointLight::assignVariablesToShader(Shader* s, int i)
{
	std::string name = "lightPoint[" + std::to_string(i) + "]";
	s->setUniformVec3f(name+".position", position);

	s->setUniformVec3f(name+".ambient", ambient);
	s->setUniformVec3f(name + ".diffuse", diffuse);
	s->setUniformVec3f(name + ".specular", specular);


	s->setUniform1f(name + ".constant", constant);
	s->setUniform1f(name + ".linear_", linear_);
	s->setUniform1f(name + ".quadratic", quadratic);
}
