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

#if 0
	Weapon* knife = new Weapon(10.f, 0.5f, 500.f);
	player->SetChild(knife);
	knife->SetPos(glm::vec3(0.0f, 7.f, 1.f));
	knife->SetRotation(glm::quat(0.70710678f, 0.70710678f, 0.0f, 0.0f));
	knife->SetScale(glm::vec3(0.25f));
	knife->Init(&MESH_DEFINES.GetMesh(MESH_KNIFE));
	GAMECONTEXT.AddObject(knife);
#endif

	RangedWeapon* weapon = new RangedWeapon(10.f, 0.5f, 300.f);
	player->SetChild(weapon);
	weapon->SetPos(glm::vec3(0.0f, -1.f, 4.f));
	weapon->RotateX(90.f);
	weapon->RotateZ(-90.f);
	weapon->SetScale(glm::vec3(0.25f));
	weapon->Init(&MESH_DEFINES.GetMesh(MESH_PISTOL));
	GAMECONTEXT.AddInteractiveGameObject(weapon);


	GameObject* anchor = new GameObject();
	anchor->SetPos(glm::vec3(0.f, 70.f, 0.f));
	anchor->Init(&MESH_DEFINES.GetMesh(MESH_BOX));
	anchor->IsAnchor(true);
	GAMECONTEXT.AddObject(anchor);

	GameObject* anchor1 = new GameObject();
	anchor1->SetPos(glm::vec3(50.f, 70.f, 0.f));
	anchor1->Init(&MESH_DEFINES.GetMesh(MESH_BOX));
	anchor1->IsAnchor(true);
	GAMECONTEXT.AddObject(anchor1);

	GameObject* anchor2 = new GameObject();
	anchor2->SetPos(glm::vec3(100.f, 70.f, 0.f));
	anchor2->Init(&MESH_DEFINES.GetMesh(MESH_BOX));
	anchor2->IsAnchor(true);
	GAMECONTEXT.AddObject(anchor2);

	Light* light = new Light();
	light->SetPos(glm::vec3(200.f, 150.f, 100.f));
	light->SetShaderId(BASIC);
	light->Init(&MESH_DEFINES.GetMesh(MESH_SUN));
	light->SetColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
	//light->IsSun(true);
	GAMECONTEXT.SetLight(light);

	//Light* light2 = new Light();
	//light2->SetPos(glm::vec3(100.f, 75.f, 0.f));
	//light2->Init(&MESH_DEFINES.GetMesh(MESH_SUN));
	//light2->SetColor(glm::vec4(1.f, 0.f, 0.f, 1.f));
	//GAMECONTEXT.SetLight(light2);

	GUI.Init();
	GAMECONTEXT.InitLights();

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