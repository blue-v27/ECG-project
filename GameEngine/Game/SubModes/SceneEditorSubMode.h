#pragma once

#include "..\ObjectPlacer.h"
class SceneEditorSubMode
{
private:
	SceneEditorSubMode() = default;
	~SceneEditorSubMode() = default;

	ObjectPlacer* m_objPlacer = nullptr;

	bool m_isActive = false;
public:

	static SceneEditorSubMode& Instance()
	{
		static SceneEditorSubMode instance;
		return instance;
	}

	SceneEditorSubMode(const SceneEditorSubMode&) = delete;
	SceneEditorSubMode& operator=(const SceneEditorSubMode&) = delete;
	SceneEditorSubMode(SceneEditorSubMode&&) = delete;
	SceneEditorSubMode& operator=(SceneEditorSubMode&&) = delete;

	void IsActive(bool val) { m_isActive = val; }
	bool IsActive()			{ return m_isActive; }

	void Init();
	void Stop();
	void ToggleEditMode();
	void Update();
	void RenderGhost();

#define SCENE_EDITOR SceneEditorSubMode::Instance()
};

