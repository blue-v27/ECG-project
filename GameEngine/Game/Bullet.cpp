#include "Bullet.h"
#include "GameContext.h"

Bullet::Bullet(glm::vec3 origin, glm::vec3 dir, float speed)
{
	m_pos = origin;
	m_direction = dir;
	m_speed = speed;

	m_scale = glm::vec3(0.1f);

	Init(&MESH_DEFINES.GetMesh(SPHERE));
	GAMECONTEXT.AddObject(this);
}

void Bullet::Update()
{
	//m_pos += m_direction * m_speed;

	InteractiveGameObject::Update();
}
