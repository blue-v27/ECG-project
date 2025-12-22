#pragma once

#include "GameObject.h"

class Water : public GameObject
{
private:
	float m_waveHeight;
	float m_waveLength;
	float m_waveSpeed;
public:

	Water();

	
	void Init(char* mesh = nullptr) override;
	void Render() override;

};

