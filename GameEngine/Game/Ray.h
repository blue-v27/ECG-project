#pragma once
#include "GameContext.h"

class Ray
{
public:
	glm::vec3 m_origin;
	glm::vec3 m_direction;

	Ray();

	bool RayCast(glm::vec3 origin, glm::vec3 direction, float range, GameObject* obj, glm::vec3& outHitPoint);
};

