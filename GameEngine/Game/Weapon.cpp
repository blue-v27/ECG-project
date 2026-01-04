#include "Weapon.h"
#include "Ray.h"
#include "GameContext.h"

Weapon::Weapon(float damage, float delay, float range)
{
	m_delay = delay;
	m_canAttack = false;
	m_range = range;
	m_damage = damage;
	m_time = 0;
}

Weapon::~Weapon()
{
}

void Weapon::Attack()
{
	if (!m_canAttack)
		return;

	Ray ray;
	std::vector<GameObject*> arr = GAMECONTEXT.GetObjectsInRange(CAMERA.GetPos(), 2 * m_range);

	for (GameObject* obj : arr)
	{
		glm::vec3 hitPoint;
		if (ray.RayCast(CAMERA.GetPos(), CAMERA.getCameraViewDirection(), m_range, obj, hitPoint))
		{
			obj->GetDamage(m_damage);
			SetScale(GetScale() * 1.1f);
			break;
		}
	}
}

void Weapon::Drop()
{
	if (GetParrent())
	{
		RemoveParrentLink();
		IsPickable(true);
		InitPhysics();
	}
}

void Weapon::Update()
{
	if (!m_canAttack)
	{
		if (glfwGetTime() - m_time > m_delay)
		{
			m_canAttack = true;
			m_time = glfwGetTime();
		}
	}

	ProcessInput(GAMECONTEXT.GetWindow(), GAMECONTEXT.GetDeltaTime());

	InteractiveGameObject::Update();
}

void Weapon::ProcessInput(Window* wnd, float dt)
{
	if (wnd->IsMouseReleased(1))
		Attack();
	if (wnd->IsReleased(GLFW_KEY_Q))
		Drop();
}
