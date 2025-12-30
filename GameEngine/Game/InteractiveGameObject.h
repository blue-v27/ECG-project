#pragma once
#include "GameObject.h"
class InteractiveGameObject : public GameObject
{
private:
	bool m_pickable = false;
public:
	InteractiveGameObject();

	void IsPickable(bool val);
	bool IsPickable()		  { return m_pickable; }

	InteractiveGameObject* AsGameObject() { return this; }
};

