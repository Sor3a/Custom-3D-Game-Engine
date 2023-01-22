#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <functional>
#include <iostream>
class Camera
{
private:
	static glm::mat4 view;
	float cameraSpeed = 5.0f;
	void mouse_callback(double xpos, double ypos);
	bool firstTime = true;
	double lastX, lastY;
	float yaw = 0, pitch = 0;
	bool change = false;



	//glm::vec3 CameraForward = glm::vec3(0.0f, 0.0f, -10.0f);
	
public:
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 CameraForward = glm::vec3(0.0f, -2.0f, -10.0f);
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
	inline static const glm::mat4 &getView() { return view; }
	void CameraWork();
	void CameraMoveWithInput(GLFWwindow* window);
	void SetCameraSpeed(float speed);
};
