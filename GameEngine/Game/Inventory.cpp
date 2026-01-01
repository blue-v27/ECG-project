#include "Inventory.h"

Inventory::Inventory()
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			m_slots[i][j] = 0;
}

Inventory::~Inventory()
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			m_slots[i][j] = 0;

	int numObj = m_items.size();
	for (int i = 0; i < numObj; ++i)
	{
		delete m_items.at(i);
		m_items.at(i) = nullptr;
	}

	m_items.clear();		
}

void Inventory::AddItem(InteractiveGameObject* item)
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			if (m_slots[i][j] != 0)
				m_items.push_back(item);
		}
}

void Inventory::RemoveItem(InteractiveGameObject* item)
{
}

void Inventory::RemoveItem(int i1, int i2)
{
}
