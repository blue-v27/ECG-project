#include "GameContext.h"

IGameObject::IGameObject()
{
	m_pos			= glm::vec3(0);
	m_scale			= glm::vec3(1);
	m_viewDirection = glm::vec3(0);
	m_up			= glm::vec3(0);
	m_right			= glm::vec3(0);

	m_rotationOx = 0.0f;
	m_rotationOy = -90.0f;

	m_parent = nullptr;
	m_mass = 10;
}

void IGameObject::IProcessInput(Window* window, float deltaTime)
{
	ProcessInput(window, deltaTime);
}

void IGameObject::IUpdate()
{
	if (m_phyMask)
		m_phyMask->UpdatePhysics();

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
