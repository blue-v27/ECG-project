#include "InteractiveGameObject.h"
#include "Inventory.h"

InteractiveGameObject::InteractiveGameObject()
{
	m_pickable       = false;
	m_shoudlBePicked = false;
}

void InteractiveGameObject::IsPickable(bool val)
{
	m_pickable = val;

	if (m_pickable)
	{		
		if(m_type == ObjectType::Watch)
			m_scale	= glm::vec3(1.f);
		else
			m_scale = glm::vec3(0.25f);
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
		{
			PickUp(other);
			INVETORY.Add(this);
		}
			

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
		m_rot = glm::quat(0.f, 0.f, 0.f, 0.f);
		m_relativeRot = glm::quat(0.f, .71f, 0.71f, 0.f);
	}
}

void InteractiveGameObject::Update()
{
	GameObject::Update();

	if (m_pickable)
	{
		RotateY(0.1f);
		RotateZ(0.1f);
		RotateX(0.1f);
	}
		
}
