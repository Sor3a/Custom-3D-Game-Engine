#pragma once

#include"../LightingObject.h"
#include "../FrameBuffer/FrameBuffer.h"
#include "../Scene/Scene.h"

class DirectionalLight :private LightingObject
{
	FrameBuffer* depthFBO;
	DepthTexture* depthTexutre;
	Shader* shadowShader;
	glm::mat4 lightProjection;
	glm::mat4 lightView;
public:
	glm::vec3 direction;
	DirectionalLight(const glm::vec3& direction, Shader* shader=nullptr,const glm::vec3 ambient = glm::vec3(1), const glm::vec3 diff = glm::vec3(1), const glm::vec3 spec = glm::vec3(1));
	//void Draw() override;
	inline glm::vec3& getAmbient(){ return ambient;}
	inline glm::vec3& getDiffuse() { return diffuse;}
	inline glm::vec3& getSpecular() { return specular;}
	void setShaderVariables(Shader* s);
	void InitializeDirectionalLight(Shader* s);
	void RenderShadowTexture(Scene *scene,Camera *camera);
	inline void BindShadowMapTexture() { depthTexutre->Bind(10); }
	inline glm::mat4 getLightSpaceMatrix() { return lightProjection * lightView; }
	~DirectionalLight();
};
