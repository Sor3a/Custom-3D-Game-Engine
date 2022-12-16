#include "GameObjectManager.h"



GameObjectManager::GameObjectManager()
{
    projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
    deltaTime = 0;
}


//GameObject* GameObjectManager::Create_Primitive(  Shader& shader, Primitive& primitive, Texture* texture = nullptr, const glm::vec3& position,const glm::vec3& scale, const glm::vec3& rotationAxis, float rotationDegree)
//{
//    GameObject* a = new GameObject(&shader ,texture, &primitive, position, scale,rotationAxis, rotationDegree);
//    //std::cout << a << std::endl;
//    return a;
//}

float GameObjectManager::deltaTime = 0.0f;
glm::mat4 GameObjectManager::projection = glm::mat4(1);
//void GameObjectManager::Draw_Primitive(const Primitive& primitive, Shader& s, const Texture& texture,const glm::vec3& position , const glm::vec3& rotation_Axis, float rotationDegree,const glm::vec4& color)
//{
//
//    glm::mat4 model = glm::mat4(1.0f);
//
//    if(rotationDegree!=0)
//        model = glm::rotate(model, glm::radians(rotationDegree),rotation_Axis);
//
//    if (position != glm::vec3(0, 0, 0))
//        model = glm::translate(model, position);
//
//    if(color.w!=0)
//        s.setUniformVec4f("u_Color", color);
//
//    s.setUniformMat4f("model", model);
//    s.setUniformMat4f("view", Camera::getView());
//    s.setUniformMat4f("projection", projection);
//    texture.Bind();
//    Renderer::GetInstance()->Draw(primitive.va, *(primitive).ib);
//
//}
void GameObjectManager::CalculateDeltaTime()
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}
