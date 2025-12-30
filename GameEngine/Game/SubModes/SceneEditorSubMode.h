#pragma once

#include "..\ObjectPlacer.h"
#include "..\fSingleton.h"
class SceneEditorSubMode : public fSingleton<SceneEditorSubMode>
{
private:
	ObjectPlacer* m_objPlacer = nullptr;
	bool	      m_isActive  = false;
public:
	void IsActive(bool val) { m_isActive = val; }
	bool IsActive()			{ return m_isActive; }
	void Init();
	void Stop();
	void ToggleEditMode();
	void Update();
	void RenderGhost();

#define SCENE_EDITOR SceneEditorSubMode::Instance()
};

