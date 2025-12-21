#pragma once

#include <glm.hpp>
#include <gtx\transform.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include "..\Graphics\window.h"
#include "..\Model Loading\mesh.h"
#include "..\Model Loading\texture.h"
#include "..\Model Loading\meshLoaderObj.h"
#include "..\Model Loading\MeshDefines.h"
#include "..\Shaders\shader.h"
#include "vector"
#include "PhysicsMask.h"

class IGameObject
{
private:

public:

	IGameObject();

	virtual void ProcessInput(Window* window, float deltaTime) = 0;
	virtual void Update() = 0;
	virtual void Init(char* mesh = nullptr) = 0;
	virtual void Render() = 0;

	void IProcessInput(Window* window, float deltaTime);
	void IUpdate();
	void IInit(char* mesh = nullptr);
	void IRender();
};