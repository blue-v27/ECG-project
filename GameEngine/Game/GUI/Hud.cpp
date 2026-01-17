#include "Hud.h"
#include "GUIManager.h"
#include "../Inventory.h"

void Hud::Render()
{
	if(INVETORY.GetKnife())
		GUI.DrawImage(m_knifeImage, 1100.f, 20.f, 2.0f);

	if(INVETORY.GetWeapon())
		GUI.DrawImage(m_pistolImage, 1100.f, 100.f, 2.0f);

	GUI.DrawImage(m_crosshairImage, 640.f, 360.f, 0.1f);
}
