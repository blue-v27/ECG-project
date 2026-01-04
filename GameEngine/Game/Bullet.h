#pragma once
#include "InteractiveGameObject.h"
class Bullet : public InteractiveGameObject
{
private:
	glm::vec3 m_origin;
	glm::vec3 m_direction;
	float m_speed;
public:
	Bullet(glm::vec3 origin, glm::vec3 dir, float speed);
	~Bullet() = default;

	void Update() override;
};

