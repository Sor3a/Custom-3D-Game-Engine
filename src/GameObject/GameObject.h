#pragma once
#include "../Primitives/Primitives.h"
#include "../Camera/Camera.h"
#include "../Material/Material.h"
#include "../Model/Model.h"
#include "../SpeeDEngine/Drawable.h"
class GameObject
{
protected:
	Shader* shader;
	//Primitive* primitive_;
	glm::vec3 rotationAxis;

	float rotationDegree;
	void PassMaterial();
	Drawable* drawable_;
	Material _Material;
	Shader _shader;
	bool isModel = false;
	//Model* model;
public:
	glm::vec3 position;
	glm::vec3 scale;
	Material* material;
	GameObject(Material* mat, Shader* shader, Primitive* primitive , const glm::vec3& position = glm::vec3(0), const glm::vec3& scale = glm::vec3(1), const glm::vec3& rotationAxis = glm::vec3(0), float rotationDegree = 0);
	GameObject(Material* mat, Primitive* primitive , const glm::vec3& position = glm::vec3(0), const glm::vec3& scale = glm::vec3(1), const glm::vec3& rotationAxis = glm::vec3(0), float rotationDegree = 0);
	GameObject(Shader* shader,Primitive* primitive,const glm::vec3& position = glm::vec3(0),const glm::vec3& scale=glm::vec3(1),const glm::vec3& rotationAxis = glm::vec3(0),float rotationDegree = 0);
	GameObject(Primitive* primitive, const glm::vec3& position = glm::vec3(0), const glm::vec3& scale = glm::vec3(1), const glm::vec3& rotationAxis = glm::vec3(0), float rotationDegree = 0);
	GameObject(const char* path, Shader* shader, const glm::vec3& position = glm::vec3(0), const glm::vec3& scale = glm::vec3(1), const glm::vec3& rotationAxis = glm::vec3(0), float rotationDegree = 0);
	inline ~GameObject() {if (isModel) { delete drawable_; std::cout << "delete model" << std::endl; }}
	void SetPosition(const glm::vec3& position);
	void setScale(const glm::vec3& scale);
	void setRotation(const glm::vec3 & rotationAxis,float rotationDegree);
	void SetPositionRotation(const glm::vec3& position, const glm::vec3& rotationAxis, float rotationDegree);
	virtual void Draw();
};
