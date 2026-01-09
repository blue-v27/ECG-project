#include "Light.h"

Light::Light()
{
	m_intensity     = 0.1f;
	m_difCoef       = 1.f;
	m_specIntensity = 0.5f;
	m_lightColor    = glm::vec4(1.f);
	m_isSun			= false;
}

void Light::Update()
{
	if (m_isSun)
	{
		m_pos.y = 200.f * glm::sin(glfwGetTime());
		m_pos.x = 200.f * glm::cos(glfwGetTime());
	}
	InteractiveGameObject::Update();
}
