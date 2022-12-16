#include "LightingObject.h"
#include"../SpeeDEngine/GameObjectManager.h"


LightingObject::LightingObject(const glm::vec3& color, Shader* shader, Primitive* primitive, const glm::vec3& position , const glm::vec3 ambient , const glm::vec3 diff , const glm::vec3 spec ) 
    :GameObject(shader, primitive, position), ambient(ambient), diffuse(diff), specular(spec)
{
    Color = color;
    if (shader != nullptr)
    {
        shader->setUniformMat4f("projection", GameObjectManager::projection);
        shader->setUniform4f("u_Color", Color.x, Color.y, Color.z, 1);
    }

}

//:GameObject(shader, nullptr, primitive, position), ambient(amb), diffuse(diff), specular(spec)

void LightingObject::Draw()
{

    glm::mat4 model = glm::mat4(1.0f);

    if (position != glm::vec3(0, 0, 0))
        model = glm::translate(model, position);

    if (rotationDegree != 0)
        model = glm::rotate(model, glm::radians(rotationDegree), rotationAxis);

    if (scale != glm::vec3(0, 0, 0))
        model = glm::scale(model, scale);


    shader->setUniformMat4f("model", model);
    shader->setUniformMat4f("view", Camera::getView());

    //glm::mat4 scale = glm::mat4(20.0f);
    //scale[3][3] = 1;
    //shader->setUniformMat4f("scale", scale);
    //texture->Bind();
    if (drawable_ != nullptr)
        drawable_->Draw(*shader);
        //Renderer::GetInstance()->Draw(primitive_->va, *(primitive_)->ib, *shader);
}