#pragma once

#include "..\ObjectPlacer.h"
class SceneEditorSubMode
{
private:
	SceneEditorSubMode() = default;
	~SceneEditorSubMode() = default;

	ObjectPlacer* m_objPlacer = nullptr;
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

	void Init();

#define SCENE_EDITOR SceneEditorSubMode::Instance()
};

