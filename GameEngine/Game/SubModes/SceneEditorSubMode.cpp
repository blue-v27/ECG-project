#include "SceneEditorSubMode.h"
#include "../SaveManager.h"

void SceneEditorSubMode::Init()
{
	m_objPlacer = new ObjectPlacer();
	m_cameraRot = CAMERA.GetRotation();
	CAMERA.FreeCam(true);
	m_isActive = true;
}

void SceneEditorSubMode::Stop()
{
	CAMERA.FreeCam(false);
	CAMERA.SetRotatation(m_cameraRot);
	CAMERA.SetRotatation(GAMECONTEXT.GetPlayer()->m_rotationOx, GAMECONTEXT.GetPlayer()->m_rotationOy);
	CAMERA.UpdateVectors();
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

void SceneEditorSubMode::Update()
{
	if (m_isActive)
	{
		RenderGhost();
		m_objPlacer->Update();

		if (GAMECONTEXT.GetWindow()->IsReleased(GLFW_KEY_UP))
			SAVE_MANAGER.SaveObjects();
	}
}

void SceneEditorSubMode::RenderGhost()
{
	if (m_isActive)
	{
		if (m_objPlacer)
			m_objPlacer->RenderGhost();
	}
}
