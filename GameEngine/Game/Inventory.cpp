#include "Inventory.h"

void Inventory::Drop(InteractiveGameObject* obj)
{
	if (obj->m_type == ObjectType::RangedWeapon)
		DropGun();
	else
		DropKnife();

}

void Inventory::Add(InteractiveGameObject* obj)
{
	if (obj->m_type == ObjectType::RangedWeapon)
		AddGun(dynamic_cast<RangedWeapon*>(obj));
	else
		AddKnife(dynamic_cast<Weapon*>(obj));
}

void Inventory::EquipKnife()
{
	if(m_knife)
		m_knife->m_isActive = true;

	if (m_gun)
		m_gun->m_isActive = false;
}

void Inventory::EquipGun()
{
	if (m_knife)
		m_knife->m_isActive = false;

	if (m_gun)
		m_gun->m_isActive = true;
}
