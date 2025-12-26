#include "SceneEditorSubMode.h"

void SceneEditorSubMode::Init()
{
	m_objPlacer = new ObjectPlacer();
	CAMERA.FreeCam(true);
	m_isActive = true;
}

void SceneEditorSubMode::Stop()
{
	CAMERA.FreeCam(false);
	m_isActive = false;
	delete m_objPlacer;
	m_objPlacer = nullptr;
}

void SceneEditorSubMode::ToggleEditMode()
{
	if (!m_isActive)
		Init();
	else
		Stop();
}
