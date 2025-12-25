#pragma once

#include <glm.hpp>
#include <gtx\transform.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

class PhysicsMask
{
private:
	glm::vec3& m_pos;
	glm::vec3 m_velocity;
	glm::vec3 m_lastFramePos;
	
	int   m_speed;
	float m_mass;
	float m_acc = 10;

	float m_gravity;


public:
	PhysicsMask(glm::vec3& pos);

	void UpdatePhysics();
	
	void ApplyGravity();

	void ComputeVelocity();

	void SetLastFramePos(glm::vec3 pos) { m_lastFramePos = pos; }

	glm::vec3 GetVelocity()         { return m_velocity; }
	void SetVelocityY(float value)  { m_velocity.y = value;  }
	void AddVelocity(glm::vec3 vel) { m_velocity += vel; }
};

