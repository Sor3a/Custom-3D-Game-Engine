#include "Camera.h"
#include"../SpeeDEngine/GameObjectManager.h"

glm::mat4 Camera::view = glm::mat4(1);
void Camera::CameraWork()
{
	//std::cout << (cameraPos + CameraForward).z << std::endl;
	if (!change)
		view = view = glm::lookAt(cameraPos, cameraPos + CameraForward, cameraUp);
}

void Camera::mouse_callback( double xpos, double ypos)
{
	if (firstTime)
	{
		lastX = xpos;
		lastY = ypos;
		firstTime = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	yaw += xoffset;
	pitch += yoffset;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	CameraForward = glm::normalize(direction);
}

void Camera::CameraMoveWithInput(GLFWwindow * window)
{
	if (!change)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glm::vec3 direction = glm::vec3(CameraForward.x, 0, CameraForward.z);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * GameObjectManager::deltaTime * direction;// *CameraForward;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * GameObjectManager::deltaTime * direction;// *CameraForward;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= glm::normalize(glm::cross(CameraForward, cameraUp)) * cameraSpeed * GameObjectManager::deltaTime;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += glm::normalize(glm::cross(CameraForward, cameraUp)) * cameraSpeed * GameObjectManager::deltaTime;
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			change = true;
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			change = false;
	}
	


	//void mouse_callback(GLFWwindow * window, double xpos, double ypos);
	//glfwSetCursorPosCallback(window, std::bind(&Camera::mouse_callback, this, std::placeholders::_1));
	double xpos=0,ypos=0;
	glfwGetCursorPos(window,&xpos,&ypos);
	mouse_callback(xpos, ypos);

}
void Camera::SetCameraSpeed(float s)
{
	cameraSpeed = s;
}

