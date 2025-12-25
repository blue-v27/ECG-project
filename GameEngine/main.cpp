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

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

Window window("Game Engine", 800, 800);
Camera camera;

glm::vec3 lightColor = glm::vec3(1.0f);
glm::vec3 lightPos   = glm::vec3(-180.0f, 100.0f, -200.0f);

int main()
{
	glClearColor(0.2f, 0.8f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	GAMECONTEXT.SetWindow(&window);
	GAMECONTEXT.SetCamera(&camera);

	Player* player = new Player();
	player->SetPos(glm::vec3(0.f, 10.f, 0.f));
	player->SetCamera(&camera);
	player->GetCamera()->SetPos(glm::vec3(0.0f, 7.f, 2.4f));
	player->Init(MeshDefines::cube);
	player->InitPhysics();
	GAMECONTEXT.AddPlayer(player);
	GAMECONTEXT.AddObject(player);
	GAMECONTEXT.AddObject(&camera);

	GameObject* plane = new GameObject();
	plane->SetTexture(TextureDefine::Rock);
	plane->Init(MeshDefines::plane);
	plane->SetScale(glm::vec3(10.f, 1.f, 10.f));
	plane->SetPos(glm::vec3(0.f, 0.f, 0.f));
	GAMECONTEXT.AddObject(plane);

#if 0
	Water* water = new Water();
	water->Init();
	water->SetScale(glm::vec3(1.f, 1.f, 1.f));
	water->SetPos(glm::vec3(-450.f, 0.f, 0.f));
	GAMECONTEXT.AddObject(water);

	GameObject* box = new GameObject();
	box->SetTexture(TextureDefine::Wood);
	box->Init(MeshDefines::cube);
	box->SetScale(glm::vec3(1.f, 1.f, 1.f));
	box->SetPos(glm::vec3(0.f, 1.f, 0.f));
	GAMECONTEXT.AddObject(box);
#endif

	while (!window.isPressed(GLFW_KEY_ESCAPE) && glfwWindowShouldClose(window.getWindow()) == 0)
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

		window.update();
	}
}
