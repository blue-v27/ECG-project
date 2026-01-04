#pragma once
#include "InteractiveGameObject.h"
class Weapon : public InteractiveGameObject
{
public:
	float m_delay;
	float m_damage;
	float m_range;
	double m_time;
	bool m_canAttack;

	Weapon(float damage, float delay, float range);
	~Weapon();
	
	void Attack();
	void Drop();
	void Update() override;
	void ProcessInput(Window* wnd, float dt) override;
};

