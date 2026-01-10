#include "Bullet.h"
#include "GameContext.h"

Bullet::Bullet()
{
	m_isActive  = false;
	m_scale	    = glm::vec3(0.01f);
	m_speed	    = 0.f;
	m_startTime = glfwGetTime();

	SetMesh(MESH_DEFINES.GetMesh(MESH_SPHERE));
	InitShader(BASIC);
	GAMECONTEXT.AddObject(this);
}

void Bullet::BulletBeginShoot(glm::vec3 origin, glm::vec3 dir, float speed)
{
	m_isActive  = true; 
	m_pos	    = origin;
	m_direction = dir;
	m_speed     = speed;
	m_startTime = glfwGetTime();
	m_scale     = glm::vec3(0.01f);
}

void Bullet::Update()
{
	m_pos += m_direction * m_speed;

	InteractiveGameObject::Update();

	if (glfwGetTime() - m_startTime > .02f)
		GAMECONTEXT.MarkForRemoval(this);
}
