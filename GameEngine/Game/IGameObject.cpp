#include "GameContext.h"

IGameObject::IGameObject()
{

}

void IGameObject::IProcessInput(Window* window, float deltaTime)
{
	ProcessInput(window, deltaTime);
}

void IGameObject::IUpdate()
{
	Update();
}

void IGameObject::IInit(char* mesh)
{
	Init(mesh);
}

void IGameObject::IRender()
{
	Render();
}
