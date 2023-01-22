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

void DirectionalLight::InitializeDirectionalLight(Shader *s)
{
	depthFBO = new FrameBuffer();
	depthTexutre = new DepthTexture(4096, 4096);
	shadowShader = new Shader("res/shaders/shadowShader.shader");
	
	depthFBO->AttachDepthTexture(depthTexutre->GetID());
	depthFBO->CheckIfComplete();

	float near_plane = 0.5f, far_plane = 50.0f;

	lightProjection = glm::ortho(-60.0f, 60.0f, -60.0f, 60.0f,
		near_plane, far_plane);
	lightView = glm::lookAt(glm::vec3(0, 8.0f, -3.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	shadowShader->UnBind();
	s->setUniform1i("shadowMap", 10);
	s->UnBind();
}
void DirectionalLight::RenderShadowTexture(Scene* scene, Camera* camera)
{
	glViewport(0, 0, depthTexutre->getWidth(), depthTexutre->getHeight());
	depthFBO->Bind();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	Renderer::GetInstance()->Clear();
	Renderer::GetInstance()->Enable();
	glCullFace(GL_FRONT);
	float x = camera->cameraPos.x;
	float z = camera->cameraPos.z;

	lightView = glm::lookAt(glm::vec3(0, 8.0f, -3.0f+z), 
		glm::vec3(0.0f, 0.0f, 0.0f+z),
		glm::vec3(0.0f, 1.0f, 0.0f)); //change the directional light shadow only in the camera view

	scene->Render(shadowShader, lightProjection, lightView);

	glCullFace(GL_BACK);
	depthFBO->UnBind();
}
DirectionalLight::~DirectionalLight()
{
	delete depthFBO;
	delete depthTexutre;
	delete shadowShader;
}