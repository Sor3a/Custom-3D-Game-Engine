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

#include "VertexBuffer_Layout/VertexBuffer.h"
#include"Renderer/Renderer.h"
#include "Texture/Texture.h"
#include "SpeeDEngine/GameObjectManager.h"
#include "Camera/Camera.h"
#include "Primitives/Primitives.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "LightingObject/LightingObject.h"
#include "LightingObject/PointLight/PointLight.h"
#include "LightingObject/DirectionalLight/DirectionalLight.h"
#include "LightingObject/FlashLight/FlashLight.h"
#include "Material/Material.h"
#include "Model/Model.h"
#include <map>
#include "FrameBuffer/FrameBuffer.h"
#include "FrameBuffer/RenderBufferObject.h"
#include "Texture/CubeTexture.h"
#include "SkyBox/SkyBox.h"
#include"../vendor/stb_Image/stb_Image.h"
#include"UniformBufferObject/UniformBufferObject.h"
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
        float skyboxVertices[] =
        {
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

        unsigned int skyboxIndices[] =
        {
            // Right
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


        glfwSwapInterval(1);
        float vertices[] = {
        -1, -1, 0,0,//0 
         -0.5,-1,1,0,//1
        -1,-0.5,0,1,//2
         -0.5,-0.5,1,1,//3

        };
        glm::vec3 positions1[] = {
            glm::vec3(0,-2,  5),
              glm::vec3(2.5f,2,  4.0f),
              glm::vec3(-3.5f,0.2,  3.0f),
              glm::vec3(15.5f, 1.5,  -2.0f),
              glm::vec3(13,6,  1),
              glm::vec3(8.5f,0.5,  8.0f),
             glm::vec3(-1.5f,0.5,  -9.0f),
              glm::vec3(9.0f, 1,  -1.0f),
        };
        glm::vec3 lighPositions[] = {
            glm::vec3(17,1,  -10),
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

        std::vector<Texture_> textures;

        Texture texture("res/textures/texture3.png", "texture_diffuse", GL_LINEAR, GL_CLAMP_TO_BORDER, nullptr, GL_NEAREST_MIPMAP_LINEAR);
        Texture texture1("res/textures/texture4.png", "texture_specular", GL_LINEAR, GL_CLAMP_TO_BORDER, nullptr, GL_NEAREST_MIPMAP_LINEAR);
        textures.emplace_back(texture.GetID(), texture.GetType());
        textures.emplace_back(texture1.GetID(), texture1.GetType());



        Material mat(textures);
        Material grassMat;
        grassMat.Color = glm::vec4(0.2, 0.5, 0.1, 0.6);

        Renderer::GetInstance()->Blend();

        GameObjectManager manager;
        Camera camera;
        Cube cube_;

        //glDepthMask(GL_FALSE);

        GameObject objects[7] =
        {
        GameObject(&mat,&s,&cube_,positions1[1]),
        GameObject(&mat,&s,&cube_,positions1[2]),
        GameObject(&mat,&s,&cube_,positions1[3]),
        GameObject(&mat,&s,&cube_,positions1[4]),
        GameObject(&mat,&s,&cube_,positions1[5]),
        GameObject(&mat,&s,&cube_,positions1[6]),
        GameObject(&mat,&s,&cube_,positions1[7]),
        };




        PointLight PointsLights[4] = {
            PointLight(&s1, &cube_,lighPositions[0],glm::vec3(0.1f),glm::vec3(2)),
             PointLight(&s1, &cube_,lighPositions[1],glm::vec3(0.1f),glm::vec3(2)),
              PointLight(&s1, &cube_,lighPositions[2],glm::vec3(0.1f)),
               PointLight(&s1, &cube_,lighPositions[3],glm::vec3(0.1f),glm::vec3(2)),
        };


        // Enables Cull Facing

        // Keeps front faces

        //for (int i = 0; i < 4; i++)
        //    PointsLights[i]= ;

        Material material(glm::vec4(0.2, 0.5, 0.2, 1));
        GameObject obj(&material, &s, &cube_, positions1[0]);
        //LightingObject Lighting_obj(glm::vec3(1, 1, 1),&s1, &cube_light,positions1[1]);

        DirectionalLight directional(glm::vec3(2.0f, -1.0f, 1.0f), nullptr, glm::vec3(0.3f), glm::vec3(0.8), glm::vec3(0.8));


        // pointLight(&s1, &cube_,glm::vec3(2,3,3));
        FlashLight flashLight(10, 13, glm::vec3(0), glm::vec3(0.1f), glm::vec3(0.3f), glm::vec3(0.5f));
        //std::cout << obj << std::endl;
        camera.SetCameraSpeed(10);
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



        GameObject m("res/3dModels/obj2/backpack.obj", &s);



        //Creating the Quade that we will dispose everything on it later
        Shader s_Quade("res/shaders/basic3.shader");
        s_Quade.setUniform1i("screenTexture", 0);
        float quadVertices[] = {
            // positions // texCoords
            -1.0f, 1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f
        };
        VertexArray quadeArray;
        VertexBuffer quadeBuffer(quadVertices, 6 * 4 * sizeof(float));
        VertexBufferLayout quadeLayout;
        quadeLayout.push<float>(2);
        quadeLayout.push<float>(2);
        quadeArray.AddBuffer(quadeBuffer, quadeLayout);


        //creation of the frame buffer
        FrameBuffer fb;
        Texture screenTexture(NULL);
        RenderBufferObject rbo;
        rbo.DepthStencilRBO();
        fb.AttachTexture(screenTexture.GetID());
        fb.AttachRBO_Depth_Stencil(rbo.getID());
        fb.CheckIfComplete();


        std::vector<std::string> faces =
        {
            "res/textures/sky/right.jpg",
                "res/textures/sky/left.bmp",
                "res/textures/sky/top.bmp",
                "res/textures/sky/bottom.bmp",
                "res/textures/sky/front.bmp",
                "res/textures/sky/back.bmp"
        };

        CubeTexture SkyTexture(faces);
        SkyBox sky(SkyTexture);
        s.setUniform1i("skybox", 2);
        SkyTexture.Bind(2);



        fb.UnBind();


        Shader TriangleShader("res/shaders/normal.shader");
        TriangleShader.setUniformVec4f("color", glm::vec4(0.5, 0.2, 0, 1));
        float triangleVertices[] =
        {
            0.0f, 0.0f,
            0.5f, 0.0f,
            0.5f, 0.5f,
        };
        VertexArray TriangleArray;
        VertexBuffer TriangleBuffer(quadVertices, sizeof(triangleVertices));
        VertexBufferLayout TriangleLayout;
        TriangleLayout.push<float>(2);
        TriangleArray.AddBuffer(TriangleBuffer, TriangleLayout);



        FrameBuffer depthFBO;
        DepthTexture depthTexutre;
        depthFBO.AttachDepthTexture(depthTexutre.GetID());
        depthFBO.CheckIfComplete();

        float near_plane = 1.0f, far_plane = 7.5f;

        glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f,
            near_plane, far_plane);
        glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f,4.0f, -1.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f));

        Shader shadowShader("res/shaders/shadowShader.shader");

        s.setUniform1i("shadowMap", 10);
        //glEnable(GL_FRAMEBUFFER_SRGB); //gamma correction
        while (!glfwWindowShouldClose(window))
        {

            Renderer::GetInstance()->StartRenderingImGui();
            /* Render here */



            manager.CalculateDeltaTime();


            camera.CameraWork();
            camera.CameraMoveWithInput(window);
            directional.setShaderVariables(&s);


            //if (flashLight.direction != camera.CameraForward)
            //    flashLight.direction = camera.CameraForward;
            //flashLight.setPosition(camera.cameraPos);
            //flashLight.setShaderVariables(&s);


            s.setUniformVec3f("viewPos", camera.cameraPos);



            glViewport(0, 0, 1024, 1024);
            depthFBO.Bind();
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            Renderer::GetInstance()->Clear();
            Renderer::GetInstance()->Enable();


            //drawing objects
            for (int i = 0; i < 7; i++)
            {
                objects[i].setRotation(glm::normalize(glm::vec3(i, 1, 0.5 * i)), i * 20.0f);

                objects[i].Draw(&shadowShader, lightProjection, lightView);
            }
            obj.setScale(glm::vec3(20, 1, 20));
            obj.Draw(&shadowShader,lightProjection,lightView);

            //sky.Draw(); //draw sky


           // glDisable(GL_FRAMEBUFFER_SRGB);
            // draw the biggest Texture
            depthFBO.UnBind();




            glViewport(0, 0, 1280, 720);
            fb.Bind();
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            Renderer::GetInstance()->Clear();
            Renderer::GetInstance()->Enable();

            {


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
            }
            //gui element 

            s.Bind();
            depthTexutre.Bind(10);
            s.setUniformMat4f("lightSpaceMatrix", lightProjection * lightView);
            //drawing lights
            for (int i = 0; i < 4; i++)
            {
                PointsLights[i].Draw();
                PointsLights[i].assignVariablesToShader(&s, i);
            }

            //drawing objects
            for (int i = 0; i < 7; i++)
            {
                objects[i].setRotation(glm::normalize(glm::vec3(i, 1, 0.5 * i)), i * 20.0f);

                objects[i].Draw();
            }
            obj.setScale(glm::vec3(20, 1, 20));
            //obj.SetPosition(glm::vec3(0,-5,0));
            obj.Draw();

            sky.Draw(); //draw sky


           // glDisable(GL_FRAMEBUFFER_SRGB);
            // draw the biggest Texture
            fb.UnBind();






            glDisable(GL_DEPTH_TEST);
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            //Renderer::GetInstance()->Clear();
            s_Quade.Bind();

            screenTexture.Bind();
            Renderer::GetInstance()->Draw(quadeArray);
            //end of the draw of the biggest texture


            //Renderer::GetInstance()->Disable();
            //TriangleShader.Bind();
            //Renderer::GetInstance()->Draw(TriangleArray);

            Renderer::GetInstance()->EndRendering(window);

        }
        //delete obj;
    }

    Renderer::GetInstance()->ShutDownRendering();
    return 0;
}
