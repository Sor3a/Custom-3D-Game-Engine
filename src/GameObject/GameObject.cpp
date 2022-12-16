
#include "GameObject.h"
#include "../SpeeDEngine/GameObjectManager.h"

GameObject::GameObject(Shader* shader,  Primitive* primitive, const glm::vec3& position,const glm::vec3& scale ,const glm::vec3& rotationAxis, float rotationDegree):
    shader(shader), drawable_(primitive),position(position)
{
    material = &_Material;
    this->rotationAxis = rotationAxis;
    this->rotationDegree = rotationDegree;
    this->scale = scale;
    
    if (shader != nullptr)
        shader->setUniformVec4f("lightColor", glm::vec4(1, 1, 1, 1));
    //model = nullptr;
}
GameObject::GameObject(Material* mat, Primitive* primitive, const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotationAxis, float rotationDegree):
    material(mat), drawable_(primitive),position(position),scale(scale),rotationAxis(rotationAxis),rotationDegree(rotationDegree)
{
    shader = &_shader;
    if (shader != nullptr)
        shader->setUniformVec4f("lightColor", glm::vec4(1, 1, 1, 1));
    //model = nullptr;
}
GameObject::GameObject(Primitive* primitive, const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotationAxis , float rotationDegree):
    drawable_(primitive),position(position),scale(scale),rotationAxis(rotationAxis),rotationDegree(rotationDegree)
{
    //model = nullptr;
    material = &_Material;
    shader = &_shader;
    if (shader != nullptr)
        shader->setUniformVec4f("lightColor", glm::vec4(1, 1, 1, 1));
    
}
GameObject::GameObject(Material* mat,Shader* shader, Primitive* primitive, const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotationAxis, float rotationDegree) : 
    shader(shader), drawable_(primitive), position(position)
{
   // model = nullptr;
    if (shader == nullptr) shader = &_shader;
    this->rotationAxis = rotationAxis;
    this->rotationDegree = rotationDegree;
    this->scale = scale;
    material = mat; //the changment of the material gonna apply to all of others exactly on texture since all of them all the same pointers 
    if (shader != nullptr)
        shader->setUniformVec4f("lightColor", glm::vec4(1, 1, 1, 1));
}
GameObject::GameObject(const char* path, Shader* shader, const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotationAxis, float rotationDegree):
    shader(shader),position(position),scale(scale),rotationAxis(rotationAxis),rotationDegree(rotationDegree)
{
    drawable_ = new Model(path);
    isModel = true;
    //std::cout << (typeid(*drawable_).name()==typeid(Model).name()) << std::endl;
    material = &_Material;
   // primitive_ = nullptr;
}

void GameObject::SetPosition(const glm::vec3& position)
{
    this->position = position;
}
void GameObject::setScale(const glm::vec3& scale)
{
    this->scale = scale;
}
void GameObject::setRotation(const glm::vec3& rotationAxis, float rotationDegree)
{
    this->rotationAxis = rotationAxis;
    this->rotationDegree = rotationDegree;
}
void GameObject::SetPositionRotation(const glm::vec3& position, const glm::vec3& rotationAxis, float rotationDegree)
{
    SetPosition(position);
    setRotation(rotationAxis, rotationDegree);
}
void GameObject::Draw()
{
    
    glm::mat4 model = glm::mat4(1.0f);

    if (position != glm::vec3(0, 0, 0))
        model = glm::translate(model, position);

    if (rotationDegree != 0)
        model = glm::rotate(model, glm::radians(rotationDegree), rotationAxis);

    if (scale != glm::vec3(0, 0, 0))
        model = glm::scale(model, scale);
    
    //glm::mat4 result = GameObjectManager::projection * Camera::getView() * model;
    shader->setUniformMat4f("projection", GameObjectManager::projection);
    shader->setUniformMat4f("view", Camera::getView());
    shader->setUniformMat4f("model", model);
    shader->setUniformMat3f("Normal_mat", glm::mat3(glm::inverse(model)),GL_TRUE);
    //shader->setUniformVec4f("material.color",_Material.Color);
    PassMaterial();

    if (drawable_)
        drawable_->Draw(*shader);
 
}
void GameObject::PassMaterial()
{
    if (material)
    {
        shader->setUniform1f("material.ambient", material->ambientStrength);
        shader->setUniform1f("material.diffuse", material->diffuseStrength);
        shader->setUniform1f("material.specular", material->specularStrength);
        shader->setUniform1f("material.shininess", material->shininess);
        shader->setUniformVec4f("material.color", material->Color);
        if (!isModel)
        {
            unsigned int diffuseNr = 1;
            unsigned int specularNr = 1;
            for (unsigned int i = 0; i < material->textureID.size(); i++)
            {
                std::string number;
                std::string name = material->textureID[i].type;
                // std::cout << name << std::endl;
                if (name != "")
                {
                    if (name == "texture_diffuse")
                        number = std::to_string(diffuseNr++);
                    else if (name == "texture_specular")
                        number = std::to_string(specularNr++);
                    std::string textureN = "material." + name + number;
                    shader->setUniform1i(textureN, i);
                    Texture::BindWithId(i, (material->textureID)[i].id);
                }
            }
        }
        

    }
}