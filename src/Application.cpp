#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include<string>
#include<sstream>
#include<tuple>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "SpeeDEngine/GameObjectManager.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "LightingObject/LightingObject.h"
#include "LightingObject/PointLight/PointLight.h"
#include "LightingObject/DirectionalLight/DirectionalLight.h"
//#include "LightingObject/FlashLight/FlashLight.h"
//#include "Material/Material.h"
//#include "Model/Model.h"
//#include <map>
//#include "FrameBuffer/FrameBuffer.h"
//#include "FrameBuffer/RenderBufferObject.h"
//#include "Texture/CubeTexture.h"
//#include "SkyBox/SkyBox.h"
//#include"../vendor/stb_Image/stb_Image.h"
//#include "VertexBuffer_Layout/VertexBuffer.h"
//#include"Renderer/Renderer.h"
//#include "Texture/Texture.h"
//#include "Camera/Camera.h"
//#include "Primitives/Primitives.h"

#include"UniformBufferObject/UniformBufferObject.h"
#include "GAME/myScene.h"
#include "FrameRenderer/FrameRenderer.h"

#define call(x) x;\
    if (error) __debugbreak();




bool error = false;
void msg( GLenum type, const GLchar* message)
{
    error = true;
    std::cout << "[OpenGL Error](" << type << ") " << message << std::endl;
}
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    call(msg(type,message));
}

int main(void)
{
    GLFWwindow* window;

    //glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 720, "Sor3a", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glewInit();
    std::cout << glGetString(GL_VERSION) << std::endl;
    /* Loop until the user closes the window */
    {
        //float skyboxVertices[] =
        //{
        //    //   Coordinates
        //    -1.0f, -1.0f,  1.0f,//        7--------6
        //     1.0f, -1.0f,  1.0f,//       /|       /|
        //     1.0f, -1.0f, -1.0f,//      4--------5 |
        //    -1.0f, -1.0f, -1.0f,//      | |      | |
        //    -1.0f,  1.0f,  1.0f,//      | 3------|-2
        //     1.0f,  1.0f,  1.0f,//      |/       |/
        //     1.0f,  1.0f, -1.0f,//      0--------1
        //    -1.0f,  1.0f, -1.0f
        //};
        //unsigned int skyboxIndices[] =
        //{
        //    // Right
        //    1, 2, 6,
        //    6, 5, 1,
        //    // Left
        //    0, 4, 7,
        //    7, 3, 0,
        //    // Top
        //    4, 5, 6,
        //    6, 7, 4,
        //    // Bottom
        //    0, 3, 2,
        //    2, 1, 0,
        //    // Back
        //    0, 1, 5,
        //    5, 4, 0,
        //    // Front
        //    3, 7, 6,
        //    6, 2, 3
        //};

        GameObjectManager manager;
        glfwSwapInterval(1);
        float vertices[] = {
        -1, -1, 0,0,//0 
         -0.5,-1,1,0,//1
        -1,-0.5,0,1,//2
         -0.5,-0.5,1,1,//3

        };
        /*glm::vec3 positions1[] = {
            glm::vec3(0,-2,  0),
              glm::vec3(2.5f,2,  4.0f),
              glm::vec3(-3.5f,1,  3.0f),
              glm::vec3(15.5f, 1.5,  -2.0f),
              glm::vec3(13,6,  1),
              glm::vec3(8.5f,0.9,  8.0f),
             glm::vec3(-1.5f,1.5,  -9.0f),
              glm::vec3(9.0f, 1,  -1.0f),
        };*/
        glm::vec3 lighPositions[] = {
            glm::vec3(4,9,  -5),
            glm::vec3(20,  0,  20),
            glm::vec3(-3,1.2f,-50),
            glm::vec3(-30,1,  6),
        };
        unsigned int indices[] = {
        2, 6, 7,
        2, 3, 7,

        //Bottom
        0, 4, 5,
        0, 1, 5,

        //Left
        0, 2, 6,
        0, 4, 6,

        //Right
        1, 3, 7,
        1, 5, 7,

        //Front
        0, 2, 3,
        0, 1, 3,

        //Back
        4, 6, 7,
        4, 5, 7

        };



        Shader s("res/shaders/Basic.shader");
        s.Bind();
        Shader s1("res/shaders/basic1.shader");


        Renderer::GetInstance()->Blend();

        
       // Camera camera;
        Cube cube_;

        //glDepthMask(GL_FALSE);


        myScene scene;

        PointLight PointsLights[] = {
            PointLight(&s1, &cube_,lighPositions[0],glm::vec3(0.0f),glm::vec3(2)),
             PointLight(&s1, &cube_,lighPositions[1],glm::vec3(0.0f),glm::vec3(2)),
              PointLight(&s1, &cube_,lighPositions[2],glm::vec3(0.0f)),
               PointLight(&s1, &cube_,lighPositions[3],glm::vec3(0.0f),glm::vec3(2)),
        };


        DirectionalLight directional(glm::vec3(0, -1.0f, 3), nullptr, glm::vec3(1.0f), glm::vec3(0.5f), glm::vec3(0.01f));


        // pointLight(&s1, &cube_,glm::vec3(2,3,3));
        //FlashLight flashLight(10, 13, glm::vec3(0), glm::vec3(0.1f), glm::vec3(0.3f), glm::vec3(0.5f));

        {
            const char* glsl_version = "#version 130";

            ImGui::CreateContext();

            ImGui_ImplOpenGL3_Init(glsl_version);
            ImGui_ImplGlfw_InitForOpenGL(window, true);
            ImGui::StyleColorsDark();

            bool show_demo_window = true;
            bool show_another_window = false;

            ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        }
        //GUI stuff
        //




        FrameRenderer fbR; // for rendering the frame and then show the frame
                           // on a quade 


       scene.Start(&s); //initilize the scene 
       directional.InitializeDirectionalLight(&s);  //initilize the directional light
        //glEnable(GL_FRAMEBUFFER_SRGB); //gamma correction
       
       while (!glfwWindowShouldClose(window))
        {

            Renderer::GetInstance()->StartRenderingImGui();
            /* Render here */



            manager.CalculateDeltaTime();


            directional.setShaderVariables(&s);


            //if (flashLight.direction != camera.CameraForward)
            //    flashLight.direction = camera.CameraForward;
            //flashLight.setPosition(camera.cameraPos);
            //flashLight.setShaderVariables(&s);


            s.setUniformVec3f("viewPos", scene.camera->cameraPos);


            directional.RenderShadowTexture(&scene, scene.camera); //create the shadow texture of the game

  /*  glViewport(0, 0, 1024, 1024);
      depthPointLightFB.Bind();
          Renderer::GetInstance()->Clear();
          Renderer::GetInstance()->Enable();
          CubedepthTexture.Bind();

         std::vector<glm::mat4> shadowTransforms;

          glm::vec3 lightPos = PointsLights[0].getPosition();

          shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos,
              lightPos + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));

          shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos,
              lightPos + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));

          shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos,
              lightPos + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));

          shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos,
              lightPos + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));

          shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos,
              lightPos + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));

          shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos,
              lightPos + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));


          for (int i = 0; i < 6; i++)
          {
              std::string ann = "shadowMatrices[" + std::to_string(i) + "]";
              pointLightShadowShader.setUniformMat4f(ann, shadowTransforms[i]);
          }
          pointLightShadowShader.setUniformVec3f("lightPos", lightPos);
          
            

          scene.Render(&pointLightShadowShader, glm::mat4(0), glm::mat4(0));
          CubedepthTexture.UnBind();
          depthPointLightFB.UnBind();
          */
       
            
            fbR.Bind();

            glViewport(0, 0, 1280, 720);
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            Renderer::GetInstance()->Clear();
            Renderer::GetInstance()->Enable();

          /* {


                ImGui::Begin("GameObject");                          // Create a window called "Hello, world!" and append into it.

                // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::SliderFloat3("Light Position", (float*)&PointsLights[0].getPosition(), -30, 30);
                //ImGui::ColorEdit3("clear color", (float*)&obj->position); // Edit 3 floats representing a color
                ImGui::InputFloat("Linear", &PointsLights[0].linear_, 0, 0.8f);
                ImGui::InputFloat("quadratic", &PointsLights[0].quadratic, 0, 2.0f);
                ImGui::SliderFloat("Ambient", &mat.ambientStrength, 0, 5);
                ImGui::SliderFloat("diffuse", &mat.diffuseStrength, 0, 5);
                ImGui::SliderFloat("specular", &mat.specularStrength, 0, 5);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            } */
            //gui element 

            s.Bind();
           // CubedepthTexture.Bind(11);

            directional.BindShadowMapTexture();
            s.setUniformMat4f("lightSpaceMatrix", directional.getLightSpaceMatrix());



            scene.Render();
            scene.Update(window);

            fbR.UnBind();




            fbR.Draw();


            Renderer::GetInstance()->EndRendering(window);

        }
        //delete obj;
        //scene.End();
    }
    

    Renderer::GetInstance()->ShutDownRendering();
    return 0;
}
