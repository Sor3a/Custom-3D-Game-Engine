#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include"../Renderer/Renderer.h"
#include <GLFW/glfw3.h>
#include "../GameObject/GameObject.h"

class GameObjectManager
{
private:
	
	float lastFrame=0;
	
public:
	static glm::mat4 projection;
	static float deltaTime;

	GameObjectManager();  //add projection Paramater If I want to
	//GameObject* Create_Primitive(Shader& shader, Primitive& primitive, Texture* texture = nullptr, const glm::vec3& position = glm::vec3(0, 0, 0), const glm::vec3& scale=glm::vec3(1,1,1), const glm::vec3& rotationAxis = glm::vec3(0, 0, 0), float rotationDegree = 0.0f);
	//void Draw_Primitive(const Primitive& primitive, Shader& s,const Texture& texture,const glm::vec3& position= glm::vec3(0.0f, 0.0f, 0.0f),const glm::vec3& rotation_Axis= glm::vec3(0.0f, 0.0f, 0.0f),float rotationDegree=0,const glm::vec4& color=glm::vec4(0));
	void CalculateDeltaTime();
	void PassDataToShaders();
};