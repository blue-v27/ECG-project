#include "ShaderManager.h"

void ShaderManager::Start()
{
	m_shaders.push_back(new Shader(ShaderTypes::basicVertex, ShaderTypes::basicFragment));
	m_shaders.push_back(new Shader(ShaderTypes::waterVertex, ShaderTypes::waterFragment));
	m_shaders.push_back(new Shader(ShaderTypes::lineVertex,  ShaderTypes::lineFragment));
	m_shaders.push_back(new Shader(ShaderTypes::textVertex,  ShaderTypes::textFragment));
	m_shaders.push_back(new Shader(ShaderTypes::ghostVertex, ShaderTypes::ghostFragment));
	m_shaders.push_back(new Shader(ShaderTypes::sunVertex,   ShaderTypes::sunFragment));
	m_shaders.push_back(new Shader(ShaderTypes::skyVertex,   ShaderTypes::skyFragment));
	m_shaders.push_back(new Shader(ShaderTypes::basicNoLightVertex, ShaderTypes::basicNoLightFragment));

	GetShader(BASIC)->UseLights(true);
	GetShader(WATER)->UseLights(true);
}

void ShaderManager::Update()
{
	int numShader = m_shaders.size();

	for (int i = 0; i < numShader; ++i)
	{
		//update shader
	}
}
