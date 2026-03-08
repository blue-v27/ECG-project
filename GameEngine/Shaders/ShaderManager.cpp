#include "ShaderManager.h"
#include "../Game/GameContext.h"

void ShaderManager::Start()
{
	m_shaders.PushLast(new Shader(ShaderTypes::basicVertex, ShaderTypes::basicFragment));
	GAMECONTEXT.AddShderBatch(m_shaders.GetLast());
	m_shaders.PushLast(new Shader(ShaderTypes::waterVertex, ShaderTypes::waterFragment));
	GAMECONTEXT.AddShderBatch(m_shaders.GetLast());
	m_shaders.PushLast(new Shader(ShaderTypes::lineVertex,  ShaderTypes::lineFragment));
	GAMECONTEXT.AddShderBatch(m_shaders.GetLast());
	m_shaders.PushLast(new Shader(ShaderTypes::textVertex,  ShaderTypes::textFragment));
	GAMECONTEXT.AddShderBatch(m_shaders.GetLast());
	m_shaders.PushLast(new Shader(ShaderTypes::ghostVertex, ShaderTypes::ghostFragment));
	GAMECONTEXT.AddShderBatch(m_shaders.GetLast());
	m_shaders.PushLast(new Shader(ShaderTypes::sunVertex,   ShaderTypes::sunFragment));
	GAMECONTEXT.AddShderBatch(m_shaders.GetLast());
	m_shaders.PushLast(new Shader(ShaderTypes::skyVertex,   ShaderTypes::skyFragment));
	GAMECONTEXT.AddShderBatch(m_shaders.GetLast());
	m_shaders.PushLast(new Shader(ShaderTypes::basicNoLightVertex, ShaderTypes::basicNoLightFragment));
	GAMECONTEXT.AddShderBatch(m_shaders.GetLast());

	GetShader(BASIC)->UseLights(true);
	GetShader(WATER)->UseLights(true);
}

void ShaderManager::Update()
{
	int numShader = m_shaders.GetSize();

	for (int i = 0; i < numShader; ++i)
	{
		//update shader
	}
}
