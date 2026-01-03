#include "Hud.h"
#include "GUIManager.h"

void Hud::Render()
{
	GUI.DrawImage("Resources/Images/hud_knife.png", 1100.f, 20.f, 2.0f);
	GUI.DrawImage("Resources/Images/hud_pistol.png", 1100.f, 100.f, 2.0f);
}
