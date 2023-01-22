# Custom 3D Game Engine


The objective of this project was to enhance my graphics programming abilities and deepen my understanding of the underlying 
architecture and design patterns of game engines.

Currently, the application supports the following features: 
1) Instance Rendering 
2) Shadow Rendering
3) Lighting: Directional, point, and spotlight
4) Multitexturing
5) Normal Mapping 
 
## How to use it

In the folder GAME you will find ***myScene.h*** and ***myScene.cpp***

You can initialize everything you need in your game in ***myScene.h***.
Like objects, materials, textures, the sky, camera...
![image](https://user-images.githubusercontent.com/70980542/213930341-523c984d-efa2-4d98-8745-f8e1223c31fd.png)

and in the start and update and render functions in ***myScene.cpp*** you can set the logic of your game...

this is the Update function of the example game made with this engine.

```c++
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
```





















