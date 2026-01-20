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

	/*Weapon* knife = new Weapon(10.f, 0.5f, 500.f);
	player->SetChild(knife);
	knife->SetPos(glm::vec3(0.0f, 7.f, 1.f));
	knife->SetRotation(glm::quat(0.70710678f, 0.70710678f, 0.0f, 0.0f));
	knife->SetScale(glm::vec3(0.25f));
	knife->Init(&MESH_DEFINES.GetMesh(MESH_KNIFE));
	GAMECONTEXT.AddInteractiveGameObject(knife);
	INVETORY.AddKnife(knife);*/

	Light* light = new Light();
	light->SetPos(glm::vec3(200.f, 150.f, 100.f));
	light->SetShaderId(BASIC);
	//light->Init(&MESH_DEFINES.GetMesh(MESH_SUN));
	light->SetColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
//	light->IsSun(true);
	GAMECONTEXT.SetLight(light);

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