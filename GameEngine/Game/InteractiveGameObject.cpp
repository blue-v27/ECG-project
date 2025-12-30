#include "InteractiveGameObject.h"

void InteractiveGameObject::IsPickable(bool val)
{
	m_pickable = val;

	if (m_pickable)
	{		
		m_scale	= glm::vec3(0.1f);
	}
	else
	{
		m_scale = glm::vec3(1.f);
	}
}
