#include "SkyBox.h"
#include "../SpeeDEngine/GameObjectManager.h"
#include "../Camera/Camera.h"
SkyBox::SkyBox(CubeTexture& cubeTexture) :
    cubeTexture(&cubeTexture), skyShader("res/shaders/sky.shader")
{
    skyShader.setUniform1i("skybox", 0);
    unsigned int cube_elements[36] = {
        // front
        1, 2, 6,
    6, 5, 1,
    // Left
    0, 4, 7,
    7, 3, 0,
    // Top
    4, 5, 6,
    6, 7, 4,
    // Bottom
    0, 3, 2,
    2, 1, 0,
    // Back
    0, 1, 5,
    5, 4, 0,
    // Front
    3, 7, 6,
    6, 2, 3
    };
    float cube_vertices[] = {
        // front
        //   Coordinates
    -1.0f, -1.0f,  1.0f,//        7--------6
     1.0f, -1.0f,  1.0f,//       /|       /|
     1.0f, -1.0f, -1.0f,//      4--------5 |
    -1.0f, -1.0f, -1.0f,//      | |      | |
    -1.0f,  1.0f,  1.0f,//      | 3------|-2
     1.0f,  1.0f,  1.0f,//      |/       |/
     1.0f,  1.0f, -1.0f,//      0--------1
    -1.0f,  1.0f, -1.0f
    };
    skyShader.setUniformMat4f("projection", GameObjectManager::projection);

    unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glGenBuffers(1, &skyboxEBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), &cube_vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), &cube_elements, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //VertexArray va;
    //va.Bind();
    //VertexBuffer vb(cube_vertices, sizeof(cube_vertices));
    ////vb.Bind();
    //IndexBuffer ib(cube_elements, 36);
    ////ib.Bind();
    //VertexBufferLayout layout;
    //layout.push<float>(3);
    //va.AddBuffer(vb, layout);
    VAO = skyboxVAO;
    EBO = skyboxEBO;
}

void SkyBox::Draw()
{

    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);
    glDepthFunc(GL_LEQUAL);

    skyShader.Bind();

    glm::mat4 projection = glm::mat4(1.0f);
    // We make the mat4 into a mat3 and then a mat4 again in order to get rid of the last row and column
    // The last row and column affect the translation of the skybox (which we don't want to affect)
    glm::mat4 view = glm::mat4(glm::mat3(Camera::getView()));
    //projection = GameObjectManager::projection;
    //skyShader.setUniformMat4f("projection", projection);
    skyShader.setUniformMat4f("view", view);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBindVertexArray(VAO);
    cubeTexture->Bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Switch back to the normal depth function
    glDepthFunc(GL_LESS);
    glCullFace(GL_BACK);
}