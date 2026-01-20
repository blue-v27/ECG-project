#include "PhysicsMask.h"
#include "GameContext.h"

PhysicsMask::PhysicsMask(glm::vec3& pos)
	: m_pos(pos), m_gravity(-9.81f * 10.f), m_velocity(glm::vec3(0)), m_mass(0), m_lastFramePos(glm::vec3(1)), m_speed(0)
{
	m_isSwinging = false;
	m_ropeLength = 0.0f;
	m_anchor	 = glm::vec3(0.f);
}

void PhysicsMask::UpdatePhysics()
{
	float dt = GAMECONTEXT.GetDeltaTime();	

	ApplyGravity();

	if (m_isSwinging)
	{	
		Swing();

		float friction = 1.5f;
		m_velocity    -= m_velocity * friction * dt;
	}
	else
	{
		float friction = 8.0f;
		m_velocity.x -= m_velocity.x * friction * dt;
		m_velocity.z -= m_velocity.z * friction * dt;

		glm::vec3 vel = glm::vec3(m_velocity.x, 0, m_velocity.z);
		m_speed = glm::length(vel);
	}	

	m_pos.x += m_velocity.x * dt; // dx / dt ^ 2
	m_pos.z += m_velocity.z * dt; // dx / dt ^ 2
}

void PhysicsMask::ApplyGravity()
{
	float dt = GAMECONTEXT.GetDeltaTime(); 

	m_velocity.y += m_gravity * dt; // dx / dt

	m_pos.y += m_velocity.y * dt; // dx / dt ^ 2
}

void PhysicsMask::ComputeVelocity()
{
	float dx = m_pos.x - m_lastFramePos.x;
	float dz = m_pos.z - m_lastFramePos.z;
	float dt = GAMECONTEXT.GetDeltaTime();

	if (dt)
	{
		m_velocity.x = dx / dt;
		m_velocity.z = dz / dt;
	}
}

void PhysicsMask::StartSwing(glm::vec3 anchor)
{
	m_isSwinging = true;
	m_ropeLength = glm::distance(m_pos, anchor);
	m_anchor	 = anchor;
}

void PhysicsMask::StopSwinging()
{
	m_isSwinging = false;
}

void PhysicsMask::Swing()
{
	float distance = glm::distance(m_pos, m_anchor);
	if (!distance)
		return;

	glm::vec3 direction = (m_pos - m_anchor) / distance;

	m_pos = m_anchor + direction * m_ropeLength;

	float vel = glm::dot(m_velocity, direction);
	m_velocity -= direction * vel;
}