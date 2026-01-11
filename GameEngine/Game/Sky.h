#pragma once
#include "fSingleton.h"
#include "../Model Loading/MeshDefines.h"
#include "../Model Loading/ShaderTypes.h"

class Sky : public fSingleton<Sky>
{
private:
	Shader* m_shader = nullptr;
	GLuint m_cubemapTexture;
	GLuint VAO, VBO;
public:
	void Start();
	void Render();
#define SKYBOX Sky::Instance()
};

