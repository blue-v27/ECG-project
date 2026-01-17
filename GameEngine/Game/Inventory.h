#pragma once
#include "RangedWeapon.h"
#include "fSingleton.h"

class Inventory : public fSingleton<Inventory>
{	
private:
	RangedWeapon* m_gun   = nullptr;
	Weapon*		  m_knife = nullptr;

public:
	void AddGun(RangedWeapon* gun);
	void DropGun()				   { m_gun = nullptr; if (m_knife) m_knife->m_isActive = true; }
		
	void AddKnife(Weapon* knife) { m_knife = knife; if (m_gun) m_gun->m_isActive  = false; }
	void DropKnife()			 { m_knife = nullptr;if (m_gun) m_gun->m_isActive = true; }

	void Drop(InteractiveGameObject* obj);
	void Add(InteractiveGameObject* obj);

	void EquipKnife();
	void EquipGun();

	RangedWeapon* GetWeapon() { return m_gun; }
	Weapon*		  GetKnife() { return m_knife; }

	

#define INVETORY Inventory::Instance()
};

