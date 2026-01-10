#pragma once
#include "InteractiveGameObject.h"
class Bullet : public InteractiveGameObject
{
private:
	glm::vec3 m_origin;
	glm::vec3 m_direction;

	double m_startTime;
	float  m_speed;
public:
	Bullet();
	~Bullet() = default;

	void BulletBeginShoot(glm::vec3 origin, glm::vec3 dir, float speed);

	void Update() override;
};

