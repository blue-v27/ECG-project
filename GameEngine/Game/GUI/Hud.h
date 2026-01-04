#pragma once
#include "../fSingleton.h"

class Hud : public fSingleton<Hud>
{
private:
	char* m_pistolImage		= "Resources/Images/hud_pistol.png";
	char* m_knifeImage		= "Resources/Images/hud_knife.png";
	char* m_crosshairImage  = "Resources/Images/hud_crosshair.png";

public:
	void Render();
#define HUD Hud::Instance()
};

