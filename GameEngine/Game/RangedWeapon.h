#pragma once
#include "Weapon.h"
#include "Bullet.h"
class RangedWeapon : public Weapon
{
private:
	glm::vec3 m_shotPoint;

	Shader* m_lineShader = nullptr;
	Bullet* m_bullet     = nullptr;
public:
	RangedWeapon(float damange, float delay, float range);
	~RangedWeapon();

	void Shoot();

	void GrabAnchor();

	void Update() override;
	void ProcessInput(Window* wnd, float dt) override;
	void RenderLine();
	void Render() override;
};

