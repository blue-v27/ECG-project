#include "RangedWeapon.h"
#include "GameContext.h"
#include "Ray.h"

RangedWeapon::RangedWeapon(float damange, float delay, float range) : Weapon(damange, delay, range)
{
	
}

RangedWeapon::~RangedWeapon()
{

}

void RangedWeapon::Shoot()
{
	if (!m_canAttack)
		return;

	Ray ray;
	std::vector<GameObject*> arr = GAMECONTEXT.GetObjectsInRange(CAMERA.GetPos(), 2 * m_range);

	Bullet* bullet = new Bullet(m_shotPoint, CAMERA.getCameraViewDirection(), 10.f * GAMECONTEXT.GetDeltaTime());
	GAMECONTEXT.AddObject(bullet);

	for (GameObject* obj : arr)
	{
		glm::vec3 hitPoint;
		if (ray.RayCast(CAMERA.GetPos() + glm::vec3(0.0f, 0.0f, 2.0f), CAMERA.getCameraViewDirection(), m_range, obj, hitPoint))
		{
			obj->GetDamage(m_damage);
			//GAMECONTEXT.RemoveObject(bullet);
			break;
		}
	}

	bullet = nullptr;
}

void RangedWeapon::Update()
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

void RangedWeapon::ProcessInput(Window* wnd, float dt)
{
	if (wnd->IsMouseReleased(1))
		Shoot();
}
