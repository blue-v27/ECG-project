#pragma once

#include <glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

struct LightUniform
{
	GLint color;
	GLint position;
	GLint ka;
	GLint kd;
	GLint ks;
};

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	void use();
	int getId();

	void UseLights(bool val) { m_useLight = val; }
	bool UseLights()		 { return m_useLight; }

	void CacheLights(int maxLights);
	void UpdateLights();

	std::vector<LightUniform> m_lights;
	
	GLint m_viewPos;
	GLint m_numLights;
private:
	unsigned int id;
	bool	     m_useLight;
	
};

