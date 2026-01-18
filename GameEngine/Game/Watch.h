#pragma once
#include "Weapon.h"
class Watch : public Weapon
{
public:
	Watch();
	~Watch() = default;

	void ProcessInput(Window* window, float deltaTime) override;
	void Render() override;
};

