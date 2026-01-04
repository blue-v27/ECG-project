#pragma once
#include "GameObject.h"
class InteractiveGameObject : public GameObject
{
private:
	bool m_pickable = false;
	bool m_shoudlBePicked = false;
public:
	InteractiveGameObject();

	void IsPickable(bool val);
	bool IsPickable()		  { return m_pickable; }
	void PickUp(GameObject* other);

	bool HandleIntersection(GameObject* other, glm::vec3&velocity = glm::vec3(100.f));

	void Update() override;

	InteractiveGameObject* AsGameObject() { return this; }
};

