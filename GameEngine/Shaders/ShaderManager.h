#pragma once
#include "shader.h"
#include "../Model Loading/ShaderTypes.h"
#include "../Game/fSingleton.h"
#include <vector>

class ShaderManager : public fSingleton<ShaderManager>
{
private:
	std::vector<Shader*> m_shaders;
public:
	void    Start();
	void    Update();
	Shader* GetShader(int index) { return m_shaders.at(index); }

	int GetShaderCount() { return m_shaders.size(); }

#define SHADER_MANAGER ShaderManager::Instance()

#define BASIC 0
#define WATER 1
#define LINE  2
#define TEXT  3
#define GHOST 4
#define SUN   5
#define SKY   6
};

