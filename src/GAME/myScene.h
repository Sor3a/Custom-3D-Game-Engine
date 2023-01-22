#pragma once
#include"../Scene/Scene.h"
#include "../GameObject/GameObject.h"
#include "../SkyBox/SkyBox.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

class myScene :public Scene
{

	Cube cube_;
	//Materials
	Material* BoxesMaterials;
	Material* planeMaterial;
	Material* playerMaterial;
	//Textures


	//GameOjbects
	std::vector<GameObject*> objects;
	GameObject* plane;
	GameObject* player;

	//skyBox
	SkyBox* sky;


	float playerSpeed,playerSpeedMax,forwardSpeed;

	std::string whatToShow;
	ImVec4 color;

	void showWinLostUI(std::string whatToShow);


public :
	Camera* camera;
	void Start(Shader* s);
	void Render(Shader* s = nullptr, glm::mat4 proj = glm::mat4(1), glm::mat4 view = glm::mat4(1));
	void End();
	void Update(GLFWwindow *window);
	~myScene();
	
};
