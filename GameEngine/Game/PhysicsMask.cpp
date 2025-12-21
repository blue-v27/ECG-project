#include "PhysicsMask.h"
#include "GameContext.h"

PhysicsMask::PhysicsMask(glm::vec3& pos)
	: m_pos(pos), m_gravity(-9.81f * 10.f), m_velocity(glm::vec3(0)), m_mass(0), m_lastFramePos(glm::vec3(1)), m_speed(0)
{

}

void PhysicsMask::UpdatePhysics()
{
	ApplyGravity();

	glm::vec3 vel = glm::vec3(m_velocity.x, 0, m_velocity.z);
	m_speed = glm::length(vel);

	printf("Speed: %d Velocity: %f %f %f\n", m_speed, glm::abs(m_velocity.x), glm::abs(m_velocity.y), glm::abs(m_velocity.z));
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
