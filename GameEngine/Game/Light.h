#pragma once
#include "InteractiveGameObject.h"

class Light : public InteractiveGameObject
{
private:
	float m_intensity;
	float m_difCoef;
	float m_specIntensity;
	glm::vec4 m_lightColor;
public:
	Light();
	~Light() = default;

	void  SetIntensity(float val) { m_intensity = val; }
	float GetIntensity()		  { return m_intensity; }

	void  SetDifCoef(float val) { m_difCoef = val; }
	float GetDifCoef()			{ return m_difCoef; }

	void  SetSpecIntensity(float val) { m_specIntensity = val; }
	float GetSpecIntensity()		  { return m_specIntensity; }

	void	  SetLightColor(glm::vec4 col) { m_lightColor = col; }
	glm::vec4 GetLightColor()			   { return m_lightColor; }

};

