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
	Weapon() = default;
	~Weapon();
	
	void SetDamage(int damage) { m_damage = damage; }
	void SetDelay(int delay)   { m_delay = delay; }
	void SetRange(int range)   { m_range = range; }

	void Attack();
	void Drop();
	void Update() override;
	void ProcessInput(Window* wnd, float dt) override;
};

