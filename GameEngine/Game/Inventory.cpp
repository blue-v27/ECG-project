#include "Inventory.h"
#include "QuestManager.h"

void Inventory::AddGun(RangedWeapon* gun)
{
	m_gun = gun; 
	if (m_knife) 
		m_knife->m_isActive = false;

	if (QUEST_MANAGER.GetCurrentQuest() == 0)
		QUEST_MANAGER.CompleteQuest(0);
}

void Inventory::AddWatch(Watch* watch)
{
	m_watch = watch;

	if (QUEST_MANAGER.GetCurrentQuest() == 1)
		QUEST_MANAGER.CompleteQuest(1);
}

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
	else if (obj->m_type == ObjectType::Weapon)
		AddKnife(dynamic_cast<Weapon*>(obj));
	else
		AddWatch(dynamic_cast<Watch*>(obj));
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
