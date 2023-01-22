#pragma once
#include"../Shader/Shader.h"
#include "../Camera/Camera.h"
class Scene
{

public: 
	virtual void Start(Shader* s) = 0;
	virtual void Render(Shader* s = nullptr, glm::mat4 proj = glm::mat4(1), glm::mat4 view = glm::mat4(1)) = 0;
	virtual void End() = 0;
	
};
