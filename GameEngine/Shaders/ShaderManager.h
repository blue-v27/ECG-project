#pragma once
#include "shader.h"
#include "../Model Loading/ShaderTypes.h"
#include "../Game/fSingleton.h"
#include <vector>
#include "../Game/DataSturctures/fArray.h"

class ShaderManager : public fSingleton<ShaderManager>
{
private:
	Array<Shader*> m_shaders;
public:
	void    Start();
	void    Update();
	Shader* GetShader(int index) { return m_shaders.GetAt(index); }

	int GetShaderCount() { return m_shaders.GetSize(); }

#define SHADER_MANAGER ShaderManager::Instance()

#define BASIC 0
#define WATER 1
#define LINE  2
#define TEXT  3
#define GHOST 4
#define SUN   5
#define SKY   6
#define BASICNOLIGHT 7
};

