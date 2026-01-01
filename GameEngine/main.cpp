#include "Graphics\window.h"
#include "Camera\camera.h"
#include "Game\Player.h"
#include "Shaders\shader.h"
#include "Model Loading\mesh.h"
#include "Model Loading\texture.h"
#include "Model Loading\meshLoaderObj.h"
#include "Game/GameContext.h"
#include "Game/GameObject.h"
#include "Model Loading/ShaderTypes.h"
#include "Model Loading\TextureDefine.h"
#include "Game/Water.h"
#include "Game/InteractiveGameObject.h"
#include "Game/SubModes/SceneEditorSubMode.h"
#include "Game/GUI/GUIManager.h"

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

Window window("Game Engine", 800, 800);

glm::vec3 lightColor = glm::vec3(1.0f);
glm::vec3 lightPos   = glm::vec3(-180.0f, 100.0f, -200.0f);

int main()
{
	glClearColor(0.2f, 0.8f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	GAMECONTEXT.SetWindow(&window);
	GAMECONTEXT.SetCamera(&CAMERA);

	GAMECONTEXT.Start();

	Player* player = new Player();
	player->SetPos(glm::vec3(0.f, 10.f, 0.f));
	player->SetCamera(&CAMERA);
	player->GetCamera()->SetPos(glm::vec3(0.0f, 7.f, 2.4f));
	player->Init(&MESH_DEFINES.GetMesh(CUBE));
	player->InitPhysics();
	GAMECONTEXT.AddPlayer(player);
	GAMECONTEXT.AddObject(player);

	GUI.Init();

	while (!window.IsReleased(GLFW_KEY_ESCAPE) && glfwWindowShouldClose(window.getWindow()) == 0)
	{
		window.clear();

		float currentFrame = glfwGetTime();
		if(lastFrame)
			deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		GAMECONTEXT.SetDeltaTime(deltaTime);
		GAMECONTEXT.SetLightPos(lightPos);
		GAMECONTEXT.SetLightColor(glm::vec4(lightColor, 1));
		GAMECONTEXT.Update();
		GAMECONTEXT.Render();

		GUI.DrawText("HELLO WORLD!", 50.0f, 750.0f, 1.0f, glm::vec3(1.0f, 1.0f, 0.0f)); 		
		GUI.DrawImage("Resources/Images/test.png", 150.0f, 730.0f, 1.0f);

		window.update();

	}

	

	// Delete all objects from memory
	while(GAMECONTEXT.GetObjectCount())
	{
		if(GameObject* obj = GAMECONTEXT.GetObject(0))
			GAMECONTEXT.RemoveObject(obj);
	}
}