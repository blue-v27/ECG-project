#include "InteractiveGameObject.h"

InteractiveGameObject::InteractiveGameObject()
{
	m_pickable = false;
	m_shoudlBePicked = false;
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
			PickUp(other);

		return true;
	}

	return false;
}

void InteractiveGameObject::PickUp(GameObject* other)
{
	if (m_pickable)
	{
		DisablePhysics();
		other->SetChild(this->AsGameObject());
		m_pickable = false;
	}
}

void InteractiveGameObject::Update()
{
	GameObject::Update();
}
