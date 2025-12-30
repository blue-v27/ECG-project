#include "InteractiveGameObject.h"

InteractiveGameObject::InteractiveGameObject()
{
	GameObject::GameObject();
}

void InteractiveGameObject::IsPickable(bool val)
{
	m_pickable = val;

	if (m_pickable)
	{		
		m_scale	= glm::vec3(0.25f);
	}
	else
	{
		m_scale = glm::vec3(1.f);
	}
}

bool InteractiveGameObject::HandleIntersection(GameObject* other, glm::vec3& velocity)
{
	if (other->m_boundingBox.HandleIntersection(other->m_pos, this->m_boundingBox, velocity))
	{
		if (m_pickable)
			m_shoudlBePicked = true;

		return true;
	}

	return false;
}

void InteractiveGameObject::Update()
{
	if (m_shoudlBePicked)
		m_scale = glm::vec3(0.f);
	GameObject::Update();
}
