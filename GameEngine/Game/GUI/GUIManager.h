#pragma once

#include <glm.hpp>
#include <gtx\transform.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include "../fSingleton.h"

class GUIManager : public fSingleton<GUIManager>
{
public:

	void DrawText(float x, float y, const char* text);

#define GUI GUIManager::Instance()
};

