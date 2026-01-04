#pragma once
#include "Weapon.h"
#include "Bullet.h"
class RangedWeapon : public Weapon
{
private:
	glm::vec3 m_shotPoint;
public:
	RangedWeapon(float damange, float delay, float range);
	~RangedWeapon();

	void Shoot();

	void Update() override;
	void ProcessInput(Window* wnd, float dt) override;
};

