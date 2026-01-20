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
#include "Game/Weapon.h"
#include "Game/RangedWeapon.h"
#include "Game/SaveManager.h"
#include "Game/Inventory.h"
#include "Game/Watch.h"

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

Window window("Game Engine", 1280, 720);

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
	player->Init(&MESH_DEFINES.GetMesh(MESH_CUBE));
	player->InitPhysics();
	GAMECONTEXT.AddPlayer(player);
	GAMECONTEXT.AddObject(player);

	SAVE_MANAGER.LoadInteractives();

	GUI.Init();
	GAMECONTEXT.InitLights();
	GAMECONTEXT.BuildOctree();

	while (!window.IsReleased(GLFW_KEY_ESCAPE) && glfwWindowShouldClose(window.getWindow()) == 0)
	{
		window.clear();
	
		float currentFrame = glfwGetTime();
		if(lastFrame)
			deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		GAMECONTEXT.SetDeltaTime(deltaTime);
		GAMECONTEXT.Update();
		GAMECONTEXT.Render();
		GAMECONTEXT.RemoveObject();

		window.update();
	}

	// Delete all objects from memory
	if(int size = GAMECONTEXT.GetObjectCount())
	{
		for(int i = 0; i < size; ++i)
			GAMECONTEXT.MarkForRemoval(GAMECONTEXT.GetObject(i));

		GAMECONTEXT.RemoveObject();
	}
}