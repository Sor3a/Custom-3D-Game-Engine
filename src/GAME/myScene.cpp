#include "myScene.h"
#include "../SpeeDEngine/GameObjectManager.h"


void myScene::Start(Shader* s)
{
    glm::vec3 positions1[] = {
              glm::vec3(0,-2,  -290),
              glm::vec3(-3,0,  -40),
              glm::vec3(-5,0,  -30.0f),
              glm::vec3(4.5f, 0,  -86.0f),
              glm::vec3(2,0,  -55),
              glm::vec3(5.5f,0,  -150.0f),
              glm::vec3(-1.5f,0,  -90.0f),
              glm::vec3(9.0f, 0,  -200.0f),

              glm::vec3(3,0,  -200),
              glm::vec3(-5,0,  -230.0f),
              glm::vec3(6.5f, 0,  -186.0f),
              glm::vec3(4,0,  -155),
              glm::vec3(-5.5f,0,  -250.0f),
              glm::vec3(-1.5f,0,  -190.0f),
              glm::vec3(5.0f, 0,  -23.0f),

              glm::vec3(0,0,  -510),
              glm::vec3(-1,0,  -430.0f),
              glm::vec3(6.0f, 0,  -290.0f),
              glm::vec3(5,0,  -450),
              glm::vec3(5.5f,0,  -480.0f),
              glm::vec3(-5.5f,0,  -470.0f),
              glm::vec3(1.0f, 0,  -380.0f),

              glm::vec3(3,0,  -530),
              glm::vec3(-2,0,  -490.0f),
              glm::vec3(-3.0f, 0,  -340.0f),
              glm::vec3(-3,0,  -560),
              glm::vec3(0.5f,0,  -460.0f),
              glm::vec3(-2.5f,0,  -365.0f),
              glm::vec3(-3.0f, 0,  -477.0f),
              
              glm::vec3(0.5f,0,  -520.0f),
              glm::vec3(-6.5f,0,  -565.0f),
              glm::vec3( 3.0f, 0,  -560.0f),
    };
    std::vector<std::string> faces =
    {
        "res/textures/sky/right.jpg",
            "res/textures/sky/left.bmp",
            "res/textures/sky/top.bmp",
            "res/textures/sky/bottom.bmp",
            "res/textures/sky/front.bmp",
            "res/textures/sky/back.bmp"
    };
    
    camera = new Camera();
    sky = new SkyBox(faces);
    
    BoxesMaterials = new Material(glm::vec4(0.8, 0.1, 0.0, 1));

    
    for (size_t i = 0; i < 30; i++)
    {
        objects.emplace_back(new GameObject(BoxesMaterials, s, &cube_, positions1[i+1]));
        objects[i]->setScale(glm::vec3(2, 1, 1));
        //objects[i]->setRotation(glm::normalize(glm::vec3(i, 1, 0.5 * i)), i * 20.0f);
    }
    planeMaterial = new Material(glm::vec4(0.2, 0.5, 0.2, 1));
    plane = new GameObject(planeMaterial,s, &cube_, positions1[0]);
    plane->setScale(glm::vec3(8, 1, 300));
    playerMaterial = new Material(glm::vec4(0.1, 0.6, 0.4, 1));
    player = new GameObject(playerMaterial, s, &cube_,glm::vec3(0,-0.5f,50));
   /// objects[0] = new GameObject();
    forwardSpeed = 10;
    playerSpeed = 20;
    playerSpeedMax = 50;
    player->scale = glm::vec3(0.5f);

    camera->cameraPos += glm::vec3(0, 2.5f, 0);
    camera->SetCameraSpeed(10);

}

void myScene::Render(Shader* s,glm::mat4 proj,glm::mat4 view)
{
    for (int i = 0; i < objects.size(); i++)
    {
        objects[i]->Draw(s, proj, view);
    }
    plane->Draw(s, proj, view);
    player->Draw(s, proj, view);
    sky->Draw();
}


void myScene::Update(GLFWwindow* window)
{
    camera->CameraWork();
    if (player->getActive() == true) //if the player is still alive
    {
        glm::vec3 direction = glm::vec3(camera->CameraForward.x, 0, camera->CameraForward.z); //get the direction of the player movement from the camera forward

        if (forwardSpeed < playerSpeedMax) //add the player speed if it's not maximum
            forwardSpeed += GameObjectManager::deltaTime * 3;

        player->position += forwardSpeed * GameObjectManager::deltaTime * direction * 0.1f; //move the player based on the speed and the direction

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
            if (player->position.x > -6.5f)  //move the player if he press A and still not in the edge of the plane
                player->position -= glm::normalize(glm::cross(camera->CameraForward, camera->cameraUp)) * playerSpeed * GameObjectManager::deltaTime;
        
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            if (player->position.x < 6.5f) //move the player if he press D and still not in the edge of the plane
            player->position += glm::normalize(glm::cross(camera->CameraForward, camera->cameraUp)) * playerSpeed * GameObjectManager::deltaTime;

        glm::vec3 cameraPos = camera->cameraPos; //get the camera position

        camera->cameraPos = glm::vec3(cameraPos.x, cameraPos.y, player->position.z + 10); // make the camera follow the player


        if (player->position.z < -590) // stop the game and let the player know that he win when he reaches the end
        {
            whatToShow = "you win";
            player->setActive(false);
            ImVec4 c(0, 0.8, 0, 1);
            color = c;
        }
        //(590 is the last point of the plane)

        for (int i = 0; i < objects.size(); i++) //detection for every object in the game if he hit or not
        {
            if (glm::abs(player->position.z - objects[i]->position.z) < 2.0f)
                if (glm::abs(player->position.x - objects[i]->position.x) < 2.1f)
                {
                    ImVec4 c(0.8, 0, 0, 1);
                    color = c;
                    whatToShow = "you lost";
                    std::cout << "collide :" << i << std::endl;
                    player->setActive(false);
                }
        }
    }
    else
        showWinLostUI(whatToShow); //tell the player if he win or lost
}

void myScene::showWinLostUI(std::string whatToShow)
{
    ImGui::Begin("Player Status");
    ImGui::SetWindowFontScale(3);
    ImVec2 WindowSize(200,100);
    ImGui::SetWindowSize(WindowSize);
    const char* c = whatToShow.c_str();

    ImGui::TextColored(color,c);
    
    ImGui::End();
}

void myScene::End()
{
    for (int i = 0; i < 6; i++)
    {
        delete objects[i];
    }
    delete plane;
    delete player;
    delete camera;

    //delete t1;
    //delete t2;

    delete planeMaterial;
    delete playerMaterial;
    delete BoxesMaterials;
}

myScene::~myScene()
{
    End();
}