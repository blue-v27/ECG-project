#pragma once
#include "InteractiveGameObject.h"

class Inventory
{	
private:
	std::vector<InteractiveGameObject*> m_items;
	int m_slots[4][4];
public:
	Inventory();
	~Inventory();

	void AddItem(InteractiveGameObject* item);
	void RemoveItem(InteractiveGameObject* item);
	void RemoveItem(int i1, int i2);

};

